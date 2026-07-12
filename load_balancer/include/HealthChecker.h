#pragma once

#include "BackendManager.h"
#include "TcpClient.h"

class HealthChecker
{
public:

    void checkServers(BackendManager &manager);

};