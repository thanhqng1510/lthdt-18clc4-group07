#include "Util.h"

void get_string_input(std::string& input, std::function<bool(const std::string& value)> is_valid, const std::string& error_message) {
	while (!getline(std::cin, input, '\n') || (is_valid != nullptr && !is_valid(input))) {
		input.clear();
		if (!std::cin)
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << error_message;
	}
}

void prompt_message(const std::string& message) {
	std::cout << message << "\nPress any key to continue...";
	std::cin.get();
}