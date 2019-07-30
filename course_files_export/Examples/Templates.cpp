// Templates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdarg>

using namespace std;

////////// class TBubble
template <typename T>
class TBubble
{
	T* array;
	int count;
public:
	TBubble(int n) : count(n)
	{
		array = new T[count];
		Initialize();
	}
	void Exchange(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}
	void BubbleSort()
	{
		int x, y;
		for (x=1; x<count; ++x)
		{
			for (y=count-1; y>=x; --y)
			{
				if (array[y-1] > array[y])
					Exchange(array[y],array[y-1]);
			}
		}
	
	}
	void Show()
	{
		for (int i=0; i<count; i++)
			cout << array[i] << '\t';
	}
	void Initialize()
	{
		for (int c=0; c<count; c++)
			array[c] = rand() % 100;
	}
};
//////////

////////// Integer wrapper
class Wrapper
{
	int number;
public: 
	operator int() { return number; }
	void operator = (int t) { number = t; }
};
//////////

////////// Template Version
template <typename T>
void TExchange(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}

template <typename T>
void TBubbleSort(T* array, int count)
{
	int a, b;
	for (a=1; a<count; ++a)
	{
		for (b=count-1; b>=a; --b)
		{
			if (array[b-1] > array[b])
				Exchange(&array[b],&array[b-1]);
		}
	}
}

template <typename T>
void TShow(T* array, int count)
{
	int i;
	for (i=0; i<count; i++)
		cout << array[i] << '\t';
}

template <typename T>
void TInitialize(T* array, int count)
{
	for (int c=0; c<count; c++)
		array[c] = (rand() % 100);
}
//////////

////////// Void* Version
void Exchange(void* a, void* b)
{
	int* va = (int*)a;
	int* vb = (int*)b;
	int temp = *va;
	*va = *vb;
	*vb = temp;
}

void BubbleSort(void* array, int count)
{
	int* vp = (int*)array;
	int a, b;
	for (a=1; a<count; ++a)
	{
		for (b=count-1; b>=a; --b)
		{
			if (vp[b-1] > vp[b])
				Exchange(&vp[b],&vp[b-1]);
		}
	}
}

void Show(void* array, int count)
{
	int i;
	int* vp = (int*)array;
	for (i=0; i<count; i++)
		cout << vp[i] << '\t';
}

void Initialize(void* array, int count)
{
	int* vp = (int*)array;
	for (int c=0; c<count; c++)
		vp[c] = rand() % 100;
}

////////// Integer Version
void Exchange(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(int* array, int count)
{
	int a, b;
	for (a=1; a<count; ++a)
	{
		for (b=count-1; b>=a; --b)
		{
			if (array[b-1] > array[b])
				Exchange(&array[b],&array[b-1]);
		}
	}
}

void Show(int* array, int count)
{
	int i;
	for (i=0; i<count; i++)
		cout << array[i] << '\t';
}

void Initialize(int* array, int count)
{
	for (int c=0; c<count; c++)
		array[c] = rand() % 100;
}
//////////

void StdArgShow(int n, ...)
{
	va_list list;
	va_start(list, n);
	for (int x = 0; x < n; x++)
	{
		int number = va_arg(list, int);
		cout << number << '\t';
	}
	cout << endl;
	va_end(list);
}

template <typename T>
void Tshow(const T& value)
{
	cout << value << '\t';
}

template <typename U, typename... T>
void Tshow(const U& head, const T&... tail)
{
	cout << head;
	Tshow(tail...);
}

void function6()
{
	StdArgShow(3,1, 2, 3);
	StdArgShow(5, 9, 12, -1, 5, 123);
	Tshow(3, 1, 2, 3);
	Tshow(5, 9, 12, -1, 5, 123);
}

// template class with user-defined
void function5()
{
	cout << "<<< function5 >>>" << endl;
	int size = 10;
	TBubble<Wrapper> bubble(size);
	cout << "Before: " << endl;
	bubble.Show();
	bubble.BubbleSort();
	cout << "\nAfter: " << endl;
	bubble.Show();
}

// template class with intrinsic
void function4()
{
	cout << "<<< function4 >>>" << endl;
	int size = 10;
	TBubble<int> bubble(size);
	cout << "Before: " << endl;
	bubble.Show();
	bubble.BubbleSort();
	cout << "\nAfter: " << endl;
	bubble.Show();
}

// template using user-defined
void function3()
{
	cout << "<<< function3 >>>" << endl;
	const int size = 10;
	Wrapper array[size];
	TInitialize(array,size);
	cout << "Before: " << endl;
	TShow(array,size);
	TBubbleSort(array,size);
	cout << "\nAfter: " << endl;
	TShow(array,size);
}

// template using intrinsic
void function2()
{
	cout << "<<< function2 >>>" << endl;
	const int size = 10;
	int array[size];
	TInitialize(array,size);
	cout << "Before: " << endl;
	TShow(array,size);
	TBubbleSort(array,size);
	cout << "\nAfter: " << endl;
	TShow(array,size);
}

// void* array
void function1()
{
	cout << "<<< function1 >>>" << endl;
	const int size = 10;
	int array[size];
	void* vp = (void*)array;
	Initialize(vp,size);
	cout << "Before: " << endl;
	Show(vp,size);
	BubbleSort(vp,size);
	cout << "\nAfter: " << endl;
	Show(vp,size);
}

// integer array
void function0()
{
	cout << "<<< function0 >>>" << endl;
	const int size = 10;
	int array[size];
	Initialize(array,size);
	cout << "Before: " << endl;
	Show(array,size);
	BubbleSort(array,size);
	cout << "\nAfter: " << endl;
	Show(array,size);
}

void main()
{
	function0();
	function1();
	function2();
	function3();
	function4();
	function5();
	function6();
}

