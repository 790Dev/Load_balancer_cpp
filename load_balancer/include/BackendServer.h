#pragma once

#include <string>

class BackendServer
{
public:

    int id;

    std::string ipAddress;

    int port;

    bool isHealthy;

    int activeConnections;

    int totalRequestsHandled;

public:

    BackendServer();

    BackendServer(int id,
                  std::string ipAddress,
                  int port);
};