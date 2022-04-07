#include"../include/database.h"

//Initialize static member variables
Database *Database::m_SingleInstance = nullptr;
std::mutex Database::m_Mutex;

Database *&Database::GetInstance()
{
    //  The technique of using two if judgement statements here is called double check lock; the advantage is that only when the judgement pointer is empty can it be locked.
    //  Avoid locking every time the GetInstance method is called. After all, the cost of locking is a little high.
    if (m_SingleInstance == nullptr) {
        std::unique_lock<std::mutex> lock(m_Mutex); // Lock up
        if (m_SingleInstance == nullptr) {
            m_SingleInstance = new (std::nothrow) Database;
        }
    }

    return m_SingleInstance;
}

void Database::deleteInstance()
{
    std::unique_lock<std::mutex> lock(m_Mutex); // Lock up
    if (m_SingleInstance)  {
        delete m_SingleInstance;
        m_SingleInstance = nullptr;
    }
}

Database::Database() 
{
    return;
}

Database::~Database() 
{
    return;
}
