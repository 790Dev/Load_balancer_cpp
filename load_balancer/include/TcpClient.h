#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

#include <string>

#pragma comment(lib, "ws2_32.lib")

class TcpClient
{
public:

    TcpClient();

    ~TcpClient();

    bool createSocket();

    bool connectToServer(std::string ipAddress, int port);

    int sendData(const char* data, int size);

    int receiveData(char* buffer, int size);

    std::string sendHttpRequest(const std::string &request);

    void close();

private:

    SOCKET clientSocket;
};