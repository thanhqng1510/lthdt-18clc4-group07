#include <iostream>

#include "Account.h"
#include "../Util.h"

std::string Account::s_customer_account_path = "Account/Data/CustomerAccount.data";
std::string Account::s_manager_account_path = "Account/Data/ManagerAccount.data";
std::string Account::s_seller_account_path = "Account/Data/SellerAccount.data";

Account::Account(const std::string& username, const std::string& pass, ACCOUNT_TYPE type) : m_username(username), m_pass(pass), m_type(type) {}

void Account::UpdatePassword() {
	std::string new_pass, pass;
	std::cout << "Enter new password: ";
	getline(std::cin, new_pass, '\n');
	std::cout << "Enter current password to confirm: ";
	getline(std::cin, pass, '\n');

	if (pass != m_pass) {
		std::cout << "Wrong password\n";
		return;
	}
	if (new_pass == m_pass) {
		std::cout << "This is your current password\n";
		return;
	}
	m_pass = new_pass;
	std::cout << "Change password successfully\n";
}