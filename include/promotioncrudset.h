#ifndef PROMOTIONCRUDSET_H
#define PROMOTIONCRUDSET_H

#include "crudcommandset.h"
#include "../include/jsonconverter.h"
#include "../include/dbcontroller.h"

class PromotionCrudSet : public CrudCommandSet 
{
 public:
    virtual void Get(web::http::http_request message) override;
    virtual void Post(web::http::http_request message) override;
    virtual void Delete(web::http::http_request message) override;
    virtual void Put(web::http::http_request message) override;
};
#endif