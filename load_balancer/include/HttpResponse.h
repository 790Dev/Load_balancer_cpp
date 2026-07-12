#pragma once

#include <string>
#include <unordered_map>

class HttpResponse
{
public:

    int statusCode;

    std::string statusMessage;

    std::unordered_map<std::string, std::string> headers;

    std::string body;

public:

    HttpResponse();

    std::string buildResponse();
};