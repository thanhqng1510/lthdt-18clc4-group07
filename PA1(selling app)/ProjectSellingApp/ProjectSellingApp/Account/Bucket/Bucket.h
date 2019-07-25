#pragma once

#include <unordered_map>
#include <string>

#include "../../BookStore/BookStore.h"

class Bucket : public BookStore {
public:
	static const unsigned int m_day_discount[5];

private:
	std::unordered_map<std::string, unsigned int> m_bucket;

public:
	Bucket();
	~Bucket();

public:
	bool CheckDiscountToday() const;
	void Show() const;
	void Add();
	void Remove();
	void BuyAll();
};