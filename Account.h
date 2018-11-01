#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <time.h>
#include <vector>
using namespace std;
class Account{
public:
	//this template splits a string comes in handy
	template<typename T>
	vector<T>
		split(const T & str, const T & delimiters) {
		vector<T> v;
		T::size_type start = 0;
		auto pos = str.find_first_of(delimiters, start);
		while (pos != T::npos) {
			if (pos != start) // ignore empty tokens
				v.emplace_back(str, start, pos - start);
			start = pos + 1;
			pos = str.find_first_of(delimiters, start);
		}
		if (start < str.length()) // ignore trailing delimiter
			v.emplace_back(str, start, str.length() - start); // add what's left of the string
		return v;
	}
protected:
	void updateBalance(); //gets the current balance.
	float balance = 10000; // inital balanace of 10000.
};
#endif