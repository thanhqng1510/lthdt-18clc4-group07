#pragma once

#include <string>
#include <vector>
#include <functional>
#include <fstream>

#include "Util.h"

// Convert a text file t a vector of any type
template<typename T>
void file_to_vec(const std::string& file_path, std::vector<T>& input, std::function<void(T& value, const std::string& line)> line_to_T) {
	std::ifstream fin(file_path);
	if (!fin.is_open()) {
		prompt_message("Fail to open " + file_path);
		return;
	}

	std::string line;
	while (getline(fin, line, '\n')) {
		T t;
		line_to_T(t, line);
		input.emplace_back(t);
	}

	prompt_message("Convert successfully");
	fin.close();
}

template<typename T>
class FileHandler {
private:
	std::string m_file_path;
	std::vector<T> m_vec;

public:
	inline FileHandler(const std::string& file_path, std::function<void(T& value, const std::string& line)> line_to_T) 
		: m_file_path(file_path) {
		file_to_vec(file_path, m_vec, line_to_T);
	}

public:
	inline void SyncWithFile() const {
		std::ofstream fout(m_file_path, ios::trunc);
		if (!fout.is_open()) {
			prompt_message("Fail to open " + m_file_path);
			return;
		}

		for (const T& t : m_vec)
			fout << t << "\n";

		fout.close();
	}
};