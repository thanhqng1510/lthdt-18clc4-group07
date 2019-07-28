#pragma once

#include <unordered_map>
#include <string>

#include "../../BookStore/BookStore.h"

class Bucket : public BookStore {
public:
	static const std::string s_bucket_folder_path;
	static const unsigned int s_day_discount[4];
	
private:
	std::unordered_map<std::string,unsigned int> m_bucket;
	std::string m_username;

public:
	Bucket(const std::string& username);
	~Bucket();

public:
	bool CheckDiscountToday() const;
	void WatchBucket() const;
	void Add();
	void Remove();
	void BuyAll();
	void SyncWithFile() const;
};
