#pragma once
#pragma once

#include<string>
#include<iostream>
#include<unordered_map>
#include<utility>
#include<fstream>
#include<time.h>
#include"BookStore.h"
using namespace std;


class Bucket :public BookStore
{
private:
	unordered_map<string, pair<Book, int>> m_bucket;
	vector<int> dis;
public:
	void ReadFileDiscount();
	bool CheckDiscount();
	void WatchBucket();
	void AddToBucket();
	void RemoveFromBucket();
	void BuyAll();

};
