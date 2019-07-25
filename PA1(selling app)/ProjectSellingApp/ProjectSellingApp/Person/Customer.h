#pragma once

#include <unordered_map>
#include <string>

#include "PersonInterface.h"
#include "../Account/Account.h"
#include "../Account/Bucket/Bucket.h"

class Customer : public PersonInterface {
private:
    unsigned int m_point;
    Bucket m_bucket;
	//unordered_map<string, Account> m_list_customer;
	//static string s_customer_account_path;
	//personInterface
public:
    Customer(const Account& account);
    //~Customer() override;
	//deleteAccount -> personInterface
	//void SyncWithFile();
	void BucketCustomer();
};