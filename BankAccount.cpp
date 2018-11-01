#include "BankAccount.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

void BankAccount::viewbalance(){
	updateBalance();
	cout << "Your current balance is " << balance << endl;
}
void BankAccount::deposit(){
	//lets just assume the user has this money.
	updateBalance();//get the most recent balance
	fstream fs;//we'll try and open the file;
	//time info
	time_t seconds;
	seconds = time(NULL);
	tm  timeinfo;
	localtime_s(&timeinfo, &seconds);
	//get rid of some characters that append a new line in the time string. 
	char str[26];
	asctime_s(str, &timeinfo);
	string times = (string)str;
	times = times.substr(0, 24);
	fs.open("history.txt", fstream::out | fstream::in | fstream::app); //open fs for reading and writing in append mode. 
	if (!fs.is_open()){//if history is not there make one
		fs.open("history.txt", fstream::out | fstream::in | fstream::trunc);
		float amount;
		cout << "Please enter the amount you wish to deposit: ";
		cin >> amount;
		while (amount > (float)5000){//I'll limit it to 5000 per transaction.
			cout << "You can only deposit $5000 at once, please enter a new amount." << endl;
			cin >> amount;
		}
		balance += amount;
		fs << times << " Deposit: " << amount << " New Balance: " << balance << "\n";
	}
	else{
		float amount;
		cout << "Please enter the amount you wish to deposit: ";
		cin >> amount;
		while (amount > (float)5000){//I'll limit it to 5000 per transaction.
			cout << "You can only deposit $5000 at once, please enter a new amount." << endl;
			cin >> amount;
		}
		balance += amount;
		fs << times << " Deposit: " << amount << " New Balance: " << balance << "\n";
	}	
}
void BankAccount::withdraw(){
	bool haveEnough = false; //we'll assume user doesn't have enough;
	updateBalance(); //get most recent balance.
	float amount; //amount to withdraw.
	cout << "Please enter amount to withdraw." << endl;
	cin >> amount;
	if (balance < amount){
		cout << "You don't have enough money to withdraw that amount!" << endl;
		return; //return so they can't withdraw any further. 
	}
	//got here so they must have enough money lets write this transaction to the history a copy paste of deposit but we -= balance instead of +=, and change some wording.
	fstream fs;
	//time info
	time_t seconds;
	seconds = time(NULL);
	tm  timeinfo;
	localtime_s(&timeinfo, &seconds);
	//get rid of some characters that append a new line in the time string. 
	char str[26];
	asctime_s(str, &timeinfo);
	string times = (string)str;
	times = times.substr(0, 24);
	fs.open("history.txt", fstream::out | fstream::in | fstream::app); //open fs for reading and writing in append mode. 
	if (!fs.is_open()){//if history is not there make one
		fs.open("history.txt", fstream::out | fstream::in | fstream::trunc);
		while (amount > (float)5000){//I'll limit it to 5000 per transaction.
			cout << "You can only withdraw $5000 at once, please enter a new amount." << endl;
			cin >> amount;
		}
		balance -= amount;
		fs << times << " Withdrawl: " << amount << " New Balance: " << balance << "\n";
	}
	else{
		while (amount > (float)5000){//I'll limit it to 5000 per transaction.
			cout << "You can only withdraw $5000 at once, please enter a new amount." << endl;
			cin >> amount;
		}
		balance -= amount;
		fs << times << " Withdrawl: " << amount << " New Balance: " << balance << "\n";
	}

}
void BankAccount::printHistory(){
	fstream fs;
	fs.open("history.txt", std::fstream::in);
	if (!fs){
		cout << "No history found." << endl;
		return;
	}
	else{
		string line;
		while (fs.good()){
			getline(fs, line);
			cout << line << endl;
		}
		fs.close();
	}
}
