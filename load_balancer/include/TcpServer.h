#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class TcpServer
{
public:

    TcpServer();

    ~TcpServer();

    bool createSocket();

    bool bindToPort(int port);

    bool startListening(int backlog = 10);

    SOCKET acceptClient();

    int receive(SOCKET clientSocket, char* buffer, int size);

    int send(SOCKET clientSocket, const char* buffer, int size);

    void close();

private:

    SOCKET serverSocket;
};