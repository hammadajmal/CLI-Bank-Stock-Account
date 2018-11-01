#include "Linked List.h"
#include <iostream>
using namespace std;
LinkedList::LinkedList() {
	myHead = NULL; //initial default values.
	myTail = NULL;
	mySize = 0;
}

LinkedList::~LinkedList() {
	//Delete everything
	Node *curr; //current node.
	Node *next; //next node
	curr = myHead; //start with the head.
	while (curr != myTail) {
		next = curr->next; // set next to be the next node.
		delete curr; //free the current node.
		curr = next; //move on with the list by setting the current node to the next one.
	}
	delete myTail;//simply delete the tail at the end.
}

int LinkedList::size() const
{
	return mySize; //return current size.
}

void LinkedList::addToStart(Node *n)
{
	if(mySize == 0){		
		myHead = n; //just set the head to the new node.
		myTail = n; //tail is also the same
		mySize++;
	}
	else{
		Node* curr; //current node.
		curr = myHead; //set curr to the old head.
		myHead = n; //set new head to n.
		myHead->next = curr; //set the new heads next node to the old head.
		curr->prev = myHead; //set the old head's prev to the new head.
		mySize++;//increase size by one since we added.
	}
}

void LinkedList::addToEnd(Node *n)
{
	if (mySize == 0) {
		addToStart(n); //no head so the end is also the start.
		return;
	}
	myTail->next = n; //set the current ends next item to the new node.
	Node *prev = myTail; //save this to set the new tails previous to the current tail.
	myTail = myTail->next; //set the current end to the new end.
	myTail->prev = prev; //set the new tails prev to the old tail. 
	mySize++; //added a node so increase size.
	//sort the list based on user selection.
	if (choice == 1){
		selectionSort();
	}
	if (choice == 2){
		insertionSort();
	}
}

void LinkedList::printList()
{
	cout << "\nList" << endl;
	cout << "Stock Name Stock Price" << endl;
	Node* curr = myHead; //current node.
	while (curr != NULL) { //keep going till we hit end of list.
		cout << curr->itemName << "       " << curr->itemNo << endl;
		curr = curr->next;
	}
	cout<<endl;
}

bool LinkedList::removeFromStart()
{
	if (myHead != NULL) {
		Node *curr = myHead;
		myHead = myHead->next; //simply set the head to the next item in the list.
		delete curr; //delete the old head.
		mySize--;
		return true; //we were able to complete this.
	}
	return false; //weren't able to do this since there is nothing at the head.
}

bool LinkedList::removeFromEnd()
{
	if (mySize == 0) return false; //weren't able to do this since there was nothing at end.
	if (mySize == 1){
		removeFromStart();
		return true;
	}
	Node* curr; //current node.
	Node* prev; //this will be the previous node.
	curr = myHead; //set current to be the head of the list.
	prev = myHead;
	while (curr->next != NULL) {
		prev = curr; //set the previous node to be the current node.
		curr = curr->next; //set curr to be the next node.
	}
	myTail = prev; //prev will not contain the node just before my tail, so to remove the tail just set my tail to the previous node.
	myTail->next = NULL; //make sure this is the new end.
	delete curr; //delete the old tail.
	mySize--;
	return true; //success.
}

/*void LinkedList::removeNodeFromList(float rem)
{
	Node * curr; //current node.
	Node * next; //next node.
	Node * prev; //previous node.
	curr = myHead;
	while (curr->itemNo != rem&&curr!=NULL) {//this will keep going until curr has the correct item number to remove.
		prev = curr; //set prev to current node.
		curr = curr->next; //move on with the list.
	}
	if (curr == NULL) { //reached the end of the list and item was not found.
		cout << "This stock price was not found.";
		return;
	}
	if (curr == myHead) {
		removeFromStart();
		return;
	}
	//after we find the correct node lets set next to the next node.
	next = curr->next;
	//now we simply set the current node's previous node to its next node thus skipping it in the list and finally delete it.
	prev->next = next;
	next->prev = prev; // opposite of above.
	delete curr;
	mySize--;
}*/

void LinkedList::removeNodeFromList(string rem) //same as the one with int but do a check for item name instead of number
{
	Node * curr; //current node.
	curr = myHead;
	while (curr->itemName != rem && curr != NULL) {
		curr = curr->next; //move on with the list.
	}
	if (curr == NULL) { //reached the end of the list and item was not found.
		cout << "This stock was not found.";
		return;
	}
	if (curr == myHead) {
		removeFromStart();
		return;
	}
	//now we simply set the current node's previous node to its next node thus skipping it in the list and finally delete it.
	curr->prev->next = curr->next;
	delete curr;
	mySize--;
}

void LinkedList::selectionSort(){
	//this algorithm will sort the linked list.
	Node *i; //used for finding next smallest
	Node *j; //used for current smallest
	//go through entire list.
	for (j = myHead; j!=NULL; j=j->next){
		//find the min element.
		Node *iMin = j; //assume first element is minimum.
		//test against elements after j to find the smallest. 
		for (i = j->next; i !=NULL; i = i->next){
			//if new element is less than j
			if (i->value > iMin->value) iMin = i; //new minimum
		}
		if (iMin != j){
			//need to swap nodes
			swap(iMin, j);
		}
	}
}
void LinkedList::insertionSort(){
	Node *i;
	Node *j;
	for (j = myHead->next; j != NULL; j = j->next){
		i = j;//set new node to j
		while (i != myHead && i->prev->value < i->value){
			swap(i, i->prev);//swap i and j.
			i = i->prev;//move backwards from current j.
		}
	}
}
void LinkedList::swap(Node *a, Node *b){
	//lets just swap the values that would effectively swap the nodes.
	float temp = a->itemNo;
	string tmp = a->itemName;
	float temp1 = a->numberShares;
	float temp2 = a->value;
	a->itemNo = b->itemNo;
	a->itemName = b->itemName;
	a->value = b->value;
	a->numberShares = b->numberShares;
	b->itemName = tmp;
	b->itemNo = temp;
	b->numberShares = temp1;
	b->value = temp2;
}
