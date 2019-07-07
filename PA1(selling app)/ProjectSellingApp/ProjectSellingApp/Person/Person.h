#pragma once

#include <string>

#include "../Account/Account.h"

class Person {
private:
	Account m_account;
	
public:
	Person(const Account& person);
	void UpdateInfo();
	void LogOut(Account person);



};
//cho doi usename voi email trong class account 
//xem co trung voi file.data 
//khong trung thi doi 
