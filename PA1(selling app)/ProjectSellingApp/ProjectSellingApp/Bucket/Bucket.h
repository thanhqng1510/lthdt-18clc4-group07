#pragma once
#pragma once

#include<string>
#include<iostream>
#include<unordered_map>
#include<utility>
#include<fstream>
#include"BookStore.h"
using namespace std;


class Bucket :public BookStore
{
private:
	unordered_map<string, pair<Book, int>> m_bucket;
public:
	void AddToBucket();
	void RemoveFromBucket();
	void BuyAll();

};
