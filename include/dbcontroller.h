#ifndef DBCONTROLLER_H_INCLUDED
#define DBCONTROLLER_H_INCLUDED

#include "database.h"
#include <mutex>
#include <list>
#include <functional>

class Dbcontroller
{
public:
    std::list<
        std::pair<int, std::reference_wrapper<Database::promotion_t>>> 
    getPromotions();

    std::list<
        std::pair<int, std::reference_wrapper<Database::product_t>>> 
    getProducts();

    std::list<
        std::pair<int, std::reference_wrapper<Database::store_t>>> 
    getStores();

    std::pair<int, std::reference_wrapper<Database::promotion_t>> getPromotion(int id);
    std::pair<int, std::reference_wrapper<Database::product_t>> getProduct(int id);
    std::pair<int, std::reference_wrapper<Database::store_t>> getStore(int id);

    void removePromotion(int id);
    void removeProduct(int id);
    void removeStore(int id);

    void addPromotion(Database::promotion_t promotion);
    void addProduct(Database::product_t product);
    void addStore(Database::store_t store);

    // Getting a single instance object
    static Dbcontroller *&GetInstance();
    //Release single instance and call when process exits
    static void deleteInstance();

private:
    // Construct and analyze it as private, prohibit external structure and Deconstruction
    Dbcontroller();
    ~Dbcontroller();

    // Construct its copy construction and assignment into private functions, forbid external copy and assignment
    Dbcontroller(const Dbcontroller &signal);
    const Dbcontroller &operator=(const Dbcontroller &signal);
private:
    // Unique single instance object pointer
    static Dbcontroller *m_SingleInstance;
    static std::mutex m_Mutex;

    std::mutex PromotionMt;
    std::mutex ProductMt;
    std::mutex StoreMt;
};

#endif