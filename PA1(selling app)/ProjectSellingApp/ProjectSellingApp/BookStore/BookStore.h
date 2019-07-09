#include<string>
#include<vector>
#include <iostream>
using namespace std;

struct book {
	static const string s_author_sample;
	static const string s_name_sample;

	string author, name;
	int price;
	unsigned int stock;

	friend ostream& operator << (ostream& stream, const book& b);
};

enum class SEARCH_KEY {
	AUTHOR = 0,
	NAME = 1
};

class BookStore {
private:
	vector<book> m_book_store;

public:
	static const std::string s_book_store_path;

public:
	// Create a bookstore for further work
	BookStore();

	// Sync with file
	inline ~BookStore() {
		SyncWithData();
	}

public:
	// Assume that index is valid
	inline book& operator [] (int index) {
		return m_book_store[index];
	}

	inline const book& operator [] (int index) const {
		return m_book_store[index];
	}

public:
	inline void PrintAll() const {
		for (const book& b : m_book_store)
			cout << b << endl;
	}

	void Search(SEARCH_KEY key) const;
	void Add();
	void Remove();
	void SyncWithData() const;
	// string GetMostSell();
	// string GetRecentSell();
};