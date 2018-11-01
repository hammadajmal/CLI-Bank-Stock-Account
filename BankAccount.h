#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include "Account.h"

class BankAccount: public Account{
public:
	void viewbalance();
	void deposit();
	void withdraw();
	void printHistory();
};
#endif