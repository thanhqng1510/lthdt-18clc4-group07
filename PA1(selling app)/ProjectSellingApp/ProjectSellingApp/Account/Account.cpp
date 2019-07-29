#include <iostream>
#include <regex>

#include "Account.h"
#include "../Utility/Util.h"

const std::string Account::s_pass_pattern = "([a-zA-Z0-9`~!@#$%^&*_<>?]{4,})";
const std::string Account::s_email_pattern = "([a-zA-Z0-9]+@[a-zA-Z0-9]+\.[a-zA-Z0-9]+)";
const std::string Account::s_username_pattern = "([a-zA-Z0-9_\.]{6,})";

void Account::GetUsernameInput(std::string& username) {
	get_input<std::string>(username ,[](const std::string& value) -> bool {
		return std::regex_match(value, std::regex(s_username_pattern));
	}, "Wrong username format or username less 6 characters, please try again : ");
}

void Account::GetPasswordInput(std::string& pass) {
	get_input<std::string>(pass, [](const std::string& value) -> bool {
		return std::regex_match(value, std::regex(s_pass_pattern));
	}, "Wrong password format or password less 4 characters, please try again : ");
}
	
void Account::GetEmailInput(std::string& email) {
	get_input<std::string>(email, [](const std::string& value) -> bool {
		return std::regex_match(value, std::regex(s_email_pattern));
	}, "Wrong email format, please try again : ");
}

Account::Account(const std::string& username, const std::string& pass, const std::string& email, ACCOUNT_TYPE type)
: m_username(username), m_pass(pass), m_email(email), m_type(type) {}

std::string Account::ToString() const {
	return m_username + " " + m_pass + " " + m_email;
}