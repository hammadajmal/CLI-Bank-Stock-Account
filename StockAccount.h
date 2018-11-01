#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H
#include "Account.h"
#include "Linked List.h"
class StockAccount: public Account{
public:
	//each function does as its name describes.
	void displayStockPrice(string stockName);
	void displayPortfolio();
	void buyShares();
	void sellShares();
	void printHistory();
	void choice();//lets user choose if he wants insertion or selection sort.
	void createPortfolioHistory();
	void graphPort();
private:
	//call populateList() whenever we need to get stock values, setRnd() for random number.
	void writePort();
	void updatePortfolio();
	void populateList(); //this will store the stock information for the session as a vector of string vectors which store various information about the stock.
	void setRnd(); //this will set rand to be a random number each time we access stock account which will then determine which value to get.
	LinkedList *portfolio = new LinkedList(); //portfolio values this is a self sorting linked list, i.e each time a value is added it'll be sorted.
	int rnd;
	vector<vector<string>> stockList; //this will store the stocks its a vector of vector of strings.
}; 
#endif