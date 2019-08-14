#pragma once

#include <string>
#include <unordered_map>

#include "PersonInterface.h"
#include "../Account/Account.h"

class Seller : public PersonInterface {
protected:
    unsigned int m_menu_option;

public:
    static void GetOptionInput(unsigned int& option);

public:
    Seller(const Account& account);

public:
    void ShowMenu() override;
};