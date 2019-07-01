#include "CustomerAccount.h"

std::string CustomerAccount::m_data_path = "Account/Data/CustomerAccount.data";

CustomerAccount::CustomerAccount(const std::string& username, const std::string& pass) : Account(username, pass) {}

bool CustomerAccount::UpdateInfo() {
	return true;
}