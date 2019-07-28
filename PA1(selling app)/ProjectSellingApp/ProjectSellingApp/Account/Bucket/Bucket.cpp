
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "Bucket.h"

const std::string Bucket::s_bucket_folder_path = "ProjectSellingApp/Account/Bucket/Data/";
const unsigned int Bucket::s_day_discount[4] = { 5, 10, 17, 25 };

Bucket::Bucket(const std::string& username) 
: m_username(username) {
	std::string file_path = s_bucket_folder_path + m_username + ".txt";

	std::ifstream fin(file_path);
	if (!fin.is_open())
		system(("touch " + file_path).c_str());
	else
		fin.close();
	
	file_to_unordered_map<std::string, unsigned int>(file_path, m_bucket, [](std::pair<std::string, unsigned int>& p, const std::string& line) -> void {
		std::vector<std::string> result;
		parse_string(result, line, ",");
		p = { result[0],
			  (unsigned int)stoi(result[1]) };
	});
}

Bucket::~Bucket(){
	SyncWithFile();
}

bool Bucket::CheckDiscountToday() const {
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
void Bucket::WatchBucket() const {
	// float factor;

	// if (Bucket::CheckDiscountToday())
	// 	factor = 0.8f;
	// else
	// 	factor = 1.f;


	// float total = 0;
	// for (auto i = m_bucket.begin(); i != m_bucket.end(); i++) {
	// 	std::cout << "Author: " << i->second.first.author << "\n"
	// 			  << "Name: " << i->second.first.name << "\n"
	// 		      << "Price: " << i->second.first.price * factor << "\n"
	// 		      << "Amount: " << i->second.second << "\n";
	// 	total += i->second.first.price * i->second.second * factor;
	// }

	// std::cout << "Total: " << total << "\n";
}

void Bucket::Add() {
	// std::string name;
	// int amount;
	// std::cout << "Enter name's book you want add: ";
	// book::GetNameInput(name);

	// for (const auto& i : m_book_store) {
	// 	if (i.second.name == name) {
	// 		std::cout << "Enter "
	// 		std::cin >> amount;
	// 		if (i->second.stock >= amount)
	// 		{
	// 			int temp = 0;
	// 			//i->second.stock -= amount;
	// 			for (auto j = m_bucket.begin(); j != m_bucket.end(); j++)
	// 			{
	// 				if (j->first == name)
	// 				{
	// 					j->second.second += amount;
	// 					temp++;
	// 				}
	// 			}
	// 			if (temp == 0)
	// 				m_bucket.insert({ name,{i->second,amount} });
	// 		}
	// 	}
	// }
}

void Bucket::Remove()
{
	// std::string Name;
	// int count = 0;
	// int amount;
	// std::cout << "Enter book's name you want remove from your bucket: ";
	// std::cin.ignore();
	// getline(std::cin, Name);
	// for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
	// {
	// 	if (i->second.first.name == Name)
	// 	{
	// 		std::cout << "Enter amount this book you want remove: ";
	// 		std::cin >> amount;
	// 		if (i->second.second >= amount)
	// 		{
	// 			i->second.second -= amount;
	// 			/*for (auto j = m_book_store.begin(); j != m_book_store.end(); i++)
	// 			{
	// 				j->second.stock += amount;
	// 			}*/
	// 		}
	// 		count++;
	// 	}
	// }
	// if (count == 0)
	// 	std::cout << "Not exist this book in your bucket";
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
	std::string file_path = s_bucket_folder_path + m_username + ".txt";
	unordered_map_to_file<std::string, unsigned int> (file_path, m_bucket, [](const std::pair<std::string, unsigned int>& value, std::string& line) -> void {
		line = value.first + "," + std::to_string(value.second);
	});
}
