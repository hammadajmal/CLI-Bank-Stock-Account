#include "Account.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void Account::updateBalance(){
	fstream fs;
	fs.open("history.txt", fstream::out | fstream::in | fstream::app); //open fs for reading and writing in append mode. 
	if (!fs.is_open()){//if history is not there make one
		fs.open("history.txt", fstream::out | fstream::in | fstream::trunc);
		fs << "Balance: " << balance << endl;
	}
	else{
		//get the last line
		string line;
		string last_line;
		while (getline(fs, line)) {
			bool is_empty = true;
			for (int i = 0; i < line.size(); i++) {
				char ch = line[i];
				is_empty = is_empty && isspace(ch);
			}
			if (!is_empty) {
				last_line = line;
			}
		}
		fs.close();
		fs.open("history.txt", fstream::out | fstream::in | fstream::app); //reopen fs to rewind state, it'll still only append.
		vector<string> tokens = split<string>(last_line, " ");// this contains the last line which has the balance info.
		if (tokens.empty())return; //no transaction has been made yet so balance is still 10000.
		balance = stof(tokens[tokens.size() - 1]);// get the current balance from the last line of history. 
	}
	fs.close();
}