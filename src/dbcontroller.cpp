#include "../include/dbcontroller.h"
#include <exception>
#include <stdlib.h>

//Initialize static member variables
Dbcontroller *Dbcontroller::m_SingleInstance = nullptr;
std::mutex Dbcontroller::m_Mutex;

Dbcontroller *&Dbcontroller::GetInstance()
{
    //  The technique of using two if judgement statements here is called double check lock; the advantage is that only when the judgement pointer is empty can it be locked.
    //  Avoid locking every time the GetInstance method is called. After all, the cost of locking is a little high.
    if (m_SingleInstance == NULL) {
        std::unique_lock<std::mutex> lock(m_Mutex); // Lock up
        if (m_SingleInstance == NULL) {
            m_SingleInstance = new (std::nothrow) Dbcontroller;
        }
    }

    return m_SingleInstance;
}

void Dbcontroller::deleteInstance()
{
    std::unique_lock<std::mutex> lock(m_Mutex); // Lock up
    if (m_SingleInstance)  {
        delete m_SingleInstance;
        m_SingleInstance = nullptr;
    }
}

std::pair<int, std::reference_wrapper<Database::promotion_t>> Dbcontroller::getPromotion(int id) {
    std::unique_lock<std::mutex> lock(PromotionMt);

    auto& promTable = Database::GetInstance()->promotions;
    auto it = promTable.find(id);
    if (it != promTable.end()) {
        // element found:
        return std::make_pair(id, std::reference_wrapper<Database::promotion_t>(it->second));
    }
    else {
        throw std::logic_error("Invalid id");
    }
}

std::pair<int, std::reference_wrapper<Database::product_t>> Dbcontroller::getProduct(int id) {
    std::unique_lock<std::mutex> lock(ProductMt);

    auto& prodTable = Database::GetInstance()->products;
    auto it = prodTable.find(id);
    if (it != prodTable.end()) {
        // element found:
        return std::make_pair(id, std::reference_wrapper<Database::product_t>(it->second));
    }
    else {
        throw std::logic_error("Invalid id");
    }
}

std::pair<int, std::reference_wrapper<Database::store_t>> Dbcontroller::getStore(int id) {
    std::unique_lock<std::mutex> lock(StoreMt);

    auto& storeTable = Database::GetInstance()->stores;
    auto it = storeTable.find(id);
    if (it != storeTable.end()) {
        // element found:
        return std::make_pair(id, std::reference_wrapper<Database::store_t>(it->second));
    }
    else {
        throw std::logic_error("Invalid id");
    }
}

void Dbcontroller::removePromotion(int id) {
    std::unique_lock<std::mutex> lock(PromotionMt);

    auto& promTable = Database::GetInstance()->promotions;
    auto it = promTable.find(id);
    if (it != promTable.end()) {
        // element found:
        promTable.erase (it);
    }
    else {
        throw std::logic_error("Invalid id");
    }
}

void Dbcontroller::removeProduct(int id) {
    std::unique_lock<std::mutex> lock(ProductMt);

    auto& prodTable = Database::GetInstance()->products;
    auto it = prodTable.find(id);
    if (it != prodTable.end()) {
        // element found:
         prodTable.erase (it);
    }
    else {
        throw std::logic_error("Invalid id");
    }
}

void Dbcontroller::removeStore(int id) {
    std::unique_lock<std::mutex> lock(StoreMt);

    auto& storeTable = Database::GetInstance()->stores;
    auto it = storeTable.find(id);
    if (it != storeTable.end()) {
        // element found:
        storeTable.erase (it);
    }
    else {
        throw std::logic_error("Invalid id");
    }
}

void Dbcontroller::addPromotion(Database::promotion_t promotion) {
    std::unique_lock<std::mutex> lock(PromotionMt);

    auto& promTable = Database::GetInstance()->promotions;
    int id;
    while(promTable.find(id = rand()) != promTable.end());
    promTable[id] = promotion;
}

void Dbcontroller::addProduct(Database::product_t product) {
    std::unique_lock<std::mutex> lock(ProductMt);

    auto& prodTable = Database::GetInstance()->products;
    int id;
    while(prodTable.find(id = rand()) != prodTable.end());
    prodTable[id] = product;
}

void Dbcontroller::addStore(Database::store_t store) {
    std::unique_lock<std::mutex> lock(StoreMt);

    auto& storeTable = Database::GetInstance()->stores;
    int id;
    while(storeTable.find(id = rand()) != storeTable.end());
    storeTable[id] = store;
}

std::list<
    std::pair<int, std::reference_wrapper<Database::promotion_t>>> 
Dbcontroller::getPromotions() 
{
    std::unique_lock<std::mutex> lock(PromotionMt);

    auto& promTable = Database::GetInstance()->promotions;
    std::list<std::pair<int, std::reference_wrapper<Database::promotion_t>>> li;
    for(auto& a : promTable) {
        li.push_back({a.first, a.second});
    }

    return li;
}

std::list<
    std::pair<int, std::reference_wrapper<Database::product_t>>> 
Dbcontroller::getProducts() 
{
    std::unique_lock<std::mutex> lock(ProductMt);

    auto& prodTable = Database::GetInstance()->products;
    std::list<std::pair<int, std::reference_wrapper<Database::product_t>>> li;
    for(auto& a : prodTable) {
        li.push_back({a.first, a.second});
    }

    return li;
}

std::list<
    std::pair<int, std::reference_wrapper<Database::store_t>>> 
Dbcontroller::getStores() 
{
    std::unique_lock<std::mutex> lock(StoreMt);

    auto& storeTable = Database::GetInstance()->stores;
    std::list<std::pair<int, std::reference_wrapper<Database::store_t>>> li;
    for(auto& a : storeTable) {
        li.push_back({a.first, a.second});
    }

    return li;
}