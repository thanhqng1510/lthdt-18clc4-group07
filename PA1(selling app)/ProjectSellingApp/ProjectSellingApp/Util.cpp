#include "Util.h"

void getStringInput(std::string& input, std::function<bool(const std::string& value)> isValid) {
	while (!getline(std::cin, input, '\n') || (isValid != nullptr && !isValid(input))) {
		input.clear();
		if (!std::cin)
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Error, please try again: ";
	}
}

void promptMessage(const std::string& message) {
	std::cout << message << "\nPress any key to continue...";
	std::cin.get();
}
