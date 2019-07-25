//#include "Menu/MainMenu.h"
//#include "BookStore/BookStore.h"
#include "Person/Seller.h"

int main() {
	Account a_seller("seller1", "1234", "s1@s1.com", ACCOUNT_TYPE::SELLER);
	Seller seller(a_seller);
	//seller.ChangeUsername();
	//seller.ChangePassword();
	//BookStore book_store;
	//book_store.PrintAll();
	seller.m_book_store.SearchByAuthor();
	//seller.m_book_store.Add();
	seller.m_book_store.Remove();
	seller.m_book_store.PrintAll();
}
