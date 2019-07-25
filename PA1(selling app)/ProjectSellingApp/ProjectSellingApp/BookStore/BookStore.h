#pragma once

#include <string>
#include <unordered_map>

struct book {
	static const std::string s_author_pattern;
	static const std::string s_name_pattern;

	static void GetAuthorInput(std::string& author);
	static void GetNameInput(std::string& name);
	static void GetPriceInput(unsigned int& price);
	static void GetStockInput(unsigned int& stock);

	std::string name, author;
	unsigned int price, stock;

	void Output() const;
	std::string ToString() const;
};

class BookStore {
public:
	static const std::string s_book_store_path;

protected:
	std::unordered_map<std::string, book> m_book_store;

public:
	BookStore();
	~BookStore();

public:
	void PrintAll() const;
	void SearchByName() const;
	void SearchByAuthor() const;
	void Add();
	void Remove();

	// string GetMostSell();
	// string GetRecentSell();
};
