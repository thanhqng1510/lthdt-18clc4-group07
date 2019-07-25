#include "Bucket.h"



void Bucket::ReadFileDiscount()
{
	ifstream fin("DateDiscount.txt");
	while (!fin.eof())
	{
		int n;
		fin >> n;
		dis.push_back(n);
	}
	fin.close();
}

bool Bucket::CheckDiscount()
{
	time_t now = time(0);
	tm local;
	localtime_s(&local, &now);
	int day = local.tm_mday;
	int mon = local.tm_mon + 1;
	int year = local.tm_year + 1900;
	for (int i = 0; i < dis.size(); i++)
	{
		if (day == dis[i])
			return true;
	}
	return false;
}

// 20% discount
void Bucket::WatchBucket()
{
	if (Bucket::CheckDiscount())
	{
		for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
		{
			i->second.first.price *= 0.8;
		}

	}
	float total = 0;
	for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
	{
		if (i->second.second != 0)
		{
			cout << "Name's book: " << i->second.first.name << endl
				<< "Author's book: " << i->second.first.author << endl
				<< "Price: " << i->second.first.price << endl
				<< "Amount: " << i->second.second << endl;
			total += i->second.first.price*i->second.second;
		}
	}
	cout << "Total: " << total << endl;
}

void Bucket::AddToBucket()
{
	string Name;
	int amount;
	cout << "Enter name's book you want add: ";
	getline(cin, Name);
	for (auto i = m_book_store.begin(); i != m_book_store.end(); i++)
	{
		if (i->second.name == Name)
		{
			cout << "Amount: ";
			cin >> amount;
			if (i->second.stock >= amount)
			{
				int temp = 0;
				//i->second.stock -= amount;
				for (auto j = m_bucket.begin(); j != m_bucket.end(); j++)
				{
					if (j->first == Name)
					{
						j->second.second += amount;
						temp++;
					}
				}
				if (temp == 0)
					m_bucket.insert({ Name,{i->second,amount} });
			}
		}
	}
}

void Bucket::RemoveFromBucket()
{
	string Name;
	int count = 0;
	int amount;
	cout << "Enter book's name you want remove from your bucket: ";
	cin.ignore();
	getline(cin, Name);
	for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
	{
		if (i->second.first.name == Name)
		{
			cout << "Enter amount this book you want remove: ";
			cin >> amount;
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
		cout << "Not exist this book in your bucket";
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
	cout << "Do you want buy all (1: Yes, 2:No ): ";
	cin >> choose;
	if (choose == 1)
	{
		ofstream fout("Bucket.txt");
		for (auto i = m_bucket.begin(); i != m_bucket.end(); i++)
		{
			fout << i->first << " "
				<< i->second.first.price << " "
				<< i->second.second << endl;
			total += i->second.first.price*i->second.second;
		}
		fout << "Total: " << total << endl;
		if (Bucket::CheckDiscount())
			fout << "Discounted " << endl;
		fout.close();
	}
}
