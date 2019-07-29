#include <vector>

#include "Customer.h"
#include "../Utility/Util.h"

void Customer::GetOptionInput(unsigned int& option) {
	get_input<unsigned int>(option, [](const unsigned int& value) -> bool {
		return value > 0 && value < 11;
	}, "Option must be between 1 and 10, please try again : ");
}

Customer::Customer(const Account& account) 
: PersonInterface(account), m_bucket(account.m_username), m_menu_option(0) {}

void Customer::ShowMenu() {
	while (m_menu_option != 10){
		system("cls");
		system("clear");
		std::cout << "Welcom.\n"
				  << "------------------------\n"
				  << "1. Show info.\n"
		          << "2. Change username.\n"
		          << "3. Change password.\n"
		          << "4. Change email.\n"
                  << "5. Delete account.\n"
                  << "------------------------\n"
				  << "6.Print all bucket.\n"
				  << "7.Add book to bucket.\n"
				  << "8.Remove book in bucket.\n"
				  << "9.Buy all.\n"
				  << "------------------------\n"
                  << "10. Log out.\n";
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
			m_menu_option = 10;
            break;
        case 6:
			m_bucket.PrintAll();
            break;
        case 7:
			m_bucket.Add();
           break;
        case 8:
			m_bucket.Remove();
            break;
        case 9: 
            m_bucket.BuyAll();
            break;
        case 10:
            PersonInterface::LogOut();
            break;
		}
	}
}

  