#pragma once

#include <string>

#include "Account.h"

class CustomerAccount : public Account {
protected:
	static std::string m_data_path;

public:
	CustomerAccount(const std::string& username, const std::string& pass);
	~CustomerAccount() = default;

public:
	bool UpdateInfo() override;
};
