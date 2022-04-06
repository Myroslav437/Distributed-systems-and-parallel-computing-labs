#include <iostream>

#include "include/stdafx.h"
#include "include/handler.h"
#include "include/database.h"

using namespace web;
using namespace http;
using namespace http::experimental::listener;

std::unique_ptr<handler> g_httpHandler;

void initDatabase();

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

void initDatabase(){
    Database::GetInstance()->products = std::map<int, Database::product_t>{
        {1, Database::product_t(10.0, "Milk", "TexasDiary Co.")},
        {2, Database::product_t(85.0, "Cheese", "Nestle UK Co.")},
        {3, Database::product_t(17.0, "Chockolate", "IndianCocoa Co.")},
        {4, Database::product_t(123.0, "Sparkling water", "CristalWater Co.")},
        {5, Database::product_t(446.0, "Nutella", "Nestle Ukraine Co.")}
    };

    Database::GetInstance()->promotions = std::map<int, Database::promotion_t>{
        {1, Database::promotion_t("Buy 2 chocolates and get third for free", "27.03.2022", "10.04.2022")},
        {2, Database::promotion_t("Get 10\% discount for all diary products", "05.05.2022", "12.05.2022")},
        {3, Database::promotion_t("Giveaway of a brand new coffee machine", "06.03.2022", "06.04.2022")}
    };

    Database::GetInstance()->stores = std::map<int, Database::store_t>{
        {1, Database::store_t("London, 50 Picadilly St.", "manager.picadilly@mystore.com", "066235423")},
        {2, Database::store_t("Edinburgh, 10 Arthur's hill", "manager.edinburgh@mystore.com", "066137468")},
    };
}