#ifndef CRUDCOMMANDSET_H
#define CRUDCOMMANDSET_H

#include "cpprest/http_listener.h"

class CrudCommandSet {
public:
    virtual void Get(web::http::http_request message) = 0;
    virtual void Post(web::http::http_request message) = 0;
    virtual void Delete(web::http::http_request message) = 0;
    virtual void Put(web::http::http_request message) = 0;
};

#endif