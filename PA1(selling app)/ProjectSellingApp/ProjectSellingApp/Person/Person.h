#pragma once

#include <string>

#include "../Account/Account.h"

class Person {
private:
	Account m_account;
	std::string m_email;

public:
	static std::string s_email_sample;
};

