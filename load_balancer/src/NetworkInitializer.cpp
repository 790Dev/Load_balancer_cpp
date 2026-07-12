#include "NetworkInitializer.h"

NetworkInitializer::NetworkInitializer()
{
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        std::cout << "[ERROR] Failed to initialize Winsock.\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "[INFO] Winsock initialized successfully.\n";
}

NetworkInitializer::~NetworkInitializer()
{
    WSACleanup();

    std::cout << "[INFO] Winsock cleaned up.\n";
}