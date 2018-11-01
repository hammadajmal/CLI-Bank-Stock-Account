#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
class LinkedList {
public:
	LinkedList();
	~LinkedList();
	int size() const;
	void addToStart(Node *);
	void addToEnd(Node *);
	void printList();
	bool removeFromStart();
	bool removeFromEnd();
	void removeNodeFromList(float);
	void removeNodeFromList(string);
	void selectionSort();//need this sort since every time we add we need to sort.
	void swap(Node *a, Node *b); //used for swapping nodes.
	void insertionSort();
	Node *myHead;
	Node *myTail;	
	int choice;
private:
	int mySize;
};
#endif