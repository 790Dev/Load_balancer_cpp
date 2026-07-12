#include "../include/HealthChecker.h"

#include <iostream>

void HealthChecker::checkServers(BackendManager &manager)
{
    std::vector<BackendServer> &servers =
        manager.getAllServers();

    for (int i = 0; i < servers.size(); i++)
    {
        TcpClient client;

        bool healthy = false;

        if (client.createSocket())
        {
            if (client.connectToServer(
                    servers[i].ipAddress,
                    servers[i].port))
            {
                healthy = true;
            }
        }

        servers[i].isHealthy = healthy;

        if (healthy)
        {
            std::cout
                << "[HEALTH] Backend "
                << servers[i].id
                << " is UP"
                << std::endl;
        }
        else
        {
            std::cout
                << "[HEALTH] Backend "
                << servers[i].id
                << " is DOWN"
                << std::endl;
        }

        client.close();
    }
}