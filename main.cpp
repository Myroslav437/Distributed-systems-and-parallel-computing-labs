#include <iostream>

#include "include/stdafx.h"
#include "include/handler.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<handler> g_httpHandler;

void on_initialize(const string_t& address);
void on_shutdown();

int main(int argc, char *argv[])
{
    utility::string_t port = U("800");

    utility::string_t address = U("http://127.0.0.1:");
    if(argc > 1) {
        address = argv[1];    
    }

    address.append(port);

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}

void on_initialize(const string_t& address)
{
    uri_builder uri(address);

    auto addr = uri.to_uri().to_string();
    g_httpHandler = std::unique_ptr<handler>(new handler(addr));
    g_httpHandler->open().wait();

    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

    return;
}

void on_shutdown()
{
    g_httpHandler->close().wait();
    return;
}