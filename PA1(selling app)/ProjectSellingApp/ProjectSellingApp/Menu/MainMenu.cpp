#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "MainMenu.h"
#include "../Util.h"
#include "../Account/Account.h"

void MainMenu::LogIn() {
	std::string username, pass;
	std::cout << "Enter username: ";
	getStringInput(username, nullptr);
	std::cout << "Enter password: ";
	getStringInput(pass, nullptr);

	std::pair<std::string, ACCOUNT_TYPE> path[3] = {
		{ Account::s_customer_account_path, ACCOUNT_TYPE::CUSTOMER },
		{ Account::s_manager_account_path, ACCOUNT_TYPE::MANAGER },
		{ Account::s_seller_account_path, ACCOUNT_TYPE::SELLER } 
	};
	for (const std::pair<std::string, ACCOUNT_TYPE>& s : path) {
		std::ifstream fin(s.first);
		if (!fin.is_open())
			std::cout << "Fail to open " << s.first << "\n";
		std::string line;
		while (getline(fin, line, '\n')) {
			std::stringstream ss(line);
			std::string word;
			ss >> word;
			if (word == username) {
				ss >> word;
				if (word == pass) {

				}
				else {
					std::cout << "Wrong password\n";
					fin.close();
					return;
				}
			}
		}
		fin.close();
	}

	std::cout << "Wrong username\n";
}

void MainMenu::CreateAccount() {
	std::string username, pass;
	std::cout << "Enter username: ";
	getStringInput(username, nullptr);
	std::cout << "Enter password: ";
	getStringInput(pass, nullptr);

	std::ifstream fin("Account/Data/CustomerAccount.data");
	if (!fin.is_open()) {
		std::cout << "Fail to open CustomerAccount.data\n";
		return;
	}
	std::string line;
	while (getline(fin, line, '\n')) {
		std::stringstream ss(line);
		std::string word;
		ss >> word;
		if (word == username) {
			std::cout << "This username has been used\n";
			fin.close();
			return;
		}
	}
	fin.close();

	std::ofstream fout("Account/Data/CustomerAccount.data", std::ios::app);
	fout << "\n" << username << " " << pass;
	fout.close();
}

MainMenu::MainMenu() : m_option(0) {}

void MainMenu::Process() {
	while (m_option != 3) {
		std::cout << "Welcome\n";
		std::cout << "1. Log in\n";
		std::cout << "2. Create account (for customer only)\n";
		std::cout << "3. Exit\n";

		std::cout << "Choose: ";
		getOptionInput<unsigned int>(m_option, [](const unsigned int& value) {
			return value > 0 && value < 4;
			});

		switch (m_option) {
		case 1:
			LogIn();
			break;
		case 2:
			CreateAccount();
			break;
		case 3:
			return;
		}
	}
}