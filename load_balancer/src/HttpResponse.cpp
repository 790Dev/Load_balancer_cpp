#include "../include/HttpResponse.h"

#include <string>
using namespace std;

HttpResponse::HttpResponse()
{
    statusCode = 200;

    statusMessage = "OK";
}

string HttpResponse::buildResponse()
{
    string response;

    response += "HTTP/1.1 ";
    response += to_string(statusCode);
    response += " ";
    response += statusMessage;
    response += "\r\n";

    // Content-Length is required
    headers["Content-Length"] = to_string(body.size());

    // Default Content-Type
    if (headers.find("Content-Type") == headers.end())
    {
        headers["Content-Type"] = "text/plain";
    }

    // Add all headers
    for (auto header : headers)
    {
        response += header.first;
        response += ": ";
        response += header.second;
        response += "\r\n";
    }

    // Blank line between headers and body
    response += "\r\n";

    // Add body
    response += body;

    return response;
}