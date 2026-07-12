#pragma once

#include <map>
#include <mutex>
#include <string>

class Metrics
{
public:

    Metrics();

    void incrementTotalRequests();

    void incrementBackendRequests(int backendId);

    void incrementFailedRequests();

    void incrementActiveConnections();

    void decrementActiveConnections();

    void printMetrics();

    std::string toJson();

private:

    int totalRequests;

    int failedRequests;

    int activeConnections;

    std::map<int, int> backendRequests;

    std::mutex metricsMutex;
};