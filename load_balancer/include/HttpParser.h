#pragma once

#include <string>
#include <sstream>

#include "HttpRequest.h"

class HttpParser
{
public:

    HttpRequest parse(std::string request);

private:

    void parseRequestLine(std::string line, HttpRequest &request);

    void parseHeader(std::string line, HttpRequest &request);
};