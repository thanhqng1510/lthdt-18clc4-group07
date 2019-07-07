#include <iostream>

#include "Account.h"
#include "../Util.h"

const std::string Account::s_customer_account_path = "Account/Data/CustomerAccount.data";
const std::string Account::s_manager_account_path = "Account/Data/ManagerAccount.data";
const std::string Account::s_seller_account_path = "Account/Data/SellerAccount.data";
const std::string Account::s_email_sample = "([a-zA-Z0-9_\.]+@[a-zA-Z]+(\.[a-zA-Z]+)+)";

Account::Account(const std::string& username, const std::string& pass, const std::string& email, ACCOUNT_TYPE type) 
	: m_username(username), m_pass(pass), m_email(email), m_type(type) {}

void Account::UpdatePassword() {
	std::string new_pass, pass;
	std::cout << "Enter new password: ";
	getline(std::cin, new_pass, '\n');
	std::cout << "Enter current password to confirm: ";
	getline(std::cin, pass, '\n');
	//them regex cua password  
	//regex password khoong dcuoc co khoang trang 
	if (pass != m_pass) {
		promptMessage("Wrong password");
		return;
	}
	if (new_pass == m_pass) {
		promptMessage("This is your current password");
		return;
	}
	m_pass = new_pass;
	promptMessage("Change password successfully");
}