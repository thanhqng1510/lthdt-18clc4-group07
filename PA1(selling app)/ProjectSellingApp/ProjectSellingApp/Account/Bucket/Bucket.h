#pragma once
#pragma once

#include<string>
#include<iostream>
#include<unordered_map>
#include<utility>
#include<fstream>
#include "../../BookStore/BookStore.h"
using namespace std;


class Bucket : public BookStore
{
private:
	unordered_map<string, pair<book, int>> m_bucket;
public:
	void AddToBucket();
	void RemoveFromBucket();
	void BuyAll();

};
