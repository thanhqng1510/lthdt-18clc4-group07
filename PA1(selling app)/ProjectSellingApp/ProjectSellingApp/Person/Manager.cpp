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
        value = { std::move(result[0]), 
                { std::move(result[0]), std::move(result[1]), std::move(result[2]), ACCOUNT_TYPE::CUSTOMER }};
    });

    file_to_unordered_map<std::string, Account>(PersonInterface::s_seller_account_path, m_seller_list, [](std::pair<std::string, Account>& value, const std::string& line) {
	    std::vector<std::string> result;
        parse_string (result, line, " ");
        value = { std::move(result[0]), 
                { std::move(result[0]), std::move(result[1]), std::move(result[2]), ACCOUNT_TYPE::SELLER }};
    });
}

Manager::~Manager() {
	unordered_map_to_file<std::string, Account>(PersonInterface::s_customer_account_path, m_customer_list, [](const std::pair<std::string, Account>& value, std::string& line) {
        line = std::move(value.second.ToString());
    });

	unordered_map_to_file<std::string, Account>(PersonInterface::s_seller_account_path, m_seller_list, [](const std::pair<std::string, Account>& value, std::string& line) {
        line = std::move(value.second.ToString());
    });
}

void Manager::CreateSeller() {
    std::string username, pass, email;
	std::cout << "Enter username: ";
	get_input<std::string>(username, nullptr, "Please try again: ");

	std::cout << "Enter password: ";
	Account::GetPasswordInput(pass);

	std::cout << "Enter email: ";
	Account::GetEmailInput(email);

    for (const auto& i : m_seller_list) {
        if (i.first == username) {
			prompt_message("This username has been used");
			return;
		}
		else if (i.second.m_email == email) {
			prompt_message("This email has been used");
			return;
		}
    }

    m_seller_list.insert({ username, { username, pass, email, ACCOUNT_TYPE::SELLER } });
}

void Manager::DeleteSeller(const std::string& name) {
    m_seller_list.erase(std::move(name));
}

void Manager::DeleteCustomer(const std::string& name) {
    m_customer_list.erase(std::move(name));
}