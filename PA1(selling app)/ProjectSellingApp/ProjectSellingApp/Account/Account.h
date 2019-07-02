#pragma once

#include <string>

class Account {
protected:
	std::string m_username, m_pass;

public:
	static std::string s_customer_account_path;
	static std::string s_manager_account_path;
	static std::string s_seller_account_path;

protected:
	void UpdateUsername();
	void UpdatePassword();

public:
	Account(const std::string& username, const std::string& pass);

public:
	// Change username and password
	void UpdateInfo();
};