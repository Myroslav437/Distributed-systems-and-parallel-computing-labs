#include "../include/productcrudset.h"
#include <tuple>

void ProductCrudSet::Get(web::http::http_request message) 
{
    try {
        auto queries = web::http::uri::split_query(message.absolute_uri().query());
        auto it = queries.begin();

        web::json::value jval;

        if(queries.size() == 0) {
            auto data = Dbcontroller::GetInstance()->getProducts();
            int arridx = 0;
            for(const auto& a : data) {
                auto tmpval = JsonConverter::productsToJson(a.second);
                tmpval["id"] = a.first;
                jval[arridx++] = tmpval;
            }
        }
        else if((it = queries.find("id")) != queries.end()) {
            auto data = Dbcontroller::GetInstance()->getProduct(std::stoi(it->second));
            auto tmpval = JsonConverter::productsToJson(data.second);
            tmpval["id"] = data.first;

            jval[0] = tmpval;
        }
        else if (it == queries.end()){
            throw std::invalid_argument("Invalid query");
        }

        message.reply(web::http::status_codes::OK, jval).then([](pplx::task<void> t)
		{
			try { t.get(); }
			catch(...) { }
    	});
    }
    catch(const std::exception& e) {
        message.reply(web::http::status_codes::BadRequest, e.what(),  U("text/plain")).then([](pplx::task<void> t)
		{
			try { t.get(); }
			catch(...) { }
    	});
    }
}

void ProductCrudSet::Post(web::http::http_request message) 
{

}

void ProductCrudSet::Put(web::http::http_request message) 
{
    try {
        auto queries = web::http::uri::split_query(message.absolute_uri().query());
        auto it = queries.begin();

        web::json::value jval;

        if(queries.size() == 0) {
            throw std::invalid_argument("Invalid query");
        }
        else if((it = queries.find("id")) != queries.end()) {
            auto val = Dbcontroller::GetInstance()->getProduct(std::stoi(it->second));
            // <productPrice, productName, productManufacturer>:
            if((it = queries.find("productPrice")) != queries.end()) {
                std::get<0>(val.second.get()) = std::stof(it->second);
            }
            if((it = queries.find("productName")) != queries.end()) {
                std::get<1>(val.second.get()) = it->second;
            }
            if((it = queries.find("productManufacturer")) != queries.end()) {
                std::get<2>(val.second.get()) = it->second;
            }
        }
        else if (it == queries.end()){
            throw std::invalid_argument("Invalid query");
        }

        message.reply(web::http::status_codes::OK, jval).then([](pplx::task<void> t)
		{
			try { t.get(); }
			catch(...) { }
    	});
    }
    catch(const std::exception& e) {
        message.reply(web::http::status_codes::BadRequest, e.what(),  U("text/plain")).then([](pplx::task<void> t)
		{
			try { t.get(); }
			catch(...) { }
    	});
    }
}

void ProductCrudSet::Delete(web::http::http_request message) 
{
    try {
        auto queries = web::http::uri::split_query(message.absolute_uri().query());
        auto it = queries.begin();

        web::json::value jval;

        if(queries.size() == 0) {
            throw std::invalid_argument("Invalid query");
        }
        else if((it = queries.find("id")) != queries.end()) {
            Dbcontroller::GetInstance()->removeProduct(std::stoi(it->second));
        }
        else if (it == queries.end()){
            throw std::invalid_argument("Invalid query");
        }

        message.reply(web::http::status_codes::OK, jval).then([](pplx::task<void> t)
		{
			try { t.get(); }
			catch(...) { }
    	});
    }
    catch(const std::exception& e) {
        message.reply(web::http::status_codes::BadRequest, e.what(),  U("text/plain")).then([](pplx::task<void> t)
		{
			try { t.get(); }
			catch(...) { }
    	});
    }
}