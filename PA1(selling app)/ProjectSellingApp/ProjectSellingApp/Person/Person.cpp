#include "Person.h"
#include "../Util.h"
Person::Person(const Account& person) : m_account(person) {
	ACCOUNT_TYPE test = m_account.GetType();
	promptMessage("Welcome " + (test == ACCOUNT_TYPE::CUSTOMER) ? "customer" : (test == ACCOUNT_TYPE::MANAGER) ? "manager" : "seller");
}

void Person::UpdateInfo() {
	 m_account.UpdatePassword();
}

void Person::LogOut(Account person) {
	promptMessage("Goodbye");
}
