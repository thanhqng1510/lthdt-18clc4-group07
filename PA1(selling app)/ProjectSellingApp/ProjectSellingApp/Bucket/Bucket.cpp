#include "Bucket.h"



void Bucket::AddToBucket()
{
	string Name;
	int amount;
		cout << "Enter name's book you want add: ";
		getline(cin, Name); 
		for (auto i = m_book_store.begin(); i != m_book_store.end(); i++)
		{
			if (i->second.name == Name )
			{
					cout << "Amount: ";
					cin >> amount;
					if (i->second.stock >= amount)
					{
						int temp = 0;
						i->second.stock -= amount;
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
						for (auto j = m_book_store.begin(); j != m_book_store.end(); i++)
						{
							j->second.stock += amount;
						}
					}
			}
		}
}

void Bucket::BuyAll()
{
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