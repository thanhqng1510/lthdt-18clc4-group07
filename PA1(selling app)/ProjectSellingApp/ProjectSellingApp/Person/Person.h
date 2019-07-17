#pragma once

#include <string>

#include "../Account/Account.h"
#include "../Utility/Util.h"

class Person {
protected:
	Account m_account;
	
public:
	inline Person(const Account& account) : m_account(account) {
	ACCOUNT_TYPE type = account.GetType();
	prompt_message((std::string)"Welcome " +
		((type == ACCOUNT_TYPE::CUSTOMER) ? (std::string)"customer" :
		(type == ACCOUNT_TYPE::MANAGER) ? (std::string)"manager" : (std::string)"seller"));
}
public:
	inline void UpdateInfo() {
		m_account.UpdatePassword();
	}

	inline void LogOut() const {
		prompt_message("Goodbye");
	}
};
//cho doi usename voi email trong class account 
//xem co trung voi file.data 
//khong trung thi doi 
