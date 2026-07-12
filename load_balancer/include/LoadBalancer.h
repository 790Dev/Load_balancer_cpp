#pragma once

#include <winsock2.h>
#include <thread>
#include <chrono>
#include <mutex>

#include "BackendManager.h"
#include "LoadBalancingAlgorithm.h"
#include "RoundRobinLoadBalancer.h"
#include "LeastConnectionLoadBalancer.h"
#include "ReverseProxy.h"
#include "HttpParser.h"
#include "Metrics.h"
#include "TcpClient.h"

class LoadBalancer
{
public:

    LoadBalancer();

    void initializeBackends();

    void handleClient(SOCKET clientSocket);

    void printMetrics();

    void setAlgorithm(LoadBalancingAlgorithm newAlgorithm);

private:

    void healthCheckLoop();

private:

    BackendManager backendManager;

    LoadBalancingAlgorithm algorithm;

    RoundRobinLoadBalancer roundRobin;

    LeastConnectionLoadBalancer leastConnection;

    ReverseProxy reverseProxy;

    Metrics metrics;

    std::thread healthCheckThread;
    
    std::mutex routingMutex;
};