#pragma once

#include <string>

enum class ACCOUNT_TYPE {
	CUSTOMER = 0,
	MANAGER = 1,
	SELLER = 2
};

class Account {
public:
	friend class PersonInterface;
	friend class Manager;
	friend class Customer;

	static const std::string s_pass_pattern;
	static const std::string s_email_pattern; 

public:
	static void GetUsernameInput(std::string& username);
	static void GetPasswordInput(std::string& pass);
	static void GetEmailInput(std::string& email);

private:
	std::string m_username, m_pass, m_email;
	ACCOUNT_TYPE m_type;

public:
	// Assume that all parameters are valid
	Account() = default;
	Account(const std::string& username, const std::string& pass, const std::string& email, ACCOUNT_TYPE type);

public:
	std::string ToString() const;
};