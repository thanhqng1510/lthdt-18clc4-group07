#include <fstream>
#include <sstream>
#include <regex>

#include "BookStore.h"
#include "../Utility/Util.h"

const string book::s_author_pattern = "([A-Z][a-z]*( [A-Z][a-z]*)*)";
const string book::s_name_pattern = "([A-Z0-9]+[a-z0-9]*( [A-Z0-9]+[a-z0-9]*)*)";

void book::Output() const {
	cout << "------------------------\n"
		 << "Author: " << author << "\n"
		 << "Name: " << name << "\n"
		 << "Price: " << price << "\n"
		 << "Stock: " << stock << "\n"
		 << (stock == 0 ? "OUT OF ORDER\n" : "")
	     << "------------------------";
}

const std::string BookStore::s_book_store_path = "BookStore/Data/BookStore.data";

BookStore::BookStore() {
	file_to_unordered_map<string, book>(s_book_store_path, m_book_store, [](pair<string, book>& value, string& line) -> void {
		vector<string> result;
		parse_string(result, line, ",");
		value = { result[0], { result[0], result[1], (unsigned int)stoi(result[2]), (unsigned int)stoi(result[3]) } };
	});
}

BookStore::~BookStore() {
	SyncWithFile();
}

void BookStore::PrintAll() const {
	for (const auto& b : m_book_store)
		b.second.Output();
}

void BookStore::Search(SEARCH_KEY key) const {
	string search;
	cout << (key == SEARCH_KEY::AUTHOR ? "Enter author's name: " : "Enter book's name: ");
	get_line_input(search, [=](const string& value) -> bool {
		return regex_match(value, regex((key == SEARCH_KEY::AUTHOR) ? book::s_author_pattern : book::s_name_pattern));
	}, "Wrong name format, please try again: ");

	bool is_found = false;
	if (key == SEARCH_KEY::NAME) {
		if (m_book_store.find(search) != m_book_store.end())
			is_found = true;
			m_book_store.at(search).Output();
	}
	else
		for (const auto& b : m_book_store)
			if ((key == SEARCH_KEY::AUTHOR && b.second.author == search) || (key == SEARCH_KEY::NAME && b.first == search)) {
				is_found = true;
				b.second.Output();
			}

	if (!is_found)
		prompt_message("Book not found");
}

void BookStore::Add() {
	book add;
	cout << "Enter book's name: ";
	get_line_input(add.name, [](const string& value) -> bool {
		return regex_match(value, regex(book::s_name_pattern));
	}, "Wrong name format, please try again: ");

	cout << "Enter book's quantity: ";
	get_input<unsigned int>(add.stock, [](const unsigned int& value) -> bool {
		return value >= 0;
	}, "Quantity must be positive, please try again: ");

	if (m_book_store.find(add.name) != m_book_store.end()) {
		m_book_store.at(add.name).stock += add.stock;

		stringstream message;
		message << "Added " << add.stock << " products to existing book (" << add.name << ") successfully";
		prompt_message(message.str());

		return;
	}

	cout << "Enter book's author: ";
	get_line_input(add.author, [](const string& value) -> bool {
		return regex_match(value, regex(book::s_author_pattern));
	}, "Wrong name format, please try again: ");

	cout << "Enter book's price: ";
	get_input<unsigned int>(add.price, [](const float& value) -> bool {
		return value >= 10000;
	}, "Price must be bigger than 10000, please try again: ");

	m_book_store.insert({add.name, add});

	stringstream message;
	message << "Added new book (" << add.name << ") with " << add.stock << " products successfully";
	prompt_message(message.str());
}

void BookStore::Remove() {
	book remove;
	cout << "Enter book's name: ";
	get_line_input(remove.name, [](const string& value) -> bool {
		return regex_match(value, regex(book::s_name_pattern));
	}, "Wrong name format, please try again: ");

	cout << "Enter book's quantity: ";
	get_input<unsigned int>(remove.stock, [](const unsigned int& value) -> bool {
		return value > 0;
	}, "Quantity must be positive, please try again: ");

	if (m_book_store.find(remove.name) != m_book_store.end()) {
		if (book& b = m_book_store.at(remove.name); b.stock >= remove.stock) {
			b.stock -= remove.stock;

			stringstream message;
			message << "Removed " << remove.stock << " products from existing book (" << b.name << ") successfully";
			prompt_message(message.str());

			return;
		}
		else {
			stringstream message;
			message << "Book " << b.name << " has " << b.stock << " products but have to remove " << remove.stock << " products";
			prompt_message(message.str());

			return;
		}
	}

	prompt_message("Book not found");
}

void BookStore::SyncWithFile() const {
	ofstream fout(s_book_store_path, ios::trunc);
	if (!fout.is_open()) {
		prompt_message("Fail to open BookStore.data");
		return;
	}

	for (const auto& b : m_book_store)
		fout << b.second.name << "," << b.second.author << "," << b.second.price << "," << b.second.stock << "\n";

	fout.close();
}

//string BookStore::GetMostSell() {
//	return m_book_store[2].name;
//}
//
//string BookStore::GetRecentSell() {
//	return m_book_store[0].name;
//}
