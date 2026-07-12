#pragma once

#include <string>

#include "BackendServer.h"
#include "TcpClient.h"

class ReverseProxy
{
public:

    std::string forwardRequest(BackendServer backend,
                               std::string request);

};