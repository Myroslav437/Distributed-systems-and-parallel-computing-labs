#ifndef HANDLER_H
#define HANDLER_H

#include "stdafx.h"
#include "../include/crudcommandset.h"
#include <map>
#include <string>
#include <memory>

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


class handler
{
    public:
        handler(utility::string_t url);

        pplx::task<void> open(){return m_listener.open();}
        pplx::task<void> close(){return m_listener.close();}

    private:
        void handle_get(http_request message);
        void handle_put(http_request message);
        void handle_post(http_request message);
        void handle_delete(http_request message);
        void handle_error(pplx::task<void>& t);

        http_listener m_listener;
        std::map<std::string, std::shared_ptr<CrudCommandSet>> crudMap;
};

#endif // HANDLER_H
