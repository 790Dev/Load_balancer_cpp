#pragma once

#include <vector>

#include "BackendServer.h"

class BackendManager
{
public:

    void addServer(BackendServer server);

    void removeServer(int id);

    BackendServer& getServer(int index);

    std::vector<BackendServer>& getAllServers();

    int getServerCount();

    std::string toJson();

private:

    std::vector<BackendServer> servers;
};