#pragma once

#include <iostream>
#include <string>
#include <numeric>
#include <functional>

// Function to get option input of any type from the user and check for error
// Pass nullptr to isValid if you don't want to check further
template<typename T>
void getOptionInput(T& input, std::function<bool(const T& value)> isValid) {
	while (!(std::cin >> input) || (isValid != nullptr && !isValid(input))) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Error, please try again: ";
	}
	std::cin.ignore();
}

// Function to get input of type string from the user and check for error
// Pass nullptr to isValid if you don't want to check further
void getStringInput(std::string& input, std::function<bool(const std::string& value)> isValid);