#pragma once

#include <unordered_map>
#include <string>

#include "PersonInterface.h"
#include "../Account/Account.h"

class Manager : public PersonInterface {
private:
    std::unordered_map<std::string, Account> m_customer_list;
    std::unordered_map<std::string, Account> m_seller_list;
    unsigned int m_menu_option;

public:
    static void GetOptionInput(unsigned int& option);

public:
    Manager(const Account& account);
    ~Manager() override;

public:
    void CreateSeller();
    void DeleteSeller();
    void DeleteCustomer();
    void SyncWithFile() const override;
    void ShowMenu() override;
};