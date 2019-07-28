#include <fstream>
#include <regex>

#include "Manager.h"
#include "Customer.h"
#include "Seller.h"
#include "../Utility/Util.h"

void Manager::GetOptionInput(unsigned int& option) {
    get_input<unsigned int>(option, [](const unsigned int& value) -> bool {
		return value > 0 && value < 15;
	}, "Option must be between 1 and 14, please try again : ");
}

Manager::Manager(const Account& account)
: PersonInterface(account), m_menu_option(0) {
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
	std::cout << "Enter username : ";
    Account::GetUsernameInput(username);

	std::cout << "Enter password : ";
	Account::GetPasswordInput(pass);

	std::cout << "Enter email : ";
	Account::GetEmailInput(email);

    for (const auto& i : m_seller_list) {
        if (i.first == username) {
			prompt_message("This username has been used !!!");
			return;
		}

		if (i.second.m_email == email) {
			prompt_message("This email has been used !!!");
			return;
		}
    }

    m_seller_list.insert({ username, { username, pass, email, ACCOUNT_TYPE::SELLER } });

    prompt_message("Seller " + username + " created successfully !!!");
}

void Manager::DeleteSeller() {
    std::string name;
    std::cout << "Enter username : ";
    Account::GetUsernameInput(name);

    if (m_seller_list.find(name) != m_seller_list.end()) {
        m_seller_list.erase(name);
        prompt_message("Seller " + name + " deleted successfully !!!");
    }
    else
        prompt_message("Seller not found !!!");
}

void Manager::DeleteCustomer() {
    std::string name;
    std::cout << "Enter username : ";
    Account::GetUsernameInput(name);

    if (m_customer_list.find(name) != m_customer_list.end()) {
        m_customer_list.erase(name);
        prompt_message("Customer " + name + " deleted successfully !!!");
    }
    else
        prompt_message("Customer not found !!!");
}

void Manager::SyncWithFile() const {
    unordered_map_to_file<std::string, Account>(PersonInterface::s_customer_account_path, m_customer_list, [](const std::pair<std::string, Account>& value, std::string& line) {
        line = value.second.ToString();
    });

	unordered_map_to_file<std::string, Account>(PersonInterface::s_seller_account_path, m_seller_list, [](const std::pair<std::string, Account>& value, std::string& line) {
        line = value.second.ToString();
    });
}

void Manager::ShowMenu() {
    while (m_menu_option != 14) {
		system("cls");
		system("clear");
		std::cout << "Welcome.\n"
                  << "-----------------------\n"
		          << "1. Show info.\n"
		          << "2. Change username.\n"
		          << "3. Change password.\n"
		          << "4. Change email.\n"
                  << "5. Delete account.\n"
                  << "-----------------------\n"
                  << "6. Create seller\n"
                  << "7. Delete seller.\n"
                  << "8. Delete customer.\n"
                  << "-----------------------\n"
                  << "9. View book store.\n"
				  << "10. View book by name.\n"
				  << "11. View book by author.\n"
				  << "12. Add book.\n"
				  << "13. Remove book.\n"
				  << "-----------------------\n"
                  << "14. Log out.\n";

		std::cout << "Choose : ";
		GetOptionInput(m_menu_option);

		switch (m_menu_option) {
		case 1:
			PersonInterface::ShowInfo();
			break;
		case 2:
			PersonInterface::ChangeUsername();
			break;
		case 3:
			PersonInterface::ChangePassword();
			break;
		case 4:
            PersonInterface::ChangeEmail();
			break;
        case 5:
            PersonInterface::DeleteAccount();
            break;
        case 6:
            CreateSeller();
            break;
        case 7:
            DeleteSeller();
            break;
        case 8:
            DeleteCustomer();
            break;
        case 9: 
            BookStore::PrintAll();
            break;
        case 10:
            BookStore::ViewByName();
            break;
        case 11: 
            BookStore::ViewByAuthor();
            break;
        case 12:
            BookStore::Add();
            break;
        case 13:
            BookStore::Remove();
            break;
        case 14:
            PersonInterface::LogOut();
            break;
		}
	}
}