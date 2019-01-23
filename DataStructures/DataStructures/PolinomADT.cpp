#include "pch.h"
#include <iostream>
using namespace std;

struct node {
	int power;
	int coef;
	node *next;
};

class Polinom {
private:
	node * head;
public:
	Polinom()
	{
		head = new node;
		head->next = nullptr;
	}
	~Polinom()
	{
		node *temp;
		while (head) {
			temp = head->next;
			delete head;
			head = temp;
		}
	}

	void Create() {
		int power, coef;
		cout << "Enter coef and power, -1 to exit: ";

		while (cin >> coef, coef != -1) {
			cin >> power;
			if (coef != 0) {
				node *temp1 = head;
				node *temp2 = head->next;
				while (temp2 != nullptr && temp2->power > power) {
					temp1 = temp2;
					temp2 = temp2->next;
				}
				if (temp2 == nullptr || temp2->power < power) {
					node *adding = new node;
					adding->coef = coef;
					adding->power = power;

					adding->next = temp2;
					temp1->next = adding;
				}
				else {
					temp2->coef += coef;
				}
			}
		}
	}

	friend Polinom *Add(Polinom *p1, Polinom *p2) {
		node *t1 = p1->head->next;
		node *t2 = p2->head->next;
		Polinom *result = new Polinom;
		node *rHead = result->head;

		while (t1 != nullptr || t2 != nullptr) {
			if (t1 == nullptr || t1->power > t2->power) {
				node *adding = new node;
				adding->coef = t2->coef;
				adding->power = t2->power;

				rHead->next = adding;
				rHead = adding;
				t2 = t2->next;
			}
			else if (t2 == nullptr || t1->power < t2->power) {
				node *adding = new node;
				adding->coef = t1->coef;
				adding->power = t1->power;

				rHead->next = adding;
				rHead = adding;
				t1 = t1->next;
			}
			else {
				node *adding = new node;
				adding->coef = t1->coef + t2->coef;
				adding->power = t1->power;

				rHead->next = adding;
				rHead = adding;
				t1 = t1->next;
				t2 = t2->next;
			}
		}
		return result;
	}
	friend Polinom *Subtract(Polinom *p1, Polinom *p2) {
		node *t1 = p1->head->next;
		node *t2 = p2->head->next;
		Polinom *result = new Polinom;
		node *rHead = result->head;

		while (t1 != nullptr || t2 != nullptr) {
			if (t1 == nullptr || t1->power > t2->power) {
				node *adding = new node;
				adding->coef = -t2->coef;
				adding->power = t2->power;

				rHead->next = adding;
				rHead = adding;
				t2 = t2->next;
			}
			else if (t2 == nullptr || t1->power < t2->power) {
				node *adding = new node;
				adding->coef = t1->coef;
				adding->power = t1->power;

				rHead->next = adding;
				rHead = adding;
				t1 = t1->next;
			}
			else {
				node *adding = new node;
				adding->coef = t1->coef - t2->coef;
				adding->power = t1->power;

				rHead->next = adding;
				rHead = adding;
				t1 = t1->next;
				t2 = t2->next;
			}
		}
		return result;
	}

	Polinom Derivate() {
		node *temp = head->next;
		Polinom *derivative = new Polinom;
		node *pHead = derivative->head;

		while (temp) {
			if (temp->power == 0) continue;
			node *adding = new node;
			adding->coef = (temp->coef)*(temp->power);
			adding->power = temp->power - 1;

			pHead->next = adding;
			pHead = adding;

			temp = temp->next;
		}
		return *derivative;
	}

	void Print() {
		node *temp = head->next;
		while (temp != nullptr) {
			cout << temp->coef << "x^" << temp->power << "  ";
			temp = temp->next;
		}
		cout << endl << endl;
	}
};