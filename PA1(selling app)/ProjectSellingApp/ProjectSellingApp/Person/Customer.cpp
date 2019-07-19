#include <vector>

#include "Customer.hpp"
#include "../Utility/Util.h/"

void parse_line_customer(std::pair<std::string, Account>& value, std::string& line) {
    std::vector<std::string> result;
    parse_string (result, line, " ");
    value = { result[0], { result[0], result[1], result[2], ACCOUNT_TYPE::CUSTOMER } };
}

Customer::Customer(const Account& account) : Person(account), m_point(0) {
    file_to_unordered_map<std::string, Account>(Account::s_customer_account_path, m_list_customer,parse_line_customer);
}

//  Customer::~Customer(){

//  }

//  void DeleteAccount();
//  void SyncWithFile();
        