/*
Name: Pooja Shende
Desc: Implementation of doubly linked list to store play list by
      perfoming various operations of dll.
*/



#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H


#include<iostream>
#include<string>
using namespace std;


class DoublyLinkedList
{
public:
	class Node
	{
	public:
		Node *next;
		Node *prev;
		string *data;
		
		Node();
		Node(Node *, Node *, string *);
		~Node();
	};

	DoublyLinkedList();
	~DoublyLinkedList();

	bool empty();
	void append(string& );
	void insertBefore(string& );
	void insertAfter(string& );
	void remove(string& );
	void begin();
	void end();
	bool next();
	bool prev();
	bool find(string& );
	const string& getData();

private:
	Node* head;  //node pointer pointing to the first node
	Node* tail;  //node pointer pointing to the last node
	Node* current; //node pointer pointing to the curent node
};


#endif
