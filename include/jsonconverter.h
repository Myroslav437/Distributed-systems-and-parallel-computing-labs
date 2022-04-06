#ifndef JSONCONVERTER_H_INCLUDED
#define JSONCONVERTER_H_INCLUDED

#include "cpprest/json.h"
#include "database.h"
#include <functional>

class JsonConverter
{
    static web::json::value promotionToJson(const Database::promotion_t& p);
    static web::json::value productsToJson(const Database::product_t& p);
    static web::json::value storeToJson(const Database::store_t& p);

    static Database::promotion_t JsonToPromotion(const web::json::value& val);
    static Database::product_t JsonToProduct(const web::json::value& val);
    static Database::store_t JsonToStore(const web::json::value& val);
};
#endif