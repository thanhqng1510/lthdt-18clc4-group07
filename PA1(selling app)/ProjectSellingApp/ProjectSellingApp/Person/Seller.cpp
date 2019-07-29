#include <fstream>

#include "Seller.h"
#include "../Utility/Util.h"

void Seller::GetOptionInput(unsigned int& option) {
    get_input<unsigned int>(option, [](const unsigned int& value) -> bool {
		return value > 0 && value < 12;
	}, "Option must be between 1 and 11, please try again : ");
}

Seller::Seller(const Account& account)
:  PersonInterface(account), m_menu_option(0) {}

void Seller::ShowMenu() {
    while (m_menu_option != 11) {
		system("cls");
		system("clear");
		std::cout << "Welcome.\n"
				  << "------------------------\n"
		          << "1. Show info.\n"
		          << "2. Change username.\n"
		          << "3. Change password.\n"
		          << "4. Change email.\n"
                  << "5. Delete account.\n"
				  << "------------------------\n"
                  << "6. View book store.\n"
				  << "7. View book by name.\n"
				  << "8. View book by author.\n"
				  << "9. Add book.\n"
				  << "10. Remove book.\n"
				  << "------------------------\n"
				  << "11. Log out.\n";

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
			m_menu_option = 11;
            break;
        case 6:
            m_book_store.PrintAll();
            break;
		case 7:
			m_book_store.ViewByName();
			break;
		case 8:
			m_book_store.ViewByAuthor();
			break;
		case 9:
			m_book_store.Add();
			break;
		case 10:
			m_book_store.Remove();
			break;
		case 11:
			PersonInterface::LogOut();
			break;
		}
	}
}
