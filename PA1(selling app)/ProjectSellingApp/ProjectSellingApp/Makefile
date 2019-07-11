build=clang++ -Wall -std=c++17

Output: Main.o Util.o Person.o MainMenu.o BookStore.o Account.o
	$(build) $? -o Output

Main.o: Main.cpp Menu/MainMenu.cpp
	$(build) -c $?

Util.o: Utility/Util.h Utility/Util.cpp
	$(build) -c $?

Person.o: Person/Person.h Person/Person.cpp
	$(build) -c $?

MainMenu.o: Menu/MainMenu.h Menu/MainMenu.cpp
	$(build) -c $?

BookStore.o: BookStore/BookStore.h BookStore/BookStore.cpp
	$(build) -c $?

Account.o: Account/Account.h Account/Account.cpp
	$(build) -c $?

clear:
	rm *.o
	rm Utility/*.h.gch
	rm Person/*.h.gch
	rm Menu/*.h.gch
	rm BookStore/*.h.gch
	rm Account/*.h.gch
