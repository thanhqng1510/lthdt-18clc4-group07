#include <iostream>
#include <regex>

#include "Account.h"
#include "../Utility/Util.h"

void Account::UpdatePassword() {
	std::string new_pass, pass;
	std::cout << "Enter new password: ";
	get_input<std::string>(new_pass, [](const std::string& value) -> bool {
		return std::regex_match(value, std::regex(s_pass_pattern));
	}, "Password must have at least 4 characters, please try again: ");

	std::cout << "Enter current password to confirm: ";
	get_input<std::string>(pass, [](const std::string& value) -> bool {
		return std::regex_match(value, std::regex(s_pass_pattern));
	}, "Password must have at least 4 characters, please try again: ");

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
