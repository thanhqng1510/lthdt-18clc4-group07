#include "Person.h"

Person::Person(const Account& person) : m_account(person) {
	ACCOUNT_TYPE type = m_account.GetType();
	prompt_message((std::string)"Welcome " +
		((type == ACCOUNT_TYPE::CUSTOMER) ? (std::string)"customer" :
		(type == ACCOUNT_TYPE::MANAGER) ? (std::string)"manager" : (std::string)"seller"));
}
