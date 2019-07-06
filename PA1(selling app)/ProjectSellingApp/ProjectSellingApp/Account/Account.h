#pragma once

#include <string>

enum class ACCOUNT_TYPE {
	CUSTOMER = 0,
	MANAGER,
	SELLER
};

class Account {
private:
	std::string m_username, m_pass, m_email;
	ACCOUNT_TYPE m_type;

public:
	static const std::string s_customer_account_path;
	static const std::string s_manager_account_path;
	static const std::string s_seller_account_path;
	static const std::string s_email_sample;

public:
	// Assume that all parameters are valid
	Account(const std::string& username, const std::string& pass, const std::string& email, ACCOUNT_TYPE type);

public:
	void UpdatePassword();
};