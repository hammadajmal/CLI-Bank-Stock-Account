#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;
class Node {
	friend class LinkedList;
public:
	Node(string& name, float price, float totalValue, int noShares)
		:itemName(name), itemNo(price), value(totalValue), numberShares(noShares)
	{
		this->next = NULL;
		this->prev = NULL;
	}
	string itemName;  //stock name.
	float itemNo; //stock price
	float value; //itemNo * numberShares
	int numberShares;
	Node *next;
	Node *prev;

};
#endif