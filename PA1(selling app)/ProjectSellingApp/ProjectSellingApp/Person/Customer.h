#pragma once

#include <unordered_map>
#include <string>

#include "PersonInterface.h"
#include "../Account/Account.h"

class Customer : public PersonInterface {
private:
    unsigned int m_point;
    //Bucket m_bucket;
    std::unordered_map <std::string, Account> m_list_customer;

public:
    Customer(const Account& account);
    //~Customer() override;

public:
    //void SyncWithFile() const override;
    //void DeleteAccount() override;
};