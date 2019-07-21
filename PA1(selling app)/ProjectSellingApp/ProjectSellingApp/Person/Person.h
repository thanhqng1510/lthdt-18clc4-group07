#pragma once

#include "../Account/Account.h"

class Person {
protected:
	Account m_account;
	
public:
	Person() = default;
	Person(const Account& account);

public:
	void UpdateInfo();
	void LogOut() const;
};