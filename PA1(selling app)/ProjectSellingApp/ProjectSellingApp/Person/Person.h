#pragma once

#include <string>

#include "../Account/Account.h"
#include "../Util.h"

class Person {
protected:
	Account m_account;
	
public:
	Person(const Account& person);

public:
	inline void UpdateInfo() {
		m_account.UpdatePassword();
	}

	inline void LogOut() {
		promptMessage("Goodbye");
	}
};
//cho doi usename voi email trong class account 
//xem co trung voi file.data 
//khong trung thi doi 
