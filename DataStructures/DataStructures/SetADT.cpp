#include "pch.h"
#include <iostream>
using namespace std;

struct node {
	int data;
	int count;
	node *next;
};

class Set {
private:
	node * head;
	int size;
public:
	Set() : size(1)
	{
		head = new node;
		head->next = head;
	}
	~Set()
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
			bool added = false;

			node *temp = head;
			while (head != temp->next) {
				if (temp->next->data == x) {
					temp->next->count++;
					added = true;
					break;
				}
				temp = temp->next;
			}
			if (!added) {
				node *adding = new node;
				adding->data = x;
				adding->next = head;
				adding->count = 1;
				temp->next = adding;
				temp = adding;
				size++;
			}
		}
	}
	void CreateSorted() {
		int x;
		while (cin >> x, x != -1)
		{
			node *temp1 = head;
			node *temp2 = head->next;

			while (temp1->next != head && x > temp2->data) {
				temp1 = temp2;
				temp2 = temp2->next;
			}
			if (temp1->next == head || x < temp2->data) {
				node *adding = new node;
				adding->data = x;
				adding->count = 1;

				adding->next = temp2;
				temp1->next = adding;
			}
			else (temp2->count)++;
		}
	}

	void Insert(int item) {
		node *temp = head;

		while (head != temp->next) {
			temp = temp->next;
		}

		node *adding = new node;
		adding->data = item;
		adding->next = head;
		temp->next = adding;
		size++;
	}
	void InsertAt(int item, int index) {
		if (index > size) {
			Insert(item);
			return;
		}

		node *temp = head;

		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}

		node *adding = new node;
		adding->data = item;
		adding->next = temp->next;
		temp->next = adding;
		size++;
	}
	void InsertNode(node *adding) {
		node *temp = head;
		while (temp->next != head) {
			temp = temp->next;
		}
		temp->next = adding;
		adding->next = head;
	}

	void Delete(int item) {
		node *temp = head;
		node *toDelete = temp->next;

		while (head != temp->next) {
			if (toDelete->data == item) {
				temp->next = toDelete->next;
				delete toDelete;
				return;
			}
			toDelete = toDelete->next;
			temp = temp->next;
		}
	}

	node *Contains(int item) {
		node *temp = head;
		while (head != temp->next) {
			if (temp->next->data == item) {
				return temp->next;
			}
			temp = temp->next;
		}
		return nullptr;
	}

	bool CheckForSub(Set *set) {
		node *start = set->head;
		node *chechking = set->head->next;

		while (start->next != set->head) {
			node *temp = Contains(chechking->data);
			if (temp != nullptr && chechking->count > temp->count) {
				return false;
			}
			else if (temp == nullptr) {
				return false;
			}
			chechking = chechking->next;
			start = start->next;
		}
		return true;
	}
	friend bool IsSubset(Set *set, Set *subset) {
		node *subHead = subset->head;
		node *sub = subHead->next;
		node *set1 = set->head->next;

		while (subHead->next != subset->head) {
			if (sub->data != set1->data || sub->count > set1->count) {
				return false;
			}
			subHead = subHead->next;
			sub = sub->next;
			set1 = set1->next;
		}
		return true;
	}

	void Union(Set *set) {
		node *start = set->head;
		node *set2Node = start->next;

		while (start->next != head) {
			if (set2Node == nullptr) return;

			node *temp = Contains(set2Node->data);

			if (temp != nullptr) {
				temp->count = (temp->count > set2Node->count) ? temp->count : set2Node->count;
			}
			else {
				InsertNode(set2Node);
			}

			start = start->next;
			set2Node = set2Node->next;
		}

	}
	friend Set *Union(Set *set1, Set *set2) {
		node *head1 = set1->head;
		node *head2 = set2->head;
		node *t1 = head1->next;
		node *t2 = head2->next;
		Set *result = new Set;
		node *setHead = result->head;

		while (head1->next != set1->head || head2->next != set2->head) {
			if (head1->next == set1->head || t1->data > t2->data) {
				node *adding = new node;
				adding->data = t2->data;
				adding->count = t2->count;

				setHead->next = adding;
				setHead = adding;

				t2 = t2->next;
				head2 = head2->next;
			}
			else if (head2->next == set2->head || t1->data < t2->data) {
				node *adding = new node;
				adding->data = t1->data;
				adding->count = t1->count;

				setHead->next = adding;
				setHead = adding;

				t1 = t1->next;
				head1 = head1->next;
			}
			else {
				node *adding = new node;
				adding->data = t1->data;
				adding->count = t1->count + t2->count;

				setHead->next = adding;
				setHead = adding;

				t1 = t1->next;
				head1 = head1->next;
				t2 = t2->next;
				head2 = head2->next;
			}
		}
		setHead->next = result->head;
		return result;
	}
	friend Set *Intersect(Set *set1, Set *set2) {
		node *head1 = set1->head;
		node *head2 = set2->head;
		node *t1 = head1->next;
		node *t2 = head2->next;
		Set *result = new Set;
		node *setHead = result->head;

		while (head1->next != set1->head && head2->next != set2->head) {
			if (t1->data < t2->data) {
				t1 = t1->next;
				head1 = head1->next;
			}
			else if (t1->data > t2->data) {
				t2 = t2->next;
				head2 = head2->next;
			}
			else {
				node *adding = new node;
				adding->data = t1->data;
				adding->count = (t1->count > t2->count) ? t2->count : t1->count;

				setHead->next = adding;
				setHead = adding;

				t1 = t1->next;
				head1 = head1->next;
				t2 = t2->next;
				head2 = head2->next;
			}
		}
		setHead->next = result->head;
		return result;
	}
	
	void Print() {
		node *temp = head->next;
		while (temp != head) {
			cout << temp->data << "-(" << temp->count << ") ";
			temp = temp->next;
		}
		cout << endl << endl;
	}
};