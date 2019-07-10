#include <fstream>
#include <sstream>
#include <regex>

#include "BookStore.h"
#include "../Utility/Util.h"

const string book::s_author_pattern = "([A-Z][a-z]*( [A-Z][a-z]*)*)";
const string book::s_name_pattern = "([A-Z0-9]+[a-z0-9]*( [A-Z0-9]+[a-z0-9]*)*)";

ostream& operator << (ostream& stream, const book& b) {
	return stream << "------------------------\n"
		          << "Author: " << b.author << "\n"
		          << "Name: " << b.name << "\n"
		          << "Price: " << b.price << "\n"
		          << "Stock: " << b.stock << "\n"
				  << (b.stock == 0 ? "OUT OF ORDER\n" : "")
	              << "------------------------";
}

const std::string BookStore::s_book_store_path = "BookStore/Data/BookStore.data";

BookStore::BookStore() {
	ifstream fin(s_book_store_path);
	if (!fin.is_open()) {
		prompt_message("Fail to open BookStore.data");
		return;
	}

	book temp;
	while (getline(fin, temp.name, ',')) {
		getline(fin, temp.author, ',');

		string Pe, Sk;
		getline(fin, Pe, ',');
		temp.price = (unsigned int)stoi(Pe);
		getline(fin, Sk);
		temp.stock = (unsigned int)stoi(Sk);

		m_book_store.emplace_back(temp);
	}

	fin.close();
}

void BookStore::Search(SEARCH_KEY key) const {
	string search;
	cout << (key == SEARCH_KEY::AUTHOR ? "Enter author's name: " : "Enter book's name: ");
	get_line_input(search, [=](const string& value) {
		return regex_match(value, regex((key == SEARCH_KEY::AUTHOR) ? book::s_author_pattern : book::s_name_pattern));
		}, "Wrong name format, please try again: ");
	
	bool is_found = false;
	for (const book& b : m_book_store) {
		if ((key == SEARCH_KEY::AUTHOR && b.author == search) || (key == SEARCH_KEY::NAME && b.name == search)) {
			is_found = true;
			cout << b << endl;
		}
	}

	if (!is_found)
		prompt_message("Book not found");
}

void BookStore::Add() {
	book add;
	cout << "Enter book's name: ";
	get_line_input(add.name, [](const string& value) {
		return regex_match(value, regex(book::s_name_pattern));
		}, "Wrong name format, please try again: ");
	cout << "Enter book's quantity: ";
	get_input<unsigned int>(add.stock, [](const unsigned int& value) {
		return value >= 0;
		}, "Quantity must be positive, please try again: ");

	for (book& b : m_book_store) {
		if (b.name == add.name) {
			b.stock += add.stock;

			stringstream message;
			message << "Added " << add.stock << " products to existing book (" << b.name << ") successfully";
			prompt_message(message.str());

			return;
		}
	}
	
	cout << "Enter book's author: ";
	get_line_input(add.author, [](const string& value) {
		return regex_match(value, regex(book::s_author_pattern));
		}, "Wrong name format, please try again: ");
	cout << "Enter book's price: ";
	get_input<unsigned int>(add.price, [](const float& value) {
		return value >= 10000;
		}, "Price must be bigger than 10000, please try again: ");

	m_book_store.emplace_back(add);

	stringstream message;
	message << "Added new book (" << add.name << ") with " << add.stock << " products successfully";
	prompt_message(message.str());
}

void BookStore::Remove() {
	book remove;
	cout << "Enter book's name: ";
	get_line_input(remove.name, [](const string& value) {
		return regex_match(value, regex(book::s_name_pattern));
		}, "Wrong name format, please try again: ");
	cout << "Enter book's quantity: ";
	get_input<unsigned int>(remove.stock, [](const unsigned int& value) {
		return value > 0;
		}, "Quantity must be positive, please try again: ");

	for (book& b : m_book_store) {
		if (b.name == remove.name)
			if (remove.stock <= b.stock) {
				b.stock -= remove.stock;

				stringstream message;
				message << "Removed " << remove.stock << " products from existing book(" << b.name << ") successfully";
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

	for (const book& b : m_book_store)
		fout << b.name << "," << b.author << "," << b.price << "," << b.stock << "\n";

	fout.close();
}

//string BookStore::GetMostSell() {
//	return m_book_store[2].name;
//}
//
//string BookStore::GetRecentSell() {
//	return m_book_store[0].name;
//}