#pragma once

#include <iostream>
#include <string>
#include <numeric>
#include <functional>

// Function to get option input of any type from the user and check for error
// Pass nullptr to isValid if you don't want to check further
// Pass a string to error_message to prompt to user when an error occur
template<typename T>
void get_input(T& input, std::function<bool(const T& value)> is_valid, const std::string& error_message) {
	while (!(std::cin >> input) || (is_valid != nullptr && !is_valid(input))) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << error_message;
	}
	std::cin.ignore();
}

// Function to get input of type string from the user and check for error
// Pass nullptr to isValid if you don't want to check further
// Pass a string to error_message to prompt to user when an error occur
void get_line_input(std::string& input, std::function<bool(const std::string& value)> is_valid, const std::string& error_message);

// Print message to console and wait for user to press any key to continue
void prompt_message(const std::string& message);