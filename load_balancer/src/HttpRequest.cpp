#include "../include/HttpRequest.h"

HttpRequest::HttpRequest()
{
    clear();
}

void HttpRequest::clear()
{
    method.clear();
    path.clear();
    version.clear();

    headers.clear();

    body.clear();
}