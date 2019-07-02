#include <iostream>

#include "Account.h"
#include "../Util.h"

std::string Account::s_customer_account_path = "Account/Data/CustomerAccount.data";
std::string Account::s_manager_account_path = "Account/Data/ManagerAccount.data";
std::string Account::s_seller_account_path = "Account/Data/SellerAccount.data";

void Account::UpdateUsername() {
	std::string new_username, temp_pass;
	std::cout << "Enter new username: ";
	getline(std::cin, new_username, '\n');
	std::cout << "Enter current password to confirm: ";
	getline(std::cin, temp_pass, '\n');

	if (temp_pass != m_pass) {
		std::cout << "Wrong password\n";
		return;
	}
	if (new_username == m_username) {
		std::cout << "This is your current username\n";
		return;
	}
	m_username = new_username;
	std::cout << "Change username successfully\n";
}

void Account::UpdatePassword() {
	std::string new_pass, temp_pass;
	std::cout << "Enter new password: ";
	getline(std::cin, new_pass, '\n');
	std::cout << "Enter current password to confirm: ";
	getline(std::cin, temp_pass, '\n');

	if (temp_pass != m_pass) {
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

Account::Account(const std::string& username, const std::string& pass) : m_username(username), m_pass(pass) {}

void Account::UpdateInfo() {
	unsigned int option = 0;
	while (option != 3) {
		std::cout << "1. Change username\n";
		std::cout << "2. Change password\n";
		std::cout << "3. Exit\n";

		std::cout << "Choose: ";
		getOptionInput<unsigned int>(option, [](const unsigned int& value) {
			return value > 0 && value < 4;
			});

		switch (option) {
		case 1:
			UpdateUsername();
			break;
		case 2:
			UpdatePassword();
			break;
		case 3:
			return;
		}
	}
}