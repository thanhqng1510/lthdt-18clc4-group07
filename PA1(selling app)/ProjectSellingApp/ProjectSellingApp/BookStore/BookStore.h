#pragma once

#include <string>
#include <unordered_map>

using namespace std;

struct book {
	static const string s_author_pattern;
	static const string s_name_pattern;

	string name, author;
	unsigned int price, stock;

	void Output() const;
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
	BookStore();
	~BookStore();

public:
	void PrintAll() const;
	void Search(SEARCH_KEY key) const;
	void Add();
	void Remove();

	// Update file with unordered_map
	void SyncWithFile() const;
	// string GetMostSell();
	// string GetRecentSell();
};
