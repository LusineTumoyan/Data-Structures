#include "pch.h"
#include <iostream>
int Priority1(char);
int Priority2(char);

const int MaxSize = 100;
template <class T>

class Stack {
private:
	T arr[MaxSize];
	int top;
public:
	Stack() : top(-1) {};

	bool IsEmpty()
	{
		return top == -1;
	}
	bool IsFull()
	{
		return top == MaxSize;
	}

	void Push(T item)
	{
		if (!IsFull())
		{
			arr[++top] = item;
		}
		else std::cout << "Stack is full";
	}
	T Pop()
	{
		if (!IsEmpty())
		{
			T temp = arr[top];
			arr[top--] = 0;
			return temp;
		}
		else
		{
			exit(1);
		}
	}
	T Peek()
	{
		if (!IsEmpty())
		{
			return arr[top];
		}
	}

	void Print()
	{
		for (int i = 0; i <= top; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
};


void FindInfix()
{
	Stack<int> stack1;
	Stack<char> stack2;

	std::cout << (41 + 7 * 3 - (61 / 8 - 5) + 1) << std::endl;

	char infix[100] = { "(41 + 7 * 3 - (61 / 8 - 5) + 1)" };
	char *ptr = infix;

	while (*ptr != '\0')
	{
		if (*ptr == ' ')
		{
			ptr++;
			continue;
		}
		if (*ptr != '+' && *ptr != '-' && *ptr != '*' && *ptr != '/' && *ptr != '(' && *ptr != ')')
		{
			int temp = *ptr - 48;
			while (*(ptr + 1) - 48 <= 9 && *(ptr + 1) - 48 >= 0)
			{
				temp = temp * 10 + *(ptr + 1) - 48;
				ptr++;
			}
			stack1.Push(temp);
			ptr++;
		}
		else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/' || *ptr == '(')
		{
			while (true) {
				if (Priority1(*ptr) > Priority2(stack2.Peek()) || stack1.IsEmpty())
				{
					stack2.Push(*ptr);
					ptr++;
					break;
				}
				else if (Priority1(*ptr) <= Priority2(stack2.Peek()))
				{
					char ch = '\0';
					switch (stack2.Pop())
					{
					case '+':
						ch = stack1.Pop();
						stack1.Push(stack1.Pop() + ch);
						break;
					case '-':
						ch = stack1.Pop();
						stack1.Push(stack1.Pop() - ch);
						break;
					case '*':
						ch = stack1.Pop();
						stack1.Push(stack1.Pop() * ch);
						break;
					case '/':
						ch = stack1.Pop();
						stack1.Push(stack1.Pop() / ch);
						break;
					}
				}
			}
		}
		else if (*ptr == ')')
		{
			while (Priority1(*ptr) <= Priority2(stack2.Peek()) && !stack1.IsEmpty())
			{
				char ch = '\0';
				switch (stack2.Pop())
				{
				case '+':
					ch = stack1.Pop();
					stack1.Push(stack1.Pop() + ch);
					break;
				case '-':
					ch = stack1.Pop();
					stack1.Push(stack1.Pop() - ch);
					break;
				case '*':
					ch = stack1.Pop();
					stack1.Push(stack1.Pop() * ch);
					break;
				case '/':
					ch = stack1.Pop();
					stack1.Push(stack1.Pop() / ch);
					break;
				}
			}
			stack2.Pop();
			ptr++;
		}
	}

	stack1.Print();
	stack2.Print();
}

int Priority1(char ch)
{
	if (ch == '+' || ch == '-') return 1;
	if (ch == '/' || ch == '*') return 2;
	if (ch == '(') return 3;
	if (ch == ')') return 0;
}
int Priority2(char ch)
{
	if (ch == '+' || ch == '-') return 1;
	if (ch == '/' || ch == '*') return 2;
	if (ch == '(') return -1;
	if (ch == ')') return 0;
}