#pragma once

#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

class NetworkInitializer
{
public:

    NetworkInitializer();

    ~NetworkInitializer();

private:

    WSADATA wsaData;
};