#pragma once

#include <string>

enum class ACCOUNT_TYPE {
	CUSTOMER = 0,
	MANAGER = 1,
	SELLER = 2
};

class Account {
public:
	static const std::string s_customer_account_path;
	static const std::string s_manager_account_path;
	static const std::string s_seller_account_path;

	static const std::string s_pass_pattern;
	static const std::string s_email_pattern;

private:
	std::string m_username, m_pass, m_email;
	ACCOUNT_TYPE m_type;

public:
	// Assume that all parameters are valid
	Account() = default;
	Account(const std::string& username, const std::string& pass, const std::string& email, ACCOUNT_TYPE type);

public:
	ACCOUNT_TYPE GetType() const;

	void UpdatePassword();
};