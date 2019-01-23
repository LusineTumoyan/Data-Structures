#include "pch.h"
#include <iostream>
using namespace std;

int GCD(int a, int b) {
	if (a < b) {
		int c = a;
		a = b;
		b = c;
	}
	while (b != 0) {
		if (a % b == 0) return b;
		b--;
	}
}

struct node {
	int data;
	node *next;
};

class ListInt {
private:
	node * head;
	int size;
public:
	ListInt() :size(1)
	{
		head = new node;
		head->next = NULL;
	}
	~ListInt()
	{
		node *temp;
		while (head) {
			temp = head->next;
			delete head;
			head = temp;
		}
	}

	void Create() {
		node *temp = head;

		int x;
		while (cin >> x, x != -1) {
			node *adding = new node;
			adding->data = x;
			adding->next = NULL;

			temp->next = adding;
			temp = adding;

			size++;
		}
	}
	void CreateDescending() {
		int x;
		while (cin >> x, x != -1) {
			node *w1 = head->next;
			node *w2 = head;
			node *adding;

			while (w1 != NULL && w1->data < x) {
				w2 = w1;
				w1 = w1->next;
			}

			if (w1 == NULL || w1->data >= x) {
				adding = new node;
				adding->data = x;

				adding->next = w1;
				w2->next = adding;
				size++;
			}

		}
	}

	void Insert(int item) {
		node *adding = new node;
		adding->data = item;

		node *temp = head;
		while (temp->next) {
			temp = temp->next;
		}

		temp->next = adding;
		size++;
	}
	void InsertAt(int item, int index) {
		if (index < size) {
			node *adding = new node;
			adding->data = item;

			node *temp = head;
			for (int i = 0; i < index; i++)
			{
				temp = temp->next;
			}

			adding->next = temp->next;
			temp->next = adding;
			size++;
		}
		else {
			node *adding = new node;
			adding->data = item;

			node *temp = head;
			while (temp->next) {
				temp = temp->next;
			}

			temp->next = adding;
			size++;
		}
	}

	int Delete(int item) {
		node *before = head;
		node *deleting = head->next;

		while (deleting) {
			if (deleting->data == item) {
				int deleted = deleting->data;
				node *temp = deleting->next;

				delete deleting;
				before->next = temp;
				size--;
				return deleted;
			}
			before = before->next;
			deleting = deleting->next;
		}
		exit(1);
	}
	int DeleteAt(int index) {
		if (index > size) {
			exit(1);
		}

		node *before = head;
		node *deleted = head->next;
		int deletedData;

		for (int i = 0; i < index - 1; i++)
		{
			before = before->next;
			deleted = deleted->next;
		}

		deletedData = deleted->data;
		before->next = deleted->next;
		delete deleted;
		size--;
		return deletedData;
	}

	ListInt *Combine(ListInt *&list) {
		ListInt *result = new ListInt;
		node *head1 = head->next;
		node *head2 = list->head->next;
		node *last = result->head;

		while (head1 || head2) {
			if (head1 == NULL) {
				node *adding = new node;
				adding->next = NULL;
				adding->data = head2->data;

				last->next = adding;
				last = adding;

				head2 = head2->next;
				result->size++;
			}
			else if (head2 == NULL) {
				node *adding = new node;
				adding->next = NULL;
				adding->data = head1->data;

				last->next = adding;
				last = adding;

				head1 = head1->next;
				result->size++;
			}
			else if (head1->data > head2->data) {
				node *adding = new node;
				adding->next = NULL;
				adding->data = head2->data;

				last->next = adding;
				last = adding;

				head2 = head2->next;
				result->size++;
			}
			else if (head1->data <= head2->data) {
				node *adding = new node;
				adding->next = NULL;
				adding->data = head1->data;

				last->next = adding;
				last = adding;

				head1 = head1->next;
				result->size++;
			}
		}
		return result;
	}

	int MaxDiv() {
		node *temp1 = head->next;
		node *temp2 = temp1->next;
		int maxDiv;

		if (size == 1) return 0;
		if (size == 2) return temp1->data;

		maxDiv = temp1->data;
		while (temp2) {
			maxDiv = GCD(maxDiv, temp2->data);
			temp2 = temp2->next;
		}
		return maxDiv;
	}

	void Print() {
		node *temp = head->next;
		while (temp) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl << endl;
	}
};