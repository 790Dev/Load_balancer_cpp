#pragma once

#include "BackendManager.h"

class RoundRobinLoadBalancer
{
public:

    RoundRobinLoadBalancer();

    BackendServer& getNextServer(BackendManager &backendManager);

private:

    int currentServer;
};