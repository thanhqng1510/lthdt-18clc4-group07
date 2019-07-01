#pragma once

#include <string>

class Account {
protected:
	std::string m_username, m_pass;

public:
	Account(const std::string& username, const std::string& pass);
	virtual ~Account() = default;

public:
	virtual bool UpdateInfo() = 0;
};