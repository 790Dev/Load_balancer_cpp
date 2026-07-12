#include "../include/HttpParser.h"
#include <sstream>
#include <string>
using namespace std;

HttpRequest HttpParser::parse(string request)
{
    HttpRequest httpRequest;

    stringstream ss(request);

    string line;

    bool firstLine = true;

    while (getline(ss, line))
    {
        // Remove '\r' from the end of the line
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        // Empty line means headers are finished
        if (line.empty())
        {
            break;
        }

        if (firstLine)
        {
            parseRequestLine(line, httpRequest);
            firstLine = false;
        }
        else
        {
            parseHeader(line, httpRequest);
        }
    }

    return httpRequest;
}

void HttpParser::parseRequestLine(string line, HttpRequest &httpRequest)
{
    stringstream ss(line);

    ss >> httpRequest.method;
    ss >> httpRequest.path;
    ss >> httpRequest.version;
}

void HttpParser::parseHeader(string line, HttpRequest &httpRequest)
{
    int position = line.find(':');

    if (position == string::npos)
    {
        return;
    }

    string key = line.substr(0, position);

    string value = line.substr(position + 1);

    // Remove leading space
    if (!value.empty() && value[0] == ' ')
    {
        value.erase(0, 1);
    }

    httpRequest.headers[key] = value;
}