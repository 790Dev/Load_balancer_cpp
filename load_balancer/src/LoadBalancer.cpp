#include "../include/LoadBalancer.h"
#include "../include/Logger.h"
#include <string>

LoadBalancer::LoadBalancer()
{
    healthCheckThread = std::thread(&LoadBalancer::healthCheckLoop, this);
}

void LoadBalancer::initializeBackends()
{
    backendManager.addServer(BackendServer(1, "127.0.0.1", 5001));
    backendManager.addServer(BackendServer(2, "127.0.0.1", 5002));
    backendManager.addServer(BackendServer(3, "127.0.0.1", 5003));
}

void LoadBalancer::handleClient(SOCKET clientSocket)
{
    metrics.incrementActiveConnections();

    char buffer[8192];

    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived <= 0)
    {
        metrics.decrementActiveConnections();
        closesocket(clientSocket);
        return;
    }

    buffer[bytesReceived] = '\0';

    std::string rawRequest(buffer);

    metrics.incrementTotalRequests();

    HttpParser parser;

    HttpRequest request = parser.parse(rawRequest);

    Logger::info(
        "Request : " +
        request.method +
        " " +
        request.path
    );

    // --- ADMIN API ROUTING ---
    if (request.path == "/metrics" || request.path == "/backends" || request.path == "/health" || 
        request.path == "/algorithm/round-robin" || request.path == "/algorithm/least-connection")
    {
        std::string jsonBody = "";
        
        if (request.path == "/metrics")
        {
            jsonBody = metrics.toJson();
        }
        else if (request.path == "/backends")
        {
            jsonBody = backendManager.toJson();
        }
        else if (request.path == "/health")
        {
            jsonBody = "{\"status\": \"ok\"}";
        }
        else if (request.path == "/algorithm/round-robin")
        {
            setAlgorithm(ROUND_ROBIN);
            jsonBody = "{\"status\": \"success\", \"algorithm\": \"round-robin\"}";
        }
        else if (request.path == "/algorithm/least-connection")
        {
            setAlgorithm(LEAST_CONNECTION);
            jsonBody = "{\"status\": \"success\", \"algorithm\": \"least-connection\"}";
        }

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Access-Control-Allow-Origin: *\r\n"
            "Connection: close\r\n"
            "Content-Length: " + std::to_string(jsonBody.length()) + "\r\n\r\n" +
            jsonBody;

        send(clientSocket, response.c_str(), response.length(), 0);
        closesocket(clientSocket);
        
        metrics.decrementActiveConnections();
        return;
    }
    // --- END ADMIN API ---

    BackendServer* backendPtr = nullptr;

    {
        std::lock_guard<std::mutex> lock(routingMutex);

        if (algorithm == ROUND_ROBIN)
        {
            backendPtr = &roundRobin.getNextServer(backendManager);
        }
        else
        {
            backendPtr = &leastConnection.getNextServer(backendManager);
        }

        backendPtr->activeConnections++;
        backendPtr->totalRequestsHandled++;
    }

    BackendServer& backend = *backendPtr;

    metrics.incrementBackendRequests(backend.id);

    Logger::info("Forwarding request to Backend " + std::to_string(backend.port));

    std::string backendResponse = reverseProxy.forwardRequest(backend, rawRequest);

    if (backendResponse.empty())
    {
        metrics.incrementFailedRequests();
        Logger::error("Backend Server Down");
        metrics.decrementActiveConnections();
        
        routingMutex.lock();
        backend.activeConnections--;
        routingMutex.unlock();
        
        closesocket(clientSocket);
        return;
    }

    send(clientSocket, backendResponse.c_str(), backendResponse.length(), 0);

    metrics.decrementActiveConnections();
    
    routingMutex.lock();
    backend.activeConnections--;
    routingMutex.unlock();
    
    closesocket(clientSocket);
}

void LoadBalancer::printMetrics()
{
    metrics.printMetrics();
}

void LoadBalancer::setAlgorithm(LoadBalancingAlgorithm newAlgorithm)
{
    algorithm = newAlgorithm;
}

void LoadBalancer::healthCheckLoop()
{
    while (true)
    {
        std::vector<BackendServer>& servers = backendManager.getAllServers();
        for (auto& server : servers)
        {
            TcpClient client;
            if (client.createSocket() && client.connectToServer(server.ipAddress, server.port))
            {
                server.isHealthy = true;
                client.close();
            }
            else
            {
                server.isHealthy = false;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
