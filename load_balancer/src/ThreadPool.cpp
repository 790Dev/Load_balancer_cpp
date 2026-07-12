#include "../include/ThreadPool.h"

#include "../include/Logger.h"

ThreadPool::ThreadPool(
    int numberOfThreads,
    LoadBalancer &lb
)
    : loadBalancer(lb)
{
    stop = false;

    for (int i = 0; i < numberOfThreads; i++)
    {
        workers.push_back(
            std::thread(
                &ThreadPool::worker,
                this
            )
        );
    }

    Logger::info(
        "Thread Pool Started"
    );
}

ThreadPool::~ThreadPool()
{
    stop = true;

    condition.notify_all();

    for (int i = 0; i < workers.size(); i++)
    {
        if (workers[i].joinable())
        {
            workers[i].join();
        }
    }
}

void ThreadPool::addClient(SOCKET clientSocket)
{
    {
        std::lock_guard<std::mutex> lock(queueMutex);

        clientQueue.push(clientSocket);
    }

    condition.notify_one();
}

void ThreadPool::worker()
{
    while (true)
    {
        SOCKET clientSocket;

        {
            std::unique_lock<std::mutex> lock(queueMutex);

            condition.wait(
                lock,
                [this]
                {
                    return stop || !clientQueue.empty();
                }
            );

            if (stop)
            {
                return;
            }

            clientSocket = clientQueue.front(); 

            clientQueue.pop();
        }

        Logger::info(
            "Worker Thread Processing Client"
        );

        loadBalancer.handleClient(clientSocket);
    }
}