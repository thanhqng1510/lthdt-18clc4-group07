#include <fstream>
#include <regex>

#include "Manager.h"
#include "Customer.h"
#include "Seller.h"
#include "../Utility/Util.h"

Manager::Manager(const Account& account)
: PersonInterface(account) {
	file_to_unordered_map<std::string, Account>(PersonInterface::s_customer_account_path, m_customer_list, [](std::pair<std::string, Account>& value, const std::string& line) {
	    std::vector<std::string> result;
        parse_string (result, line, " ");
        value = { result[0], 
                { result[0], result[1], result[2], ACCOUNT_TYPE::CUSTOMER }};
    });

    file_to_unordered_map<std::string, Account>(PersonInterface::s_seller_account_path, m_seller_list, [](std::pair<std::string, Account>& value, const std::string& line) {
	    std::vector<std::string> result;
        parse_string (result, line, " ");
        value = { result[0], 
                { result[0], result[1], result[2], ACCOUNT_TYPE::SELLER }};
    });
}

Manager::~Manager() {
	SyncWithFile();
}

void Manager::CreateSeller() {
    std::string username, pass, email;
	std::cout << "Enter username: ";
    Account::GetUsernameInput(username);

	std::cout << "Enter password: ";
	Account::GetPasswordInput(pass);

	std::cout << "Enter email: ";
	Account::GetEmailInput(email);

    for (const auto& i : m_seller_list) {
        if (i.first == username) {
			prompt_message("This username has been used.");
			return;
		}

		if (i.second.m_email == email) {
			prompt_message("This email has been used.");
			return;
		}
    }

    m_seller_list.insert({ username, { username, pass, email, ACCOUNT_TYPE::SELLER } });

    prompt_message("Seller " + username + " created successfully.");
}

void Manager::DeleteSeller(const std::string& name) {
    m_seller_list.erase(name);

    prompt_message("Seller " + name + " deleted successfully.");
}

void Manager::DeleteCustomer(const std::string& name) {
    m_customer_list.erase(name);

    prompt_message("Customer " + name + " deleted successfully.");
}

void Manager::SyncWithFile() const {
    unordered_map_to_file<std::string, Account>(PersonInterface::s_customer_account_path, m_customer_list, [](const std::pair<std::string, Account>& value, std::string& line) {
        line = value.second.ToString();
    });

	unordered_map_to_file<std::string, Account>(PersonInterface::s_seller_account_path, m_seller_list, [](const std::pair<std::string, Account>& value, std::string& line) {
        line = value.second.ToString();
    });
}