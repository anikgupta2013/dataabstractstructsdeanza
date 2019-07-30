// Recursion.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <array>

using namespace std;

template <typename T>
class Node
{
public:
	T value;
	Node *prev;
	Node() { prev = NULL; value = INT_MIN; }
	Node(T t) { prev = NULL; value = t; }
};

template <typename T>
class Stack
{
	Node<T>* top;
public:
	Stack() { top = NULL; }
	Stack(T t) { Push(t); }
	void Push(T value)
	{
		cout << "Pushing " << value << endl;
		Node<T>* temp = new Node<T>(value);
		if (!top)
		{
			top = temp;
			top->prev = NULL;
		}
		else
		{
			temp->prev = top;
			top = temp;
		}
	}
	T Pop()
	{
		if (top)
		{
			T value = top->value;
			Node<T>* deleteMe = top;
			top = top->prev;
			cout << "Popping " << value << endl;
			delete deleteMe;
			return value;
		}
		return NULL;
	}
	Node<T>* Top()
	{
		return top;
	}
	bool Empty()
	{
		return top == NULL;
	}
};

void Output(Node<int>* node)
{
	if (node)
	{
		cout << node->value << endl;
		Output(node->prev);
	}
}

void Iterative(Stack<int>& stack)
{
	while (!stack.Empty())
	{
		int value = stack.Pop();
		cout << value << endl;
	}
}

void Recursive(Stack<int>& stack)
{
	Output(stack.Top());
}

void StackFunction()
{
	Stack<int> stack;
	int count = 0;
	while (count < 5)
	{
		stack.Push(rand() % 100 + 1);
		count++;
	}
	Iterative(stack);
	count = 0;
	while (count < 5)
	{
		stack.Push(rand() % 100 + 1);
		count++;
	}
	Recursive(stack);
}

int Add(int& sum, int number)
{
	if (number)
	{
		cout << "Addit:  number = " << number << endl;
		Add(sum+=number,number-1);
	}
	return sum;
}

void Forwards(char begin, char end)
{
	if ( begin <= end )
	{
		cout << begin;
		Forwards(begin+1, end);
	}
}

void Backwards(char begin, char end)
{
	if (begin <= end)
	{
		Backwards(begin+1,end);
		cout << begin;
	}
}

void BitShow(int number)
{
	if (number)
	{
		cout << "BitShow:  number = " << number << endl;
		BitShow(number >> 1);
		if (number%2)
			cout << "1";
		else
			cout << "0";
	}
}

int BinarySearch(array<string,10>& base, string target, int first, int last)
{
	cout << "Calling Binary search " << first << '\t' << last << endl;
	int index;
	if (first > last)
		index = -1; 
	else
	{
		int mid = first + (last - first) / 2;
		if (target.compare(base[mid]) == 0)
			index = mid; 
		else if (target < base[mid])
			index = BinarySearch(base, target, first, mid - 1);
		else
			index = BinarySearch(base, target, mid + 1, last);
	} 

	return index;
}  

void main()
{
	array<string,10> planets =
	{
		"Ceres",
		"Earth",
		"Jupiter",
		"Mars",
		"Mercury",
		"Neptune",
		"Pluto",
		"Saturn",
		"Uranus",
		"Venus",
	};

	char a = 'a';
	char z = 'z';
	Forwards(a, z);
	cout << endl;

	Backwards(a, z);
	cout << endl;

	int sum = 0, number = 10;
	int total = Add(sum, number);
	cout << "the sum is: " << total << endl;

	number = 10;
	BitShow(number);
	cout << endl;

	int index = BinarySearch(planets, "Saturn", 0, planets.size());
	cout << planets[index];

	StackFunction();
}