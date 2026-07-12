#include "../include/Metrics.h"

#include <iostream>

Metrics::Metrics()
{
    totalRequests = 0;

    failedRequests = 0;

    activeConnections = 0;
}

void Metrics::incrementTotalRequests()
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    totalRequests++;
}

void Metrics::incrementBackendRequests(int backendId)
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    backendRequests[backendId]++;
}

void Metrics::incrementFailedRequests()
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    failedRequests++;
}

void Metrics::incrementActiveConnections()
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    activeConnections++;
}

void Metrics::decrementActiveConnections()
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    if (activeConnections > 0)
    {
        activeConnections--;
    }
}

void Metrics::printMetrics()
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    std::cout << "\n";
    std::cout << "========== Metrics ==========\n";

    std::cout << "Total Requests : "
              << totalRequests
              << std::endl;

    std::cout << "Failed Requests : "
              << failedRequests
              << std::endl;

    std::cout << "Active Connections : "
              << activeConnections
              << std::endl;

    std::cout << "\nBackend Requests\n";

    for (auto entry : backendRequests)
    {
        std::cout << "Backend "
                  << entry.first
                  << " : "
                  << entry.second
                  << std::endl;
    }

    std::cout << "=============================\n";
}

std::string Metrics::toJson()
{
    std::lock_guard<std::mutex> lock(metricsMutex);
    std::string json = "{";
    json += "\"totalRequests\":" + std::to_string(totalRequests) + ",";
    json += "\"failedRequests\":" + std::to_string(failedRequests) + ",";
    json += "\"activeConnections\":" + std::to_string(activeConnections);
    json += "}";
    return json;
}