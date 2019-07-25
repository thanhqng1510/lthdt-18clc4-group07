#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

#include "MainMenu.h"
#include "../Utility/Util.h"
#include "../Account/Account.h"
#include "../Person/PersonInterface.h"


void MainMenu::LogIn(LOG_IN_KEY key) {
	std::string username, pass, email;

	if (key == LOG_IN_KEY::USERNAME) {
		std::cout << "Enter username: ";
		Account::GetUsernameInput(username);
	}
	else {
		std::cout << "Enter email: ";
		Account::GetEmailInput(email);
	}

	std::cout << "Enter password: ";
	Account::GetPasswordInput(pass);

	std::pair<std::string, ACCOUNT_TYPE> path[3] = {
		{ PersonInterface::s_customer_account_path, ACCOUNT_TYPE::CUSTOMER },  //Account p.first
		{ PersonInterface::s_manager_account_path, ACCOUNT_TYPE::MANAGER },    //ACCOUNT_TYPE p.second
		{ PersonInterface::s_seller_account_path, ACCOUNT_TYPE::SELLER }
	};

	for (const std::pair<std::string, ACCOUNT_TYPE>& p : path) {
		std::ifstream fin(p.first);
		if (!fin.is_open()) {
			prompt_message("Fail to open " + p.first + ".");
			continue;
		}

		std::string line;
		while (getline(fin, line, '\n')) {
			std::stringstream ss(line);
			std::string cur_username, cur_pass, cur_email;

			ss >> cur_username >> cur_pass >> cur_email;
			if ((key == LOG_IN_KEY::USERNAME && cur_username == username) || (key == LOG_IN_KEY::EMAIL && cur_email == email)) {
				if (cur_pass == pass) {
					prompt_message("Hello !!!");
					// Person person(Account(username, pass, email, p.second));
				}
				else {
					prompt_message("Wrong password.");
					fin.close();
					return;
				}
			}
		}
		fin.close();
	}

	prompt_message("Wrong username or email.");
}

void MainMenu::CreateAccount() {
	std::string username, pass, email;
	std::cout << "Enter username: ";
	Account::GetUsernameInput(username);
	
	std::cout << "Enter password: ";
	Account::GetPasswordInput(pass);

	std::cout << "Enter email: ";
	Account::GetEmailInput(email);

	std::ifstream fin(PersonInterface::s_customer_account_path);
	if (!fin.is_open()) {
		prompt_message("Fail to open " + PersonInterface::s_customer_account_path + ".");
		return;
	}

	std::string line;
	while (getline(fin, line, '\n')) {
		std::stringstream ss(std::move(line));
		std::string cur_username, cur_email;
		ss >> cur_username >> cur_email >> cur_email;

		if (cur_username == username) {
			prompt_message("This username has been used.");
			fin.close();
			return;
		}
		else if (cur_email == email) {
			prompt_message("This email has been used.");
			fin.close();
			return;
		}
	}
	fin.close();

	std::ofstream fout(PersonInterface::s_customer_account_path, std::ios::app);
	fout << "\n" << username << " " << pass << " " << email;
	fout.close();

	prompt_message("Account created successfully.");
}

void MainMenu::GetOptionInput(unsigned int& option) {
	get_input<unsigned int>(option, [](const unsigned int& value) -> bool {
		return value > 0 && value < 5;
	}, "Option must be between 1 and 4, please try again: ");
}

MainMenu::MainMenu()
: m_option(0) {}

void MainMenu::Show() {
	while (m_option != 4) {
		system("cls");
		system("clear");
		std::cout << "Welcome.\n";
		std::cout << "1. Log in with email.\n";
		std::cout << "2. Log in with username.\n";
		std::cout << "3. Create account (for customer only).\n";
		std::cout << "4. Exit.\n";

		std::cout << "Choose: ";
		GetOptionInput(m_option);

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
