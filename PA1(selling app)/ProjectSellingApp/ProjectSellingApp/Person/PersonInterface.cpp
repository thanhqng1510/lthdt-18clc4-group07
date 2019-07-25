#include <fstream>

#include "PersonInterface.h"
#include "../Utility/Util.h"

const std::string PersonInterface::s_customer_account_path = "ProjectSellingApp/Account/Data/CustomerAccount.data";
const std::string PersonInterface::s_seller_account_path = "ProjectSellingApp/Account/Data/SellerAccount.data";
const std::string PersonInterface::s_manager_account_path = "ProjectSellingApp/Account/Data/ManagerAccount.data";

PersonInterface::PersonInterface(const Account& account) : m_self_account(nullptr), m_self_account_path(account.m_type == ACCOUNT_TYPE::CUSTOMER ? &s_customer_account_path : account.m_type == ACCOUNT_TYPE::MANAGER ? &s_manager_account_path : &s_seller_account_path) { 
    file_to_unordered_map<std::string, Account>(*m_self_account_path, m_self_list, [&](std::pair<std::string, Account>& value, const std::string& line) -> void {
	    std::vector<std::string> result;
        parse_string (result, line, " ");
        value = { std::move(result[0]), 
                { std::move(result[0]), std::move(result[1]), std::move(result[2]), account.m_type }};
    });

    m_self_account = &m_self_list.at(account.m_username);
}

PersonInterface::~PersonInterface() {
    unordered_map_to_file<std::string, Account>(*m_self_account_path, m_self_list, [](const std::pair<std::string, Account>& value, std::string& line) {
        line = std::move(value.second.ToString());
    });
}

void PersonInterface::ChangeUsername() {
    std::string new_username;
    std::cout << "Enter new username: ";
	Account::GetUsernameInput;

    std::string cur_pass;
    std::cout << "Enter current password to confirm: ";
    Account::GetPasswordInput(cur_pass);
    if (cur_pass != m_self_account->m_pass) {
        prompt_message("Wrong password\n");
        return;
    }

    for (const auto& a : m_self_list)
        if (a.first == new_username) {
            prompt_message("This username has been used");
            return;
        }

    m_self_account->m_username = std::move(new_username);
    
    prompt_message("Change username successfully");
}

void PersonInterface::ChangePassword() {
    std::string new_pass, cur_pass;
    std::cout << "Enter new password: ";
    Account::GetPasswordInput(new_pass);
    std::cout << "Enter current password to confirm: ";
    Account::GetPasswordInput(cur_pass);

    if (cur_pass != m_self_account->m_pass) {
        prompt_message("Wrong password\n");
        return;
    }

    m_self_account->m_pass = new_pass;

    prompt_message("Change password successfully");
}

void PersonInterface::ChangeEmail() {
    std::string new_email;
    std::cout << "Enter new email: ";
    Account::GetEmailInput(new_email);

    std::string cur_pass;
    std::cout << "Enter current password to confirm: ";
    Account::GetPasswordInput(cur_pass);
    if (cur_pass != m_self_account->m_pass) {
        prompt_message("Wrong password\n");
        return;
    }

    for (const auto& a : m_self_list)
        if (a.second.m_email == new_email) {
            prompt_message("This email has been used");
            return;
        }

    m_self_account->m_email = std::move(new_email);

    prompt_message("Change email successfully");
}

void PersonInterface::LogOut() const {
	prompt_message("Goodbye");
}

void PersonInterface::DeleteAccount() {
    m_self_list.erase(m_self_account->m_username);
    m_self_account = nullptr;

    prompt_message("Account deleted\n");
    LogOut();
}