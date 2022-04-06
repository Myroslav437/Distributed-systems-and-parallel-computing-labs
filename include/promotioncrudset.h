#ifndef PROMOTIONCRUDSET_H
#define PROMOTIONCRUDSET_H

#include "crudcommandset.h"

class PromotionCrudSet : public CrudCommandSet 
{
    virtual void Get(web::http::http_request message) override;
    virtual void Post(web::http::http_request message) override;
    virtual void Delete(web::http::http_request message) override;
    virtual void Put(web::http::http_request message) override;
};

inline void PromotionCrudSet::Get(web::http::http_request message) 
{
    try {

    }
    catch(const std::exception& e) {

    }
}

inline void PromotionCrudSet::Post(web::http::http_request message) 
{
    try {

    }
    catch(const std::exception& e) {

    }
}

inline void PromotionCrudSet::Put(web::http::http_request message) 
{
    try {

    }
    catch(const std::exception& e) {

    }
}

inline void PromotionCrudSet::Delete(web::http::http_request message) 
{
    try {

    }
    catch(const std::exception& e) {

    }
}

#endif