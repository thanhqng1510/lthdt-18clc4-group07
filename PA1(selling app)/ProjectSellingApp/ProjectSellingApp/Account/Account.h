#pragma once

#include <string>

enum class ACCOUNT_TYPE {
	CUSTOMER = 0,
	MANAGER,
	SELLER
};

class Account {
protected:
	std::string m_username, m_pass;
	ACCOUNT_TYPE m_type;

public:
	static std::string s_customer_account_path;
	static std::string s_manager_account_path;
	static std::string s_seller_account_path;

public:
	Account(const std::string& username, const std::string& pass, ACCOUNT_TYPE type);

public:
	void UpdatePassword();
};