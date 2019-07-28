
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "Bucket.h"

const std::string Bucket::s_bucket_folder_path = "ProjectSellingApp/Account/Bucket/Data/";
const unsigned int Bucket::s_day_discount[4] = { 5, 10, 17, 25 };

Bucket::Bucket(const std::string& username) 
: m_username(username), m_file_path(s_bucket_folder_path + username + ".txt") {
	std::ifstream fin(m_file_path);
	if (!fin.is_open())
		system(("touch " + m_file_path).c_str());
	else
		fin.close();
	
	file_to_unordered_map<std::string, unsigned int>(m_file_path, m_bucket, [](std::pair<std::string, unsigned int>& p, const std::string& line) -> void {
		std::vector<std::string> result;
		parse_string(result, line, ",");
		p = { result[0],
			  (unsigned int)stoi(result[1]) };
	});
}

Bucket::~Bucket(){
	SyncWithFile();
}

bool Bucket::IsSaleToday() const {
	time_t now = time(nullptr);
	tm* local = localtime(&now);
	int day = local->tm_mday;
	int mon = local->tm_mon + 1;
	int year = local->tm_year + 1900;

	for (int i = 0; i < 5; i++)
		if (day == s_day_discount[i])
			return true;
	return false;
}

// 20% discount
void Bucket::PrintAll() const {
	float factor;
	if (Bucket::IsSaleToday())
		factor = 0.8f;
	else
		factor = 1.f;

	float total = 0;
	for (const std::pair<std::string,unsigned int>& i : m_bucket){
		const book& b = m_book_store.at(i.first);
		b.Output();
		std::cout << "Price after sale : " << b.price * factor << "\n"
				  << "Amount in your bucket: " << i.second << "\n"
				  << "------------------------\n";
		total += b.price * factor;
	}

	std::cout << "TOTAL : " << total << "\n";
	prompt_message("");
}

void Bucket::Add() {
	std::string name;
	std::cout << "Enter book's name : ";
	book::GetNameInput(name);
	
	if (m_book_store.find(name) != m_book_store.end()) {
		const book& b = m_book_store.at(name);

		unsigned int amount;
		std::cout << "Enter number of book you want to buy : ";
		get_input<unsigned int>(amount, [&b](const unsigned int& value) -> bool {
			return (value > 0 && value <= b.stock) ;
		}, "Amount must be positive and less than or equal to " + std::to_string(b.stock));

		if (m_bucket.find(name) != m_bucket.end()) {
			m_bucket.at(name) += amount;
			prompt_message("Book amount increased successfully.");
		}
		else {
			m_bucket.insert({ name, amount });
			prompt_message("Book added successfully.");
		}
	}
	else 
		prompt_message("Book not found.");
}

void Bucket::Remove() {
	std::string name;
	std::cout << "Enter book's name you want remove from your bucket: ";
	book::GetNameInput(name);

	if (m_bucket.find(name) != m_bucket.end()){
		unsigned int& cur_amount = m_bucket.at(name);
		unsigned int amount;
		std::cout << "Enter number of book you want to remove : ";
		get_input<unsigned int>(amount, [&cur_amount](const unsigned int& value) -> bool {
			return (value > 0 && value <= cur_amount);
		}, "Amount must be positive and less than or equal to " + std::to_string(cur_amount));

		cur_amount -= amount;

		if (cur_amount == 0) {
			m_bucket.erase(name);
			prompt_message("Book removed successfully.");
		}
		else
			prompt_message("Book amount decreased successfully.");

	} 
	else 
		prompt_message ("Book not found.");
}

void Bucket::BuyAll()
{
	// Bucket::WatchBucket();
	// for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
	// {
	// 	for (auto j = m_book_store.begin(); j != m_book_store.end(); j++)
	// 	{
	// 		if (i->first == j->second.name)
	// 			j->second.stock -= i->second.second;
	// 	}
	// }
	// int choose;
	// int total=0;
	// std::cout << "Do you want buy all (1: Yes, 2:No ): ";
	// std::cin >> choose;
	// if (choose == 1)
	// {
	// 	std::ofstream fout("Bucket.txt");
	// 	for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
	// 	{
	// 		fout << i->first << " "
	// 			<< i->second.first.price << " "
	// 			<< i->second.second << "\n";
	// 		total += i->second.first.price*i->second.second;
	// 	}
	// 	fout << "Total: " << total << "\n";
	// 	if (Bucket::CheckDiscountToday())
	// 		fout << "Discounted " << "\n";
	// 	fout.close();
	// }
}

void Bucket::SyncWithFile() const {
	unordered_map_to_file<std::string, unsigned int> (m_file_path, m_bucket, [](const std::pair<std::string, unsigned int>& value, std::string& line) -> void {
		line = value.first + "," + std::to_string(value.second);
	});
}
