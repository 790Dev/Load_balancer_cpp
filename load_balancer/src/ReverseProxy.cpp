#include "../include/ReverseProxy.h"

#include <iostream>

std::string ReverseProxy::forwardRequest(BackendServer backend,
                                         std::string request)
{
    TcpClient client;

    if (!client.createSocket())
    {
        return "";
    }

    if (!client.connectToServer(backend.ipAddress, backend.port))
    {
        return "";
    }

    client.sendData(request.c_str(), request.length());

    char buffer[8192];

    int bytes = client.receiveData(buffer, sizeof(buffer) - 1);

    if (bytes <= 0)
    {
        client.close();
        return "";
    }

    buffer[bytes] = '\0';

    client.close();

    return std::string(buffer);
}