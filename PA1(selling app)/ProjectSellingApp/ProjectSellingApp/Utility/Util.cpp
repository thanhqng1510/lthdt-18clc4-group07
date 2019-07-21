#include "Util.h"

void prompt_message(const std::string& message) {
	std::cout << message << "\nPress any key to continue...";
	std::cin.get();
}

void get_line_input(std::string& input, std::function<bool(const std::string& value)> is_valid, const std::string& error_message) {
	while (!getline(std::cin, input, '\n') || (is_valid != nullptr && !is_valid(input))) {
		input.clear();
		if (!std::cin)
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << error_message;
	}
}

void parse_string(std::vector<std::string>& result, const std::string& string, const std::string& sep) {
    unsigned long start_pos = 0;
    size_t found_pos = string.find(sep, start_pos);
    while (found_pos != std::string::npos) {
        if (found_pos != 0)
            result.emplace_back(string.substr(start_pos, found_pos - start_pos));

        start_pos = found_pos + sep.length();
        found_pos = string.find(sep, start_pos);
    }
    if (start_pos < string.size())
        result.emplace_back(string.substr(start_pos, found_pos - start_pos));
}
