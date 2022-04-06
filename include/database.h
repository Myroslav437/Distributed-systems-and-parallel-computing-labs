#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <map>
#include <tuple>
#include <string>
#include <mutex>

class Database
{
public:
    // <promotionDescription, promotionValidFrom, promotionValidUntill>:
    using promotion_t = std::tuple<std::string, std::string, std::string>;
    // <storeAddress, storeManagerEmail, storeManagerPhone>:
    using store_t = std::tuple<std::string, std::string, std::string>;
    // <productPrice, productName, productManufacturer>:
    using product_t = std::tuple<float, std::string,std::string>;

    // promotions: promotionID, promotion_t:
    std::map<int, promotion_t> promotions;
    // stores: storeID, store_t:
    std::map<int, store_t> stores;
    // products: productID, product_t: 
    std::map<int, product_t> products;

    // Getting a single instance object
    static Database *&GetInstance();
    //Release single instance and call when process exits
    static void deleteInstance();

private:
    // Construct and analyze it as private, prohibit external structure and Deconstruction
    Database();
    ~Database();

    // Construct its copy construction and assignment into private functions, forbid external copy and assignment
    Database(const Database &signal);
    const Database &operator=(const Database &signal);

private:
    // Unique single instance object pointer
    static Database *m_SingleInstance;
    static std::mutex m_Mutex;
};
#endif