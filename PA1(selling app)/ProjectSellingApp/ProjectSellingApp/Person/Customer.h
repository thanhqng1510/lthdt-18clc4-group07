#pragma once

#include <unordered_map>
#include <string>

#include "PersonInterface.h"
#include "../Account/Account.h"

class Customer : public PersonInterface {
private:
    unsigned int m_point;
    //Bucket m_bucket;

public:
    Customer(const Account& account);
    //~Customer() override;
};