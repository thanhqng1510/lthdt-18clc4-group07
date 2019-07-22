#include <vector>

#include "Customer.h"
#include "../Utility/Util.h"

Customer::Customer(const Account& account) 
: PersonInterface(account), m_point(0) {
    //file_to_unordered_map<std::string, Account>(s_customer_account_path, m_list_customer, PersonInterface::m_line_to_pair);
}

//  Customer::~Customer()

//  void DeleteAccount();
//  void SyncWithFile();
        