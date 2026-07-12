#pragma once

#include "BackendManager.h"

class LeastConnectionLoadBalancer
{
public:

    BackendServer& getNextServer(BackendManager &backendManager);

};