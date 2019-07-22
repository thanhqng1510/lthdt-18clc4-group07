#pragma once

#include <unordered_map>
#include <string>

#include "PersonInterface.h"
#include "../Account/Account.h"

class Manager : public PersonInterface {
private:
    std::unordered_map<std::string, Account> m_customer_list;
    std::unordered_map<std::string, Account> m_seller_list;

public:
    Manager(const Account& account);
    ~Manager() override;

public:
    void CreateSeller();
    void DeleteSeller(const std::string& name);
    void DeleteCustomer(const std::string& name);
};