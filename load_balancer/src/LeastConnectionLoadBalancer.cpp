#include "../include/LeastConnectionLoadBalancer.h"

BackendServer& LeastConnectionLoadBalancer::getNextServer(
    BackendManager &backendManager)
{
    int totalServers = backendManager.getServerCount();

    if (totalServers == 0)
    {
        static BackendServer emptyServer;
        return emptyServer;
    }

    BackendServer* bestServer = nullptr;

    for (int i = 0; i < totalServers; i++)
    {
        BackendServer& current =
            backendManager.getServer(i);

        if (!current.isHealthy)
        {
            continue;
        }

        if (!bestServer)
        {
            bestServer = &current;
        }
        else if (current.activeConnections < bestServer->activeConnections)
        {
            bestServer = &current;
        }
    }

    if (!bestServer)
    {
        static BackendServer emptyServer;
        return emptyServer;
    }

    return *bestServer;
}