#include "../include/jsonconverter.h"

web::json::value JsonConverter::promotionToJson(const Database::promotion_t& p) 
{
    // // <promotionDescription, promotionValidFrom, promotionValidUntill>:
    // using promotion_t = std::tuple<std::string, std::string, std::string>;

    web::json::value val;
    val["promotionDescription"] = web::json::value::string(std::get<0>(p));
    val["promotionValidFrom"] = web::json::value::string(std::get<1>(p));
    val["promotionValidUntill"] = web::json::value::string(std::get<2>(p));

    return val;
}

web::json::value JsonConverter::productsToJson(const Database::product_t& p) 
{
    // // <productPrice, productName, productManufacturer>:
    // using product_t = std::tuple<float, std::string,std::string>;

    web::json::value val;
    val["productPrice"] = web::json::value::number(std::get<0>(p));
    val["productName"] = web::json::value::string(std::get<1>(p));
    val["productManufacturer"] = web::json::value::string(std::get<2>(p));

    return val;
}

web::json::value JsonConverter::storeToJson(const Database::store_t& p) 
{
    // // <storeAddress, storeManagerEmail, storeManagerPhone>:
    // using store_t = std::tuple<std::string, std::string, std::string>;

    web::json::value val;
    val["storeAddress"] = web::json::value::string(std::get<0>(p));
    val["storeManagerEmail"] = web::json::value::string(std::get<1>(p));
    val["storeManagerPhone"] = web::json::value::string(std::get<2>(p));

    return val;
}

Database::promotion_t JsonConverter::JsonToPromotion(const web::json::value& val) 
{
    // // <promotionDescription, promotionValidFrom, promotionValidUntill>:
    // using promotion_t = std::tuple<std::string, std::string, std::string>;
    std::string promotionDescription = val.at(U("promotionDescription")).as_string();
    std::string promotionValidFrom = val.at(U("promotionValidFrom")).as_string();
    std::string promotionValidUntill = val.at(U("promotionValidUntill")).as_string();

    return Database::promotion_t(promotionDescription, promotionValidFrom, promotionValidUntill);
}

Database::product_t JsonConverter::JsonToProduct(const web::json::value& val) 
{
    // // <productPrice, productName, productManufacturer>:
    // using product_t = std::tuple<float, std::string,std::string>;

    float productPrice = val.at(U("productPrice")).as_double();
    std::string productName = val.at(U("productName")).as_string();
    std::string productManufacturer = val.at(U("productManufacturer")).as_string();

    return Database::product_t(productPrice, productName, productManufacturer);

}
Database::store_t JsonConverter::JsonToStore(const web::json::value& val)
{
    // // <storeAddress, storeManagerEmail, storeManagerPhone>:
    // using store_t = std::tuple<std::string, std::string, std::string>

    std::string storeAddress = val.at(U("storeAddress")).as_string();
    std::string storeManagerEmail = val.at(U("storeManagerEmail")).as_string();
    std::string storeManagerPhone = val.at(U("storeManagerPhone")).as_string();

    return Database::promotion_t(storeAddress, storeManagerEmail, storeManagerPhone);
}