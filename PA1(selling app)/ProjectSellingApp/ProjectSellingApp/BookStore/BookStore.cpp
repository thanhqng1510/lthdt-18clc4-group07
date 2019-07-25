#include <fstream>
#include <sstream>
#include <regex>

#include "BookStore.h"
#include "../Utility/Util.h"

const std::string book::s_author_pattern = "([A-Z][a-z]*( [A-Z][a-z]*)*)";
const std::string book::s_name_pattern = "([A-Z0-9]+[a-z0-9]*( [A-Z0-9]+[a-z0-9]*)*)";

void book::GetAuthorInput(std::string& author) {
	get_line_input(author, [](const std::string& value) -> bool {
		return std::regex_match(value, std::regex(book::s_author_pattern));
	}, "Wrong name format, please try again: ");
}
	
void book::GetNameInput(std::string& name) {
	get_line_input(name, [](const std::string& value) -> bool {
		return std::regex_match(value, std::regex(book::s_name_pattern));
	}, "Wrong name format, please try again: ");
}

void book::GetPriceInput(unsigned int& price) {
	get_input<unsigned int>(price, [](const float& value) -> bool {
		return value >= 10000;
	}, "Price must be bigger than 10000, please try again: ");
}

void book::GetStockInput(unsigned int& stock) {
	get_input<unsigned int>(stock, [](const unsigned int& value) -> bool {
		return value >= 0;
	}, "Quantity must be positive, please try again: ");
}

void book::Output() const {
	std::cout << "------------------------\n"
		 << "Author: " << author << ".\n"
		 << "Name: " << name << ".\n"
		 << "Price: " << price << ".\n"
		 << "Stock: " << stock << ".\n"
		 << (stock == 0 ? "OUT OF ORDER.\n" : "")
	     << "------------------------\n";
}

std::string book::ToString() const {
	return (name + "," + author + "," + std::to_string(price) + "," + std::to_string(stock));
}

const std::string BookStore::s_book_store_path = "ProjectSellingApp/BookStore/Data/BookStore.txt";

BookStore::BookStore() {
	file_to_unordered_map<std::string, book>(s_book_store_path, m_book_store, [](std::pair<std::string, book>& value, const std::string& line) -> void {
		std::vector<std::string> result;
		parse_string(result, line, ",");
		value = {result[0], 
				{result[0],result[1], (unsigned int)stoi(result[2]), (unsigned int)stoi(result[3]) } };
	});
}

BookStore::~BookStore() {
	unordered_map_to_file<std::string, book>(s_book_store_path, m_book_store, [](const std::pair<std::string, book>& value, std::string& line) {
		line = value.second.ToString();
	});
}

void BookStore::PrintAll() const {
	for (const auto& b : m_book_store)
		b.second.Output();
}

void BookStore::SearchByName() const {
	std::string search;
	std::cout << "Enter book's name: ";
	book::GetNameInput(search);

	if (m_book_store.find(search) != m_book_store.end())
		m_book_store.at(search).Output();
	else
		prompt_message("Book not found.");
}

void BookStore::SearchByAuthor() const {
	std::string search;
	std::cout << "Enter author's name: ";
	book::GetAuthorInput(search);
	
	bool is_found = false;
	for (const auto& b : m_book_store)
		if (b.second.author == search) {
			is_found = true;
			b.second.Output();
		}

	if (!is_found)
		prompt_message("Book not found.");
}

void BookStore::Add() {
	book add;
	std::cout << "Enter book's name: ";
	book::GetNameInput(add.name);

	std::cout << "Enter book's quantity: ";
	book::GetStockInput(add.stock);

	if (m_book_store.find(add.name) != m_book_store.end()) {
		m_book_store.at(add.name).stock += add.stock;

		std::string message = "Added " + std::to_string(add.stock) + " products to existing book (" + add.name + ") successfully.";
		prompt_message(message);

		return;
	}

	std::cout << "Enter book's author: ";
	book::GetAuthorInput(add.author);

	std::cout << "Enter book's price: ";
	book::GetPriceInput(add.price);

	m_book_store.insert({ add.name, add });

	std::string message = "Added new book (" + add.name + ") with " + std::to_string(add.stock) + " products successfully.";
	prompt_message(message);
}

void BookStore::Remove() {
	book remove;
	std::cout << "Enter book's name: ";
	book::GetNameInput(remove.name);

	std::cout << "Enter book's quantity: ";
	book::GetStockInput(remove.stock);

	if (m_book_store.find(remove.name) != m_book_store.end()) {
		if (m_book_store.at(remove.name).stock >= remove.stock) {
			m_book_store.at(remove.name).stock -= remove.stock;

			std::string message = "Removed " + std::to_string(remove.stock) + " products from existing book (" + m_book_store.at(remove.name).name + ") successfully.";
			prompt_message(message);

			return;
		}
		else {
			std::string message = "Book " + m_book_store.at(remove.name).name + " has " + std::to_string(m_book_store.at(remove.name).stock) + " products but have to remove " + std::to_string(remove.stock) + " products.";
			prompt_message(message);

			return;
		}
	}

	prompt_message("Book not found.");
}

//string BookStore::GetMostSell() {
//	return m_book_store[2].name;
//}
//
//string BookStore::GetRecentSell() {
//	return m_book_store[0].name;
//}