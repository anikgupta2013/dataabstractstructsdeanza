#include <iostream>
#include <vector>
#include <iterator>
#include <array>
#include "ConsoleColor.h"

using namespace std;

template <typename T>
class DynamicArray : public vector<T> { };

template <typename T>
class Heap
{
	DynamicArray<T> heap;
public:
	Heap() { }
	~Heap(){ }
	int size() { return heap.size(); }
	void insert(T element)
	{
		cout << blue << ">>> Inserting " << element << white << endl;
		heap.push_back(element);
		heapifyup(heap.size() - 1);
	}
	T deletemin()
	{
		T min = heap.front();
		heap[0] = heap.at(heap.size() - 1);
		heap.pop_back();
		heapifydown(0);
		return min;
	}
	void print()
	{
		cout << green;
		auto pos = heap.begin();
		cout << "Heap = ";
		while (pos != heap.end()) 
		{
			cout << *pos << " ";
			++pos;
		}
		cout << endl;
	}
	void heapifyup(int index)
	{
		cout << yellow << "Heapup index=" << index << endl;
		if (index > -1)
		{
			cout << "parent(index)=" << parent(index) << endl;
			if (parent(index) > -1)
				cout << "heap[parent(index)]=" << heap[parent(index)] << endl;
			cout << "heap[index]=" << heap[index] << endl;
		}
		while ((index > 0) && (parent(index) >= 0) && (heap[parent(index)] > heap[index]))
		{
			T tmp = heap[parent(index)];
			heap[parent(index)] = heap[index];
			heap[index] = tmp;
			index = parent(index);
		}
		cout << white;
	}
	void heapifydown(int index)
	{
		cout << red << "Heapdown index=" << index << endl;
		cout << "left(index)=" << left(index) << endl;
		cout << "right(index)=" << right(index) << endl;
		int child = left(index);
		if ((child > 0) && (right(index) > 0) && (heap[child] > heap[right(index)]))
		{
			child = right(index);
		}
		if (child > 0)
		{
			T tmp = heap[index];
			heap[index] = heap[child];
			heap[child] = tmp;
			heapifydown(child);
		}
		cout << white;
	}
	int left(int parent)
	{
		int i = (parent << 1) + 1; // 2 * parent + 1
		return (i < heap.size()) ? i : -1;
	}
	int right(int parent)
	{
		int i = (parent << 1) + 2; // 2 * parent + 2
		return (i < heap.size()) ? i : -1;
	}
	int parent(int child)
	{
		if (child != 0)
		{
			int i = (child - 1) >> 1;
			return i;
		}
		return -1;
	}
};

int main()
{
	// Create the heap
	array<int, 10> numbers =
	{
		100,200,300,400,500,600,700,800,900,1000
	};
	random_shuffle(numbers.begin(), numbers.end());
	Heap<int> heap;
	for (auto i : numbers)
	{
		heap.insert(i);
		heap.print();
	}

	int heapSize = heap.size();
	for (int i = 0; i < heapSize; i++)
		cout << "Get min element = " << heap.deletemin() << endl;
}



