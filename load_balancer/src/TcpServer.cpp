#include "TcpServer.h"

#include <iostream>

TcpServer::TcpServer()
{
    serverSocket = INVALID_SOCKET;
}

TcpServer::~TcpServer()
{
    close();
}

bool TcpServer::createSocket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET)
    {
        std::cout << "[ERROR] Failed to create socket.\n";
        return false;
    }

    std::cout << "[INFO] Socket created successfully.\n";

    return true;
}

bool TcpServer::bindToPort(int port)
{
    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (::bind(
            serverSocket,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cout << "[ERROR] Failed to bind socket.\n";
        return false;
    }

    std::cout << "[INFO] Bound to port " << port << ".\n";

    return true;
}

bool TcpServer::startListening(int backlog)
{
    if (::listen(serverSocket, backlog) == SOCKET_ERROR)
    {
        std::cout << "[ERROR] Failed to listen.\n";
        return false;
    }

    std::cout << "[INFO] Listening for incoming connections...\n";

    return true;
}

SOCKET TcpServer::acceptClient()
{
    SOCKET clientSocket = ::accept(serverSocket, nullptr, nullptr);

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "[ERROR] Failed to accept client.\n";
        return INVALID_SOCKET;
    }

    std::cout << "[INFO] Client connected.\n";

    return clientSocket;
}

int TcpServer::receive(SOCKET clientSocket, char* buffer, int size)
{
    return recv(clientSocket, buffer, size, 0);
}

int TcpServer::send(SOCKET clientSocket, const char* buffer, int size)
{
    return ::send(clientSocket, buffer, size, 0);
}

void TcpServer::close()
{
    if (serverSocket != INVALID_SOCKET)
    {
        closesocket(serverSocket);
        serverSocket = INVALID_SOCKET;
    }
}