#pragma once

#include <unordered_map>
#include <string>

#include "../../BookStore/BookStore.h"

class Bucket : public BookStore {
private:
	std::unordered_map<std::string, std::pair<book, unsigned int>> m_bucket;
	unsigned int m_day_discount[4];

public:
	//Bucket();
	//~Bucket();

public:
	bool CheckDiscountToday() const;
	void WatchBucket() const;
	void Add();
	void Remove();
	void BuyAll();
};
