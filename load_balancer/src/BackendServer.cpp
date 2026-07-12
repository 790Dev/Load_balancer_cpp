#include "../include/BackendServer.h"

BackendServer::BackendServer()
{
    id = 0;

    ipAddress = "";

    port = 0;

    isHealthy = true;

    activeConnections = 0;

    totalRequestsHandled = 0;
}

BackendServer::BackendServer(int serverId,
                             std::string ip,
                             int serverPort)
{
    id = serverId;

    ipAddress = ip;

    port = serverPort;

    isHealthy = true;

    activeConnections = 0;

    totalRequestsHandled = 0;
}