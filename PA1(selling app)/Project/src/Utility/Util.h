#pragma once

#include <string>
#include <functional>
#include <limits>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

// Print message to console and wait for user to press any key to continue
void prompt_message(const std::string& message);

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

// Cut string to small parts by a seperator
void parse_string(std::vector<std::string>& result, const std::string& string, const std::string& sep);

// Convert a text file to an unordered_map of any type
template<typename T, typename U>
void file_to_unordered_map(const std::string& file_path, std::unordered_map<T, U>& map, std::function<void(std::pair<T, U>& value, const std::string& line)> line_to_pair) {
	std::ifstream fin(file_path);
	if (!fin.is_open()) {
		prompt_message("Fail to open " + file_path + " !!!");
		return;
	}

	std::string line;
	while (getline(fin, line, '\n')) {
		if (line == "")
			continue;
			
		std::pair<T, U> p;
		line_to_pair(p, line);
		map.insert(p);
	}

	fin.close();
}

// Replace file with new data
template<typename T, typename U>
void unordered_map_to_file(const std::string& file_path, const std::unordered_map<T, U>& map, std::function<void(const std::pair<T, U>& value, std::string& line)> pair_to_line) {
	std::ofstream fout(file_path, std::ios::trunc);
	if (!fout.is_open()) {
		prompt_message("Fail to open " + file_path + " !!!");
		return;
	}

	for (const auto& i : map) {
		std::string line;
		pair_to_line(i, line);
		fout << line << "\n";
	}
	
	fout.close();
}