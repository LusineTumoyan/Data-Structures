#include "pch.h"
#include <iostream>
using namespace std;

struct node {
	char data;
	node *next;
	node *previous;
};

class ListString {
private:
	node * head;
	node * tail;
	int size;
public:
	ListString() : size(1)
	{
		head = new node;
		head->next = nullptr;
		head->previous = nullptr;
		tail = head;
	}
	~ListString()
	{
		node *temp;
		while (head) {
			temp = head->next;
			delete head;
			head = temp;
		}
		size = 0;
	}

	void Create() {
		char x;
		while (cin >> x, x != 'q') {
			node *adding = new node;
			adding->data = x;
			adding->previous = tail;
			adding->next = NULL;

			tail->next = adding;
			tail = adding;
			size++;
		}
	}

	void Insert(char x) {
		node *adding = new node;
		adding->data = x;
		adding->previous = tail;
		adding->next = NULL;
		tail->next = adding;
		tail = adding;
		size++;
	}
	void InsertAt(char x, int index) {
		if (index > size) {
			Insert(x);
			return;
		}

		node *temp = head;
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}

		node *adding = new node;
		adding->data = x;
		adding->previous = temp;
		adding->next = temp->next;
		temp->next = adding;
		adding->next->previous = adding;
		size++;
	}

	ListString *Concat(ListString *&myList) {
		node *temp = myList->head->next;

		while (temp) {
			temp->previous = tail;
			tail->next = temp;
			tail = temp;
			temp = temp->next;
			size++;
		}
		return this;
	}

	int Find(ListString *&sub) {
		if (sub == NULL || sub->size > size || sub->size == 1) {
			return -1;
		}

		int index;
		bool found;
		node *temp1 = head;
		node *temp2;
		node *temp11;

		for (int i = 0; i < size - sub->size + 1; i++)
		{
			temp1 = temp1->next;
			temp2 = sub->head->next;
			index = i;
			found = true;
			temp11 = temp1;

			while (temp2) {
				if (temp11->data != temp2->data) {
					found = false;
					break;
				}
				temp11 = temp11->next;
				temp2 = temp2->next;
			}
			if (found) break;
		}
		if (found) return index;
		return -1;
	}

	void Reverse() {
		node *temp1 = head->next;
		node *temp2 = tail;
		int myData;

		for (int i = 0; i < size / 2; i += 2)
		{
			myData = temp1->data;
			temp1->data = temp2->data;
			temp2->data = myData;

			temp1 = temp1->next;
			temp2 = temp2->previous;
		}
	}
	
	void AddSymbol() {
		node *temp = head;
		head->data = 'a';

		while (temp) {
			bool number = false;
			if (temp->next != nullptr && temp->data == 'a' && temp->next->data != 'a') {
				node *end = temp->next;
				while (end != nullptr && end->data != 'a') {
					number = true;
					if (end->data > '9' || end->data < '0') {
						number = false;
						break;
					}
					end = end->next;
				}
				if (number) {
					node *adding = new node;
					adding->data = '$';

					adding->previous = temp;
					adding->next = temp->next;
					temp->next = adding;
					adding->next->previous = adding;

					temp = end;
				}
			}
			if (!number) temp = temp->next;
		}
	}

	void Print() {
		node *temp = head->next;

		while (temp) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};
