#pragma once

#include <string>
#include <unordered_map>

#include "PersonInterface.h"
#include "../Account/Account.h"

class Seller : public PersonInterface {
public:
    Seller(const Account& account);
};