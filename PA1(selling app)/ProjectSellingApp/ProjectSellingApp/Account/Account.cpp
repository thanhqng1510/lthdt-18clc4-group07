#include <iostream>
#include <regex>

#include "Account.h"
#include "../Util.h"

const std::string Account::s_customer_account_path = "Account/Data/CustomerAccount.data";
const std::string Account::s_manager_account_path = "Account/Data/ManagerAccount.data";
const std::string Account::s_seller_account_path = "Account/Data/SellerAccount.data";
const std::string Account::s_pass_sample = "([a-zA-Z0-9!@#$%^&*<>?]{8,})";
const std::string Account::s_email_sample = "([a-zA-Z0-9_\.]+@[a-zA-Z]+(\.[a-zA-Z]+)+)";

void Account::UpdatePassword() {
	std::string new_pass, pass;
	std::cout << "Enter new password: ";
	get_input<std::string>(new_pass, [](const std::string& value) {
		return std::regex_match(value, std::regex(s_pass_sample));
		}, "Password must have at least 8 characters, please try again: ");	
	std::cout << "Enter current password to confirm: ";
	get_input<std::string>(pass, [](const std::string& value) {
		return std::regex_match(value, std::regex(s_pass_sample));
		}, "Password must have at least 8 characters, please try again: ");
	
	if (pass != m_pass) {
		prompt_message("Wrong password");
		return;
	}
	if (new_pass == m_pass) {
		prompt_message("This is your current password");
		return;
	}
	m_pass = new_pass;
	prompt_message("Change password successfully");
}