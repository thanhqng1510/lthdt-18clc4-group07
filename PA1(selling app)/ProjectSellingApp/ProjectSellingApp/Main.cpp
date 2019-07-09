#include "Menu/MainMenu.h"
#include "Util.h"

#include "BookStore/BookStore.h"

int main() {
	BookStore a;
	a.PrintAll();
	a.Remove();
	a.PrintAll();
	std::cin.get();

	/*MainMenu main_menu;
	main_menu.Process();*/
}