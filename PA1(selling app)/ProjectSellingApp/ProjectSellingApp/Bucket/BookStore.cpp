#include"BookStore.h"


BookStore::BookStore()
{
	ifstream fin;
	fin.open("bookStore.txt");
	Book Temp;
	string Pe;
	string Sk;
	while (getline(fin, Temp.name, ','))
	{
		getline(fin, Temp.author, ',');
		getline(fin, Pe, ',');
		Temp.price = (int)atof(Pe.c_str());
		getline(fin, Sk);
		Temp.stock = (unsigned int)atof(Sk.c_str());
		m_book_store.insert({ Temp.name,Temp });
	}
	unordered_map<string, Book>::iterator V = m_book_store.begin();
	for (; V != m_book_store.end(); V++)
	{
		cout << V->second.name << " "
			<< V->second.author << " "
			<< V->second.price << " "
			<< V->second.stock << endl;
	}
	fin.close();
}

void BookStore::Search()
{
	int x = 0;
	do {
		int temp = 0;
		unordered_map<string, Book>::iterator V = m_book_store.begin();
		string BookName;
		cout << "Please enter book's name: ";
		cin >> BookName;
		while (V != m_book_store.end())
		{
			if ((V)->second.name == BookName)
			{
				cout << "Yes" << endl;
				temp++;
			}
			V++;
		}
		if (temp == 0)
			cout << "No" << endl;
		cout << "Do you want search book another" << "1:Yes/2:No: ";
		cin >> x;
	} while (x == 1);
}

void BookStore::Add()
{
	int x = 0;
	do {
		Book B;
		cout << "Please enter book's name you want add: ";
		cin >> B.name;
		cout << "Please enter number book you want add in stock: ";
		cin >> B.stock;
		int temp = 0;
		for (auto i = m_book_store.begin(); i != m_book_store.end(); i++)
		{
			if (i->second.name == B.name)
			{
				i->second.stock += B.stock;
				temp++;
				break;
			}
		}
		if (temp == 0)
		{
			cout << "Please enter book's author: ";
			cin >> B.author;
			cout << "Please enter book's price: ";
			cin >> B.price;
			m_book_store.insert({ B.name, B });
		}
		cout << "Do you want add book another " << "1:Yes/2:No: ";
		cin >> x;
	} while (x == 1);
}

void BookStore::Remove()
{
	int x = 0;
	do {
		int temp = 0;
		Book B;
		cout << "Please enter book's name you want remove: ";
		cin >> B.name;
		cout << "Please enter number book you want remove in stock: ";
		cin >> B.stock;
		for (auto i = m_book_store.begin(); i != m_book_store.end(); i++)
		{
			if (i->second.name == B.name && B.stock <= i->second.stock)
			{
				i->second.stock -= B.stock;
				temp++;
				break;
			}
		}
		if (temp == 0)
			cout << "This book not remove" << endl;
		cout << "Do you want remove book another " << "1:Yes/2:No: ";
		cin >> x;
	} while (x == 1);
}

//string BookStore::GetMostSell()
//{
//	return m_book_store[2].name;
//}
//
//string BookStore::GetRecentSell()
//{
//	return m_book_store[0].name;
//}

void BookStore::Output()
{
	unordered_map<string, Book>::iterator V = m_book_store.begin();
	for (; V != m_book_store.end(); V++)
	{
		cout << (V)->second.name << " "
			<< (V)->second.author << " "
			<< (V)->second.price << " "
			<< (V)->second.stock << endl;
	}
}