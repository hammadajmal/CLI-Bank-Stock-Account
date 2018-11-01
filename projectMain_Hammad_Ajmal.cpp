#include "BankAccount.h"
#include "StockAccount.h"
#include "Account.h"
#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>
#include <iterator> 
#include <vector>
using namespace std;

int main(){
	BankAccount ba;//Bank Account;	
	StockAccount sa; //stock account;
	// beginning the program printing out inital messages and displaying initial options
	cout << "Welcome to the Account Management System." << endl;
	//defining a few flags and selector variables, each should have a descriptive name.  
	bool exit = false;
	int selector = -1;
	//simple menu with a bunch of if conditions and while to make sure we stay in a certain menu until user wants out. 
	while (!exit){
		cout << "Please select an account to access:" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		cin >> selector;
		if (selector == 1){
			bool firstcase = true; //stay in this option until user wants out.
			sa.choice();//we'll let user choose which sort he wants for this session.
			while (firstcase){
				cout << "Please select an option :" << endl;
				cout << "1. Display the price for a stock symbol" << endl;
				cout << "2. Display the current portfolio" << endl;
				cout << "3. Buy shares" << endl;
				cout << "4. Sell shares" << endl;
				cout << "5. View a graph for the portfolio value" << endl;
				cout << "6. View transaction history" << endl;
				cout << "7. Return to previous menu" << endl;
				cin >> selector;
				if (selector == 1){
					string Name;
					cout << "Which stock do you want to view the price for?" << endl;
					cin >> Name;
					sa.displayStockPrice(Name);
				}
				if (selector == 2){
					sa.displayPortfolio();
				}
				if (selector == 3){
					sa.buyShares();
				}
				if (selector == 4){
					sa.sellShares();
				}
				if (selector == 5){
					sa.graphPort();
				}
				if (selector == 6){
					sa.printHistory();
				}
				if (selector == 7){					
					firstcase = false;
				}

			}
		}
		if (selector == 2){
			bool secondcase = true;//we'll stay in this option until user wants out.
			while (secondcase){
				cout << "Please select an option :" << endl;
				cout << "1. View account balance" << endl;
				cout << "2. Deposit money" << endl;
				cout << "3. Withdraw money" << endl;
				cout << "4. Print out history" << endl;
				cout << "5. Return to previous menu" << endl;
				cin >> selector;
				if (selector == 1){
					ba.viewbalance();
				}
				if (selector == 2){
					ba.deposit();
				}
				if (selector == 3){
					ba.withdraw();
				}
				if (selector == 4){
					ba.printHistory();
				}
				if (selector == 5){
					secondcase = false;
				}
			}
		}
		if (selector == 3) exit = true;
	}	
	//create a portfolio history before we exit.
	sa.createPortfolioHistory();
	//now we are done.
}