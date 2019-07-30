/*
 * Name: Anik Gupta
 * Course: CIS 22C
 * Lab0 - Extending Arrays
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

interface ArrayInterface<T>{

	/** Gets the current number of entries in this array.
	@return The integer number of entries currently in the bag. */
	public int getCurrentSize();

	/** Sees whether this array is empty.
	@return True if the bag is empty, or false if not. */
	public boolean isEmpty();

	/** Adds a new entry to this array.
	@post  If successful, newEntry is stored in the array and
	the count of items in the bag has increased by 1.
	@param newEntry  The object to be added as a new entry.
	@return  True if addition was successful, or false if not. */
	public boolean add(T newEntry);

	/** Removes one occurrence of a given entry from this array,
	if possible.
	@post  If successful, anEntry has been removed from the array
	and the count of items in the array has decreased by 1.
	@param anEntry  The entry to be removed.
	@return  True if removal was successful, or false if not. */
	public boolean remove(T anEntry);

	/** Removes all entries from this array.
	@post  Array contains no items, and the count of items is 0. */
	public void clear();

	/** Counts the number of times a given entry appears in array.
	@param anEntry  The entry to be counted.
	@return  The number of times anEntry appears in the array. */
	public int getFrequencyOf(T anEntry);

	/** Tests whether this array contains a given entry.
	@param anEntry  The entry to locate.
	@return  True if array contains anEntry, or false otherwise. */
	public boolean contains(T anEntry);

}

class DynamicArray<T> implements ArrayInterface<T>{
	public static int INVALID=-1;
	public static int DEFAULT_CAPACITY = 10;	// Small size to test
	
	private T[] items;							// Java  
	private int itemCount;                      // Current count of array items 
	private int maxItems;                       // Max capacity of the array

	@SuppressWarnings("unchecked")
	public DynamicArray(){
		maxItems = DEFAULT_CAPACITY;
		itemCount = 0;
		items = (T[]) new Object[maxItems];
	} 
	
	@Override
	public int getCurrentSize()
	{
		return itemCount;
	}  
	
	@Override
	public boolean isEmpty() 
	{
		return itemCount == 0;
	}  
	
	T get(int index)
	{
		return items[index];
	}
	
	@Override
	public boolean add(T newEntry)
	{
		boolean hasRoomToAdd = (itemCount < maxItems);
		if (!hasRoomToAdd)
		{
			items = Arrays.copyOf(items, maxItems*2);            
			maxItems = maxItems * 2;
			
		}  
		items[itemCount] = newEntry;
		itemCount++;
		
		return hasRoomToAdd;
	}  
	
	@Override
	public boolean remove(T anEntry)
	{
		int locatedIndex = getIndexOf(anEntry, 0);
		boolean canRemoveItem = !isEmpty() && (locatedIndex > INVALID);
		if (canRemoveItem)
		{
			itemCount--;
			items[locatedIndex] = items[itemCount];
		} 

		return canRemoveItem;
	}  
	
	@Override
	public void clear()
	{
		itemCount = 0;
	}
	
	@Override
	public boolean contains(T anEntry)
	{
		return getIndexOf(anEntry, 0) > INVALID;
	}  
	
	@Override
	public int getFrequencyOf(T anEntry) 
	{
		return countFrequency(anEntry, 0);
	}  
	
	int countFrequency(T anEntry, int searchIndex) 
	{
		int frequency = 0;
		if (searchIndex < itemCount)
		{
			if (items[searchIndex].equals(anEntry))
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
	
	int getIndexOf(T target, int searchIndex)
	{
		int result = -1;
		if (searchIndex < itemCount)
		{
			if (items[searchIndex].equals(target))
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
	
	T getIndexValue(int index)
	{
		return items[index];
	}
	
	@Override
	public String toString(){
		String s = "The array contains " + this.getCurrentSize() + " items:\n";
		for (int i = 0; i < this.getCurrentSize(); i++)
		{
			s+= items[i] + " ";
		}  
		return s;
	}
}

public class DynamicArrayDriver{
	
	public static String FILE_NAME = "Words.txt";
	
	public static void TestBench(DynamicArray<String> darray){
		try {
			Scanner sc = new Scanner(new File(FILE_NAME));
			while(sc.hasNextLine()){
				darray.add(sc.nextLine());
			}
			sc.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}  
	
	public static void main(String[] args){
		DynamicArray<String> darray = new DynamicArray<String>();
		System.out.println("Reading Words from File:");
		TestBench(darray);
		System.out.println(darray);
//		System.out.println(darray.remove("box"));
//		System.out.println(darray);
		System.out.println("All done!");
	}
}




