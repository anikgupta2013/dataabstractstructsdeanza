
#include <iostream>
#include "ConsoleColor.h"
using namespace std;

class BinarySearchTree
{
	int* array;
	int size;
public:
	BinarySearchTree(int s) : size(s)
	{
		size = reSize(size);
		array = new int[size];
		for (int x = 0; x < size; x++) 
			array[x] = NULL;
	}
	int reSize(int x) 
	{
		int value = pow(2, x);
		return value;
	}
	void insert(int x) 
	{
		int currentIndex = 0;
		cout << red << "\n-->insert: " << x << endl;
		while (true) 
		{
			if (array[currentIndex] == NULL) 
			{
				array[currentIndex] = x;
				cout << blue << "Inserted @ index: " << currentIndex << endl;
				break;
			}
			else if (x < array[currentIndex]) 
			{
				currentIndex = (2 * currentIndex + 1);
				cout << green << " <<< Left " << currentIndex << endl;
			}
			else  
			{
				currentIndex = (2 * currentIndex + 2);
				cout << yellow << " Right >>> " << currentIndex << endl;
			}
		}
	}
	void search(int x) 
	{
		cout << red << "Search: " << x << endl;
		int currentIndex = 0;
		while (true) 
		{
			if (array[currentIndex] == NULL) 
			{
				cout << red << "Not Found" << endl;
				break;
			}
			if (array[currentIndex] == x) 
			{
				cout << blue << "Found at index: " << currentIndex << endl;
				break;
			}
			else if (x < array[currentIndex]) 
			{
				cout << green << " <<< Left " << endl;
				currentIndex = (2 * currentIndex + 1);
			}
			else 
			{
				cout << yellow << " >>> Right " << endl;
				currentIndex = (2 * currentIndex + 2);
			}
		}
	}
	void parent(int x) 
	{
		while (x != 0) 
		{
			x = (x - 1) / 2;
			cout << "---|";
		}
	}
	void inOrder(int currentIndex) 
	{
		if (array[currentIndex] != NULL) 
		{
			inOrder(2 * currentIndex + 1);
			parent(currentIndex);
			cout << array[currentIndex] << endl;
			inOrder(2 * currentIndex + 2);
		}
	}
	void preOrder(int currentIndex)
	{
		if (array[currentIndex] != NULL)
		{
			parent(currentIndex);
			cout << array[currentIndex] << " " << endl;
			preOrder(2 * currentIndex + 1);
			preOrder(2 * currentIndex + 2);
		}
	}
	void postOrder(int currentIndex) 
	{
		if (array[currentIndex] != NULL) 
		{
			postOrder(2 * currentIndex + 1);
			postOrder(2 * currentIndex + 2);
			parent(currentIndex);
			cout << array[currentIndex] << " " << endl;
		}
	}
	void printArray()
	{
		int exp = 1;
		int sum = int(pow(2, exp));
		int power = sum;
		for (int i = 0; i < size; i++)
		{
			if (i == sum)
			{
				cout << red << "| " << endl;
				exp++;
				power = int(pow(2, exp));
				sum += power;
			}
			if (array[i])
			{
				(i % 2) ? cout << green << array[i] << ' ' : cout << yellow << array[i] << ' ';
			}
			else
			{
				cout << blue << ". ";
			}
		}
		cout << white << endl;
	}
};

int main() 
{
	int array[] = { 42, 68, 35, 1, 70, 25, 79, 59, 63, 65 };
	int size = sizeof(array) / sizeof(array[0]);
	int asize = log(size*size) / log(2);
	BinarySearchTree bst(asize);
	for (int i = 0; i < size; i++)
		bst.insert(array[i]);
	cout << endl;
	cout << blue << "Inorder" << yellow << endl;
	bst.inOrder(0);
	cout << blue << "Preorder" << yellow << endl;
	bst.preOrder(0);
	cout << blue << "Postorder" << yellow << endl;
	bst.postOrder(0);
	cout << blue << "\nSearch" << yellow << endl;
	bst.search(65);
	cout << "\nIn memory" << endl;
	bst.printArray();
}