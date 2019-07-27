#pragma once

#include <unordered_map>
#include <string>
#include <functional>

#include "../BookStore/BookStore.h"
#include "../Account/Account.h"

class PersonInterface : public BookStore {
public:
    static const std::string s_customer_account_path;
	static const std::string s_seller_account_path;
	static const std::string s_manager_account_path;

protected:
	Account* m_self_account;
	const std::string* const m_self_account_path;
	std::unordered_map<std::string, Account> m_self_list;

public:
	BookStore m_book_store;

public:
	PersonInterface(const Account& account);
	virtual ~PersonInterface();

public:
	void ShowInfo() const;
	void ChangeUsername();
	void ChangePassword();
	void ChangeEmail();
	void LogOut() const;
	void DeleteAccount();
	virtual void SyncWithFile() const;
	virtual void ShowMenu() = 0;
};