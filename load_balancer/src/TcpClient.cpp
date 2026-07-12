#include "../include/TcpClient.h"

#include <iostream>

TcpClient::TcpClient()
{
    clientSocket = INVALID_SOCKET;
}

TcpClient::~TcpClient()
{
    close();
}

bool TcpClient::createSocket()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "[ERROR] Failed to create client socket.\n";
        return false;
    }

    return true;
}

bool TcpClient::connectToServer(std::string ipAddress, int port)
{
    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    inet_pton(AF_INET,
              ipAddress.c_str(),
              &serverAddress.sin_addr);

    if (connect(clientSocket,
                (sockaddr*)&serverAddress,
                sizeof(serverAddress))
        == SOCKET_ERROR)
    {
        std::cout << "[ERROR] Failed to connect to backend server.\n";
        return false;
    }

    std::cout << "[INFO] Connected to Backend Server\n";

    return true;
}

int TcpClient::sendData(const char* data, int size)
{
    return send(clientSocket,
                data,
                size,
                0);
}

int TcpClient::receiveData(char* buffer, int size)
{
    return recv(clientSocket,
                buffer,
                size,
                0);
}

void TcpClient::close()
{
    if (clientSocket != INVALID_SOCKET)
    {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
    }
}

std::string TcpClient::sendHttpRequest(const std::string &request)
{
    sendData(request.c_str(), request.length());

    char buffer[8192];

    int bytes = receiveData(buffer, sizeof(buffer) - 1);

    if (bytes <= 0)
    {
        return "";
    }

    buffer[bytes] = '\0';

    return std::string(buffer);
}