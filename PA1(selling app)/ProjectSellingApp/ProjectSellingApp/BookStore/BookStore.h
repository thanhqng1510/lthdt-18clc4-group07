#pragma once

#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>
using namespace std;

struct Book
{
	string name;
	string author;
	float price;
	unsigned int stock;
};

class BookStore
{
private:
	unordered_map<string,Book> m_book_store;
public:
	BookStore();
	void Search();
	void Add();
	void Remove();
	/*string GetMostSell();
	string GetRecentSell();*/
	void Output();
	~BookStore() {};
};