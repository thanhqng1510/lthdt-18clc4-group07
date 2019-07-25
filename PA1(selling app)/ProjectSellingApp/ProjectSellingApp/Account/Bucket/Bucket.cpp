#include <ctime>
#include <fstream>
#include <iostream>

#include "Bucket.h"

const unsigned int Bucket::m_day_discount[5] = { 1, 10, 15, 25, 30 };

bool Bucket::CheckDiscountToday() const {
	time_t now = time(nullptr);
	tm* local = localtime(&now);
	int day = local->tm_mday;
	int mon = local->tm_mon + 1;
	int year = local->tm_year + 1900;

	for (int i = 0; i < 5; i++)
		if (day == m_day_discount[i])
			return true;

	return false;
}

// 20% discount
void Bucket::Show() const {
	float factor;

	if (Bucket::CheckDiscountToday())
		factor = 0.8f;
	else
		factor = 1.f;


	float total = 0;
	for (const auto& i : m_bucket) {
		m_book_store.at(i.first).Output();
		total += m_book_store.at(i.first).price * i.second * factor;
	}

	std::cout << "Total: " << total << "\n";
}

void Bucket::Add() {
	std::string name;
	std::cout << "Enter book's name: ";
	book::GetNameInput(name);

	for (const auto& i : m_book_store) {
		if (i.second.name == name) {
			std::cout << "Enter number of copies you want: "
			std::cin >> amount;
			if (i->second.stock >= amount)
			{
				int temp = 0;
				//i->second.stock -= amount;
				for (auto j = m_bucket.begin(); j != m_bucket.end(); j++)
				{
					if (j->first == name)
					{
						j->second.second += amount;
						temp++;
					}
				}
				if (temp == 0)
					m_bucket.insert({ name,{i->second,amount} });
			}
		}
	}

	if (m_book_store.find(name) != m_book_store.end()) {
		unsigned int amount;
		std::cout << "Enter number of copies you want: ";
		book::GetStockInput(amount);
	}

	prompt_message("Book not found.");
}

void Bucket::RemoveFromBucket()
{
	std::string Name;
	int count = 0;
	int amount;
	std::cout << "Enter book's name you want remove from your bucket: ";
	std::cin.ignore();
	getline(std::cin, Name);
	for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
	{
		if (i->second.first.name == Name)
		{
			std::cout << "Enter amount this book you want remove: ";
			std::cin >> amount;
			if (i->second.second >= amount)
			{
				i->second.second -= amount;
				/*for (auto j = m_book_store.begin(); j != m_book_store.end(); i++)
				{
					j->second.stock += amount;
				}*/
			}
			count++;
		}
	}
	if (count == 0)
		std::cout << "Not exist this book in your bucket";
}

void Bucket::BuyAll()
{
	Bucket::WatchBucket();
	for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
	{
		for (auto j = m_book_store.begin(); j != m_book_store.end(); j++)
		{
			if (i->first == j->second.name)
				j->second.stock -= i->second.second;
		}
	}
	int choose;
	int total=0;
	std::cout << "Do you want buy all (1: Yes, 2:No ): ";
	std::cin >> choose;
	if (choose == 1)
	{
		std::ofstream fout("Bucket.txt");
		for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
		{
			fout << i->first << " "
				<< i->second.first.price << " "
				<< i->second.second << "\n";
			total += i->second.first.price*i->second.second;
		}
		fout << "Total: " << total << "\n";
		if (Bucket::CheckDiscountToday())
			fout << "Discounted " << "\n";
		fout.close();
	}
}