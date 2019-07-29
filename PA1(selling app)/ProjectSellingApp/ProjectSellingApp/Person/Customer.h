#pragma once

#include <unordered_map>
#include <string>

#include "PersonInterface.h"
#include "../Account/Account.h"
#include "../Account/Bucket/Bucket.h"

class Customer : public PersonInterface {
private:
    Bucket m_bucket;
	unsigned int m_menu_option;

public:
    static void GetOptionInput(unsigned int& option);

public:
    Customer(const Account& account);
    ~Customer() override = default;

public:
	void ShowMenu() override;
};