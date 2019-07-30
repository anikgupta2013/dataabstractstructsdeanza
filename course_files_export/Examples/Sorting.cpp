#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <chrono>
#include "ConsoleColor.h"

using namespace std::chrono;
using namespace std;

string animals[] =
{
	"Zebra",
	"Xray",
	"Turtle",
	"Rabbit",
	"Monkey",
	"Kangaroo",
	"Giraffe",
	"Fox",
	"Elephant",
	"Bison"
};

template <typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
void Reverse(T* tarray, int size)
{
	for (int i = 0; i < size; i += 2)
		Swap(tarray[i], tarray[size - i - 1]);
}

template<typename T>
int partition(T* bag, int first, int last)
{
	T x = bag[last];
	int i = first - 1;
	for (int j = first; j < last; j++)
	{
		if (bag[j] <= x)
			i = i + 1;
		Swap(bag[i], bag[j]);
	}
	Swap(bag[i + 1], bag[last]);
	return i + 1;
}

/*
A quick sort first selects a value, which is called the pivot value.  
The role of the pivot value is to assist with splitting the list. 
The actual position where the pivot value belongs in the final 
sorted list, commonly called the split point, will be used to 
divide the list for subsequent calls to the quick sort. The goal 
of the partition process is to move items that are on the wrong 
side with respect to the pivot value while also converging on 
the split point.
*/
template <typename T>
void quickSort(T* theArray, int first, int last)
{
	if (first < last)
	{
		int pivotIndex = partition(theArray, 0, last);
		quickSort(theArray, first, pivotIndex - 1);
		quickSort(theArray, pivotIndex + 1, last);
	}
}

/*
Shellsort, also known as Shell sort or Shell's method, 
is an in-place comparison sort. It can be seen as either 
a generalization of sorting by exchange (bubble sort) or 
orting by insertion (insertion sort). The method starts 
by sorting pairs of elements far apart from each other, 
then progressively reducing the gap between elements to 
be compared. Starting with far apart elements, it can 
move some out-of-place elements into position faster 
than a simple nearest neighbor exchange.
*/
template <typename T>
void shellSort(T* theArray, int size)
{
	int nswaps = 0;
	int pass = 0;
	for (int half = size / 2; half > 0; half = half / 2)
	{
		for (int unsorted = half; unsorted < size; unsorted++)
		{
			T nextItem = theArray[unsorted];
			int loc = unsorted;
			int start = loc;
			while ((loc >= half) && (theArray[loc - half] > nextItem))
			{
				theArray[loc] = theArray[loc - half];
				loc = loc - half;
				nswaps++;
			}
			Output(theArray, size, theArray[loc], theArray[start]);
			theArray[loc] = nextItem;
		}
		pass++;
	}
	cout << white << "Number of passes: " << pass << "\tNumber of swaps: " << nswaps << endl;
}

template <typename T>
int findIndexOfLargest(T* theArray, int size)
{
	int indexbig = 0;
	for (int currentIndex = 1; currentIndex < size; currentIndex++)
	{
		if (theArray[currentIndex] > theArray[indexbig])
		{
			indexbig = currentIndex;
		}
	}
	return indexbig;
}

/*
The algorithm divides the input list into two parts: 
the sublist of items already sorted, which is built 
up from left to right at the front (left) of the list, 
and the sublist of items remaining to be sorted that 
occupy the rest of the list. The algorithm proceeds 
by finding the smallest (or largest, depending on sorting 
order) element in the unsorted sublist, exchanging (swapping) 
it with the leftmost unsorted element (putting it in sorted 
order), and moving the sublist boundaries one element to the right.
*/
template <typename T>
void selectionSort(T* theArray, int size)
{
	int pass = 0;
	int nswaps = 0;
	for (int last = size - 1; last >= 1; last--)
	{
		int largest = findIndexOfLargest(theArray, last + 1);
		Swap(theArray[largest], theArray[last]); nswaps++;
		Output(theArray, size, theArray[last], theArray[largest]);
		pass++;
	}
	Output(theArray, size, theArray[0], theArray[size - 1]);
	cout << white << "Number of passes: " << pass << "\tNumber of swaps: " << nswaps << endl;
}

/*
Insertion sort iterates, consuming one input element each repetition, 
and growing a sorted output list. At each iteration, insertion sort 
removes one element from the input data, finds the location it belongs 
within the sorted list, and inserts it there. It repeats until no 
input elements remain.
*/
template <typename T>
void insertionSort(T* theArray, int size)
{
	int nswaps = 0;
	int pass = 1;
	for (int x = 1; x < size; x++)
	{
		T nextItem = theArray[x];
		int loc = x;
		while ((loc > 0) && (theArray[loc - 1] > nextItem))
		{
			if (theArray[loc] != theArray[loc - 1])
				Output(theArray, size, theArray[loc], theArray[loc - 1]);
			theArray[loc] = theArray[loc - 1];
			loc--;
			nswaps++;
		}
		theArray[loc] = nextItem;
		pass++;
	}
	Output(theArray, size, theArray[0], theArray[size - 1]);
	cout << white << "Number of passes: " << pass << "\tNumber of swaps: " << nswaps << endl;
}

/*
Shaker sort, also known as bidirectional bubble sort, cocktail sort, 
shaker sort (which can also refer to a variant of selection sort), 
ripple sort, shuffle sort, or shuttle sort, is a variation of bubble 
sort that is both a stable sorting algorithm and a comparison sort. 
The algorithm differs from a bubble sort in that it sorts in both 
directions on each pass through the list.
*/
template <typename T>
void shakerSort(T* theArray, int size)
{
	int nswaps = 0;
	int npasses = 0;
	for (int i = 0; i < size / 2; i++) 
	{
		bool swapped = false;
		for (int j = i; j < size - i - 1; j++) 
		{ //one way
			if (theArray[j] > theArray[j + 1]) 
			{
				Swap(theArray[j], theArray[j + 1]);
				Output(theArray, size, theArray[j], theArray[j + 1]);
				swapped = true;
				nswaps++;
			}
			npasses++;
		}
		for (int j = size - 2 - i; j > i; j--) 
		{ //and back
			if (theArray[j] < theArray[j - 1])
			{
				Swap(theArray[j], theArray[j - 1]);
				Output(theArray, size, theArray[j], theArray[j - 1]);
				swapped = true;
				nswaps++;
			}
			npasses++;
		}
		if (!swapped) break; //block (break if no element was swapped - the array is sorted)
	}
	cout << white << "Number of passes: " << npasses << "\tNumber of swaps: " << nswaps << endl;
}

/*
Bubble sort, sometimes referred to as sinking sort, 
is a simple sorting algorithm that repeatedly steps 
through the list to be sorted, compares each pair of 
adjacent items and swaps them if they are in the wrong 
order. The pass through the list is repeated until no 
swaps are needed, which indicates that the list is sorted. 
The algorithm, which is a comparison sort, is named for 
the way smaller or larger elements "bubble" to the top of the list.
*/
template <typename T>
void bubbleSort(T* theArray, int size)
{
	int nswaps = 0;
	int npasses = 0;
	for (int index = 0; index < size - 1; index++)
	{
		for (int jndex = 0; jndex < size - index - 1; jndex++)
		{
			if (theArray[jndex] > theArray[jndex + 1])
			{
				swap(theArray[jndex], theArray[jndex + 1]);
				Output(theArray, size, theArray[jndex], theArray[jndex + 1]);
				nswaps++;
			}
		}
		npasses++;
	}
	cout << white << "Number of passes: " << npasses << "\tNumber of swaps: " << nswaps << endl;
}

template <typename T>
void Output(T* theArray, int size, string a, string b)
{
	for (int i = 0; i < size; i++)
	{
		if (theArray[i] == a)
			cout << blue << '[' << theArray[i] << ']' << " ";
		else if (theArray[i] == b)
			cout << green << '[' << theArray[i] << ']' << " ";
		else
			cout << white << '[' << theArray[i] << ']' << " ";
	}
	cout << endl;
}

void main()
{
	system_clock::time_point tbegin = system_clock::now();
	cout << yellow << "\nBubble Sort" << white << endl;
	int size = sizeof(animals) / sizeof(animals[0]);
	bubbleSort(animals, size);
	system_clock::time_point tend = system_clock::now();
	cout << "Duration: " << static_cast<double>((tend - tbegin).count()) / 10000000.0 << endl;

	tbegin = system_clock::now();
	cout << yellow << "\nShaker Sort" << white << endl;
	Reverse(animals, size);
	shakerSort(animals, size);
	tend = system_clock::now();
	cout << "Duration: " << static_cast<double>((tend - tbegin).count()) / 10000000.0 << endl;

	tbegin = system_clock::now();
	cout << yellow << "\nInsertion Sort" << white << endl;
	Reverse(animals, size);
	insertionSort(animals, size);
	tend = system_clock::now();
	cout << "Duration: " << static_cast<double>((tend - tbegin).count()) / 10000000.0 << endl;

	tbegin = system_clock::now();
	cout << yellow << "\nSelection Sort" << white << endl;
	Reverse(animals, size);
	selectionSort(animals, size);
	tend = system_clock::now();
	cout << "Duration: " << static_cast<double>((tend - tbegin).count()) / 10000000.0 << endl;

	tbegin = system_clock::now();
	cout << yellow << "\nShell Sort" << white << endl;
	Reverse(animals, size);
	shellSort(animals, size);
	tend = system_clock::now();
	cout << "Duration: " << static_cast<double>((tend - tbegin).count()) / 10000000.0 << endl;

	tbegin = system_clock::now();
	cout << yellow << "\nQuick Sort" << white << endl;
	Reverse(animals, size);
	quickSort(animals, 0, size);
	tend = system_clock::now();
	cout << "Duration: " << static_cast<double>((tend - tbegin).count()) / 10000000.0 << endl;
}

