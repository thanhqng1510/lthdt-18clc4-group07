
#include<iostream>
#include<string>
#include<vector>
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
	vector<Book> m_book_store;
public:
	BookStore();
	void Search();
	void Add();
	void Remove();
	string GetMostSell();
	string GetRecentSell();
	void Output();
	~BookStore() {};
};