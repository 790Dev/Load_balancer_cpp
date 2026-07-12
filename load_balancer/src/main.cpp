#include <iostream>
#include <string>
#include <thread>
#include <functional>

#include "../include/NetworkInitializer.h"
#include "../include/TcpServer.h"
#include "../include/HttpParser.h"
#include "../include/LoadBalancer.h"
#include "../include/ThreadPool.h"
#include "../include/Logger.h"

int main()
{
    NetworkInitializer network;

    TcpServer server;

    if (!server.createSocket())
        return 1;

    if (!server.bindToPort(8080))
        return 1;

    if (!server.startListening())
        return 1;

    Logger::info("Load Balancer Started");
    Logger::info("Listening on Port 8080");

    LoadBalancer loadBalancer;
    loadBalancer.setAlgorithm(ROUND_ROBIN);
    loadBalancer.initializeBackends();

    ThreadPool pool(20, loadBalancer);

    while (true)
    {
        SOCKET client =
            server.acceptClient();

        if (client == INVALID_SOCKET)
        {
            continue;
        }

        pool.addClient(client);
    }

    return 0;
}