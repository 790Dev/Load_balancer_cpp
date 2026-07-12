#pragma once

#include <winsock2.h>

class ClientHandler
{
public:

    static void handleClient(SOCKET clientSocket);
};