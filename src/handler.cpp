#include "../include/handler.h"
#include "../include/promotioncrudset.h"

handler::handler(utility::string_t url):m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&handler::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));

    crudMap["promotions"] = std::shared_ptr<CrudCommandSet>(new PromotionCrudSet);
}

void handler::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error, Log it if a logger is available
    }
}


//
// Get Request 
//
void handler::handle_get(http_request message)
{
    ucout << message.to_string() << endl;
    ucout << "absolute_uri\t" << message.absolute_uri().to_string() << endl;

    web::uri myuri(message.request_uri());

    ucout << "path\t" << myuri.path() << std::endl;
    auto paths = http::uri::split_path(myuri.path());  
    for(const auto& p : paths) {
        std::cout << p << std::endl;
    }

    ucout << "query\t" << myuri.query() << std::endl;
    auto queries = http::uri::split_query(myuri.query());
    for(const auto& p : queries) {
        std::cout << p.first << "\t" << p.second << std::endl;
    }

    this->crudMap["promotions"]->Get(message);
    //pplx::task<void>([this, message](){});

    return;

};

void handler::handle_post(http_request message)
{
    ucout <<  message.to_string() << endl;

    message.reply(status_codes::OK,message.to_string());
    return ;
};

void handler::handle_delete(http_request message)
{
    ucout <<  message.to_string() << endl;

    message.reply(status_codes::OK, message.to_string());
    return;
};


void handler::handle_put(http_request message)
{
    ucout <<  message.to_string() << endl;

    message.reply(status_codes::OK, message.to_string());
    return;
};