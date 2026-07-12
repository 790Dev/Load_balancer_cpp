#include "../include/BackendManager.h"

void BackendManager::addServer(BackendServer server)
{
    servers.push_back(server);
}

void BackendManager::removeServer(int id)
{
    for (int i = 0; i < servers.size(); i++)
    {
        if (servers[i].id == id)
        {
            servers.erase(servers.begin() + i);
            break;
        }
    }
}

BackendServer& BackendManager::getServer(int index)
{
    return servers[index];
}

std::vector<BackendServer> & BackendManager::getAllServers()
{
    return servers;
}

int BackendManager::getServerCount()
{
    return servers.size();
}

std::string BackendManager::toJson()
{
    std::string json = "[";
    for (size_t i = 0; i < servers.size(); i++)
    {
        json += "{";
        json += "\"id\":" + std::to_string(servers[i].id) + ",";
        json += "\"port\":" + std::to_string(servers[i].port) + ",";
        json += "\"healthy\":" + std::string(servers[i].isHealthy ? "true" : "false") + ",";
        json += "\"requests\":" + std::to_string(servers[i].activeConnections) + ",";
        json += "\"totalHandled\":" + std::to_string(servers[i].totalRequestsHandled);
        json += "}";
        if (i < servers.size() - 1)
        {
            json += ",";
        }
    }
    json += "]";
    return json;
}