#include "Person.h"
#include "../Utility/Util.h"

Person::Person(const Account& account) 
: m_account(account) {
	ACCOUNT_TYPE type = account.GetType();
	prompt_message((std::string)"Welcome " +
		((type == ACCOUNT_TYPE::CUSTOMER) ? (std::string)"customer" :
		(type == ACCOUNT_TYPE::MANAGER) ? (std::string)"manager" : (std::string)"seller"));
}

void Person::UpdateInfo() {
	m_account.UpdatePassword();
}

void Person::LogOut() const {
	prompt_message("Goodbye");
}