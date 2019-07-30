
#include <array>
#include <iostream>
#include <string>
#include <memory>

using namespace std;

enum { INVALID=-1,DEFAULT_CAPACITY = 10 };	// Small size to test

class ArrayInterface
{
public:
	/** Gets the current number of entries in this array.
	@return The integer number of entries currently in the bag. */
	virtual int getCurrentSize() = 0;

	/** Sees whether this array is empty.
	@return True if the bag is empty, or false if not. */
	virtual bool isEmpty() = 0;

	/** Adds a new entry to this array.
	@post  If successful, newEntry is stored in the array and
	the count of items in the bag has increased by 1.
	@param newEntry  The object to be added as a new entry.
	@return  True if addition was successful, or false if not. */
	virtual bool add(int newEntry) = 0;

	/** Removes one occurrence of a given entry from this array,
	if possible.
	@post  If successful, anEntry has been removed from the array
	and the count of items in the array has decreased by 1.
	@param anEntry  The entry to be removed.
	@return  True if removal was successful, or false if not. */
	virtual bool remove(int anEntry) = 0;

	/** Removes all entries from this array.
	@post  Array contains no items, and the count of items is 0. */
	virtual void clear() = 0;

	/** Counts the number of times a given entry appears in array.
	@param anEntry  The entry to be counted.
	@return  The number of times anEntry appears in the array. */
	virtual int getFrequencyOf(int anEntry) = 0;

	/** Tests whether this array contains a given entry.
	@param anEntry  The entry to locate.
	@return  True if array contains anEntry, or false otherwise. */
	virtual bool contains(int anEntry) = 0;

};

class DynamicArray : public ArrayInterface
{
private:
	int* items;							// Array of items
	// T[] items;						// Java  
	int itemCount;                      // Current count of array items 
	int maxItems;                       // Max capacity of the array
public:
	DynamicArray(int capacity = DEFAULT_CAPACITY) : itemCount(0), maxItems(capacity)
	{
		items = new int[capacity];
		// adapt for Java
	}  
	~DynamicArray()
	{
		// not necessary in Java
		if (items)
			delete[] items;
	}
	int getCurrentSize()
	{
		return itemCount;
	}  
	bool isEmpty() 
	{
		return itemCount == 0;
	}  
	int& get(int index)
	{
		return items[index];
	}
	// not available in Java
	int& operator [](int index)
	{
		return get(index);
	}
	bool add(int newEntry)
	{
		bool hasRoomToAdd = (itemCount < maxItems);
		if (hasRoomToAdd)
		{
			items[itemCount] = newEntry;
			itemCount++;
		}  
		return hasRoomToAdd;
	}  
	bool remove(int anEntry)
	{
		int locatedIndex = getIndexOf(anEntry, 0);
		bool canRemoveItem = !isEmpty() && (locatedIndex > INVALID);
		if (canRemoveItem)
		{
			itemCount--;
			items[locatedIndex] = items[itemCount];
		} 

		return canRemoveItem;
	}  

	void clear()
	{
		itemCount = 0;
	}  
	bool contains(int anEntry)
	{
		return getIndexOf(anEntry, 0) > INVALID;
	}  
	int getFrequencyOf(int anEntry) 
	{
		return countFrequency(anEntry, 0);
	}  
	int countFrequency(int anEntry, int searchIndex) 
	{
		int frequency = 0;
		if (searchIndex < itemCount)
		{
			if (items[searchIndex] == anEntry)
			{
				frequency = 1 + countFrequency(anEntry, searchIndex + 1);
			}
			else
			{
				frequency = countFrequency(anEntry, searchIndex + 1);
			}  
		}  

		return frequency;
	}  
	int getIndexOf(int target, int searchIndex)
	{
		int result = -1;
		if (searchIndex < itemCount)
		{
			if (items[searchIndex] == target)
			{
				result = searchIndex;
			}
			else
			{
				result = getIndexOf(target, searchIndex + 1);
			}  
		}  
		return result;
	}  
	int& getIndexValue(int index)
	{
		return items[index];
	}
	// not available in Java
	friend ostream& operator << (ostream& stream, DynamicArray& darray)
	{
		stream << "The array contains " << static_cast<int>(darray.getCurrentSize()) << " items:" << endl;
		for (int i = 0; i < darray.getCurrentSize(); i++)
		{
			stream << darray[i] << " ";
		}  
		stream << endl << endl;
		return stream;
	} 
};

void TestBench(DynamicArray darray)
{
	cout << "Add items to the bag container: " << endl;
	for (int i = 0; i < DEFAULT_CAPACITY; i++)
		darray.add(int(rand()));
	cout << darray;
}  

void main()
{
	DynamicArray darray;
	cout << "Testing the Dynamic Array:" << endl;
	TestBench(darray);
	cout << "All done!" << endl;
}  

