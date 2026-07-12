#include "../include/RoundRobinLoadBalancer.h"
#include<iostream>

RoundRobinLoadBalancer::RoundRobinLoadBalancer()
{
    currentServer = 0;
}

BackendServer& RoundRobinLoadBalancer::getNextServer(BackendManager &backendManager)
{
    int totalServers = backendManager.getServerCount();

    if (totalServers == 0)
    {
        static BackendServer emptyServer;
        return emptyServer;
    }

    int checkedServers = 0;

    while (checkedServers < totalServers)
    {
        BackendServer& server = backendManager.getServer(currentServer);

        currentServer++;

        if (currentServer >= totalServers)
        {
            currentServer = 0;
        }

        if (server.isHealthy)
        {
            return server;
        }

        checkedServers++;
    }

    std::cout << "[ERROR] No Healthy Backend Available\n";

    static BackendServer emptyServer;
    return emptyServer;
}