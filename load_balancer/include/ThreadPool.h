#pragma once

#include <winsock2.h>

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "LoadBalancer.h"
class ThreadPool
{
public:

    ThreadPool(int numberOfThreads,LoadBalancer &loadBalancer);

    ~ThreadPool();

    void addClient(SOCKET clientSocket);

private:

    void worker();

private:

    std::vector<std::thread> workers;

    std::queue<SOCKET> clientQueue;

    std::mutex queueMutex;

    std::condition_variable condition;

    bool stop;

    LoadBalancer &loadBalancer; 
};