#include "Person.h"

Person::Person(const Account& person) : m_account(person) {
	ACCOUNT_TYPE type = m_account.GetType();
	promptMessage("Welcome " + (type == ACCOUNT_TYPE::CUSTOMER) ? "customer" : (type == ACCOUNT_TYPE::MANAGER) ? "manager" : "seller");
}