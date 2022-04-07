#include "../include/handler.h"
#include "../include/promotioncrudset.h"
#include "../include/storecrudset.h"
#include "../include/productcrudset.h"

#include <thread>

handler::handler(utility::string_t url):m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&handler::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));

    crudMap["promotions"] = std::shared_ptr<CrudCommandSet>(new PromotionCrudSet);
    crudMap["stores"] = std::shared_ptr<CrudCommandSet>(new StoreCrudSet);
    crudMap["products"] = std::shared_ptr<CrudCommandSet>(new ProductCrudSet);
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
    try {
        web::uri myuri(message.request_uri());
        std::string firstDir = http::uri::split_path(myuri.path())[0];

        if(crudMap.find(firstDir) != crudMap.end()) {
            pplx::task<void>([=]{crudMap[firstDir]->Get(message);});
        }
        else {
            try {   
                message.reply(status_codes::NotFound);
            }
            catch(...) { }
    
        }
    }
    catch(...) {
        try {   
            message.reply(status_codes::InternalError);
        }
        catch(...) { }
    }
    return;
};

void handler::handle_post(http_request message)
{
    ucout << message.to_string() << endl;
    try {
        web::uri myuri(message.request_uri());
        std::string firstDir = http::uri::split_path(myuri.path())[0];

        if(crudMap.find(firstDir) != crudMap.end()) {
            pplx::task<void>([=]{crudMap[firstDir]->Post(message);});
        }
        else {
            try {   
                message.reply(status_codes::NotFound);
            }
            catch(...) { }
    
        }
    }
    catch(...) {
        try {   
            message.reply(status_codes::InternalError);
        }
        catch(...) { }
    }
    return;
};

void handler::handle_delete(http_request message)
{
    ucout << message.to_string() << endl;
    try {
        web::uri myuri(message.request_uri());
        std::string firstDir = http::uri::split_path(myuri.path())[0];

        if(crudMap.find(firstDir) != crudMap.end()) {
            pplx::task<void>([=]{crudMap[firstDir]->Delete(message);});
        }
        else {
            try {   
                message.reply(status_codes::NotFound);
            }
            catch(...) { }
    
        }
    }
    catch(...) {
        try {   
            message.reply(status_codes::InternalError);
        }
        catch(...) { }
    }
    return;
};


void handler::handle_put(http_request message)
{
    ucout << message.to_string() << endl;
    try {
        web::uri myuri(message.request_uri());
        std::string firstDir = http::uri::split_path(myuri.path())[0];

        if(crudMap.find(firstDir) != crudMap.end()) {
            pplx::task<void>([=]{crudMap[firstDir]->Put(message);});
        }
        else {
            try {   
                message.reply(status_codes::NotFound);
            }
            catch(...) { }
    
        }
    }
    catch(...) {
        try {   
            message.reply(status_codes::InternalError);
        }
        catch(...) { }
    }
    return;
};