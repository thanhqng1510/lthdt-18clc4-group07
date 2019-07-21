#pragma once

#include <unordered_map>
#include <string>

#include "Person.h"
#include "../Account/Account.h"

class Customer : public Person {
private:
    unsigned int m_point;
    //Bucket m_bucket;
    std::unordered_map <std::string, Account> m_list_customer;

public:
    Customer() = default;
    Customer(const Account& account);
    //~Customer();

public:
    //void DeleteAccount();
    //void SyncWithFile();
};