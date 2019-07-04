#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

#include "MainMenu.h"
#include "../Util.h"
#include "../Account/Account.h"

void MainMenu::LogIn(LOG_IN_KEY key) {
	std::string username, pass, email;

	if (key == LOG_IN_KEY::USERNAME) {
		std::cout << "Enter username: ";
		getStringInput(username, nullptr);
	}
	else {
		std::cout << "Enter email: ";
		getStringInput(email, [](const std::string& value) {
			return std::regex_match(value, std::regex(Account::s_email_sample));
			});
	}
	std::cout << "Enter password: ";
	getStringInput(pass, nullptr);

	std::pair<std::string, ACCOUNT_TYPE> path[3] = {
		{ Account::s_customer_account_path, ACCOUNT_TYPE::CUSTOMER },
		{ Account::s_manager_account_path, ACCOUNT_TYPE::MANAGER },
		{ Account::s_seller_account_path, ACCOUNT_TYPE::SELLER }
	};

	for (const std::pair<std::string, ACCOUNT_TYPE>& p : path) {
		std::ifstream fin(p.first);
		if (!fin.is_open()) {
			promptMessage("Fail to open " + p.first);
			continue;
		}
		std::string line;
		while (getline(fin, line, '\n')) {
			std::stringstream ss(std::move(line));
			std::string cur_username, cur_pass, cur_email;
			ss >> cur_username >> cur_pass >> cur_email;
			if ((key == LOG_IN_KEY::USERNAME && cur_username == username) || (key == LOG_IN_KEY::EMAIL && cur_email == email)) {
				if (cur_pass == pass) {
					promptMessage("Hello");
				}
				else {
					promptMessage("Wrong password");
					fin.close();
					return;
				}
			}
		}
		fin.close();
	}

	promptMessage("Wrong username or email");
}

void MainMenu::CreateAccount() {
	std::string username, pass, email;
	std::cout << "Enter username: ";
	getStringInput(username, nullptr);
	std::cout << "Enter password: ";
	getStringInput(pass, nullptr);
	std::cout << "Enter email: ";
	getStringInput(email, [](const std::string& value) {
		return std::regex_match(value, std::regex(Account::s_email_sample));
		});

	std::ifstream fin("Account/Data/CustomerAccount.data");
	if (!fin.is_open()) {
		promptMessage("Fail to open CustomerAccount.data");
		return;
	}
	std::string line;
	while (getline(fin, line, '\n')) {
		std::stringstream ss(std::move(line));
		std::string cur_username, cur_email;
		ss >> cur_username >> cur_email >> cur_email;
		if (cur_username == username) {
			promptMessage("This username has been used");
			fin.close();
			return;
		}
		else if (cur_email == email) {
			promptMessage("This email has been used");
			fin.close();
			return;
		}
	}
	fin.close();

	std::ofstream fout("Account/Data/CustomerAccount.data", std::ios::app);
	fout << "\n" << username << " " << pass << " " << email;
	fout.close();

	promptMessage("Account created successfully");
}

MainMenu::MainMenu() : m_option(0) {}

void MainMenu::Process() {
	while (m_option != 3) {
		system("cls");
		std::cout << "Welcome\n";
		std::cout << "1. Log in with email\n";
		std::cout << "2. Log in with username\n";
		std::cout << "3. Create account (for customer only)\n";
		std::cout << "4. Exit\n";

		std::cout << "Choose: ";
		getOptionInput<unsigned int>(m_option, [](const unsigned int& value) {
			return value > 0 && value < 5;
			});

		switch (m_option) {
		case 1:
			LogIn(LOG_IN_KEY::EMAIL);
			break;
		case 2:
			LogIn(LOG_IN_KEY::USERNAME);
			break;
		case 3:
			CreateAccount();
			break;
		case 4:
			return;
		}
	}
}