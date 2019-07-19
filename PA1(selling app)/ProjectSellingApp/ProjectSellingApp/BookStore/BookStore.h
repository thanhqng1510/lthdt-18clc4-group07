#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

#include "../Utility/Util.h"
using namespace std;

struct book {
	inline static const string book::s_author_pattern = "([A-Z][a-z]*( [A-Z][a-z]*)*)";
	inline static const string book::s_name_pattern = "([A-Z0-9]+[a-z0-9]*( [A-Z0-9]+[a-z0-9]*)*)";

	string name, author;
	unsigned int price, stock;

	friend ostream& operator << (ostream& stream, const book& b);
};

enum class SEARCH_KEY {
	AUTHOR = 0,
	NAME = 1
};

class BookStore {
public:
	static const string s_book_store_path;

private:
	unordered_map<string, book> m_book_store;

public:
	// Create a bookstore for further work
	inline BookStore() {
		file_to_unordered_map<string, book>(s_book_store_path, m_book_store, [](pair<string, book>& value, string& line) -> void {
			vector<string> result;
			parse_string(result, line, ",");
			value = { result[0], { result[0], result[1], (unsigned int)stoi(result[2]), (unsigned int)stoi(result[3]) } };
		});
	}

	inline ~BookStore() {
		SyncWithFile();
	}

public:
	inline void PrintAll() const {
		for (const auto& b : m_book_store)
			cout << b.second << endl;
	}

	void Search(SEARCH_KEY key) const;
	void Add();
	void Remove();

	// Update file with unordered_map
	void SyncWithFile() const;
	// string GetMostSell();
	// string GetRecentSell();
};
