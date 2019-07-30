/*
 * Name: Anik Gupta
 * Course: CIS 22C
 * Lab3 - Double Linked Lists, Stacks and Queues
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.sql.Timestamp;
import java.util.Arrays;
import java.util.Date;
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


interface ListInterface <T>{  
	// Sees whether this list is empty.  
	// return True if the list is empty, or false if not.  
	boolean isEmpty();    
	//  Adds a new entry to the list.  
	// post  If successful, newEntry is stored in the list and  
	// the count of items in the list has increased by 1.  
	// param newEntry  The object to be added as a new entry.  
	// return  True if addition was successful, or false if not.  
	boolean add(T newEntry);
	// Removes one occurrence of a given entry from this list, if possible.  
	// post  If successful, anEntry has been removed from the list and the count of  
	// items in the list has decreased by 1.  
	// param anEntry  The entry to be removed.  
	// return  True if removal was successful, or false if not.  
	boolean remove(T anEntry);
	// Removes all entries from this list.  
	// post  List contains no items, and the count of items is 0.  
	void clear();
	// Counts the number of times a given entry appears in list.  
	// param anEntry  The entry to be counted.  
	// return  The number of times anEntry appears in the list.  
	int getFrequencyOf(T anEntry);
	// Tests whether this list contains a given entry.  
	// param anEntry  The entry to locate.  
	// return  True if list contains anEntry, or false otherwise.  
	boolean contains(T anEntry);
}
class Node<T>{  
	T item; // A data item  
	Node<T> prev; // previous node  
	public Node() {
		item = null;
		prev = null; 
	}
	public Node(T t) { 
		item = t;
		prev = null;
	};

}

class List<T> implements ListInterface<T> {

	public static final boolean ADD_AT_HEAD = true;

	Node<T> head;  
	int itemCount;           

	public List(){
		head = null;
		itemCount = 0;
	}
	public List(T node){
		head = new Node<T>(node);
		itemCount = 1;
	}

	@Override
	public boolean isEmpty() {
		return itemCount == 0;
	}

	@Override
	public boolean add(T newEntry) {

		// Add at head
		if(ADD_AT_HEAD){
			if(newEntry != null){
				if(head != null){
					// Not the first item
					Node<T> node = new Node<T>(newEntry);
					node.prev = head;
					head = node;
				}
				else{
					// First item
					head = new Node<T>(newEntry);
				}
				itemCount++;
				return true;
			}
			return false;
		}
		else{

			/// Add at tail (inefficient - requires linked list traversal every time)
			if(newEntry != null){
				if(head != null){
					// Not first item
					Node<T> node = new Node<T>(newEntry);
					Node<T> curr = head;
					while(curr.prev != null){
						curr = curr.prev;
					}
					curr.prev = node;
				}
				else{
					//First item
					head = new Node<T>(newEntry);
				}
				itemCount++;
				return true;
			}
			return false;
		}
	}

	@Override
	public boolean remove(T anEntry) {
		//if(contains(anEntry)){
		Node<T> curr = head;
		if(curr.item.equals(anEntry)){
			//element found at head
			if(itemCount == 1) clear(); // the only item has to be removed
			else{
				Node<T> found = curr;
				head = found.prev;
				found.prev = null;
			}
		}
		else{
			//element not at head
			while(curr.prev != null){
				if(curr.prev.item.equals(anEntry)){
					break;
				}
				curr = curr.prev;
			}
			if(curr.prev == null) return false; // case where anEntry is not in List
			Node<T> found = curr.prev;
			curr.prev = found.prev;
			found.prev = null;
		}

		itemCount--;
		return true;
		//}
		//return false;
	}

	@Override
	public void clear() {
		head = null;
		itemCount = 0;
	}

	@Override
	public int getFrequencyOf(T anEntry) {
		Node<T> curr = head;
		int count = 0;
		while(curr != null){
			if(curr.item.equals(anEntry)){
				count++;
			}
			curr = curr.prev;
		}
		return count;
	}

	@Override
	public boolean contains(T anEntry) {
		return getFrequencyOf(anEntry) > 0;
	}

	@Override
	public String toString(){
		String s = "The list contains " + this.itemCount + " items:\n";
		Node<T> curr = head;


		//Print when using head addition
		if(ADD_AT_HEAD){
			return s+giveString(head);
		}
		else{
			// Print when using tail addition

			while(curr != null){
				s+= curr.item + " ";
				curr = curr.prev;
			}
			return s;
		}


	}
	private String giveString(Node<T> start){
		// Recursive string building
		if(start != null){
			return giveString(start.prev) + start.item + " " ;
		}
		return "";
	}
}


class Sort{
	/**
	 * 
	 * @param arr - The DynamicArray to be sorted
	 * @param nthRadix - The radix the array is being sorted by
	 */
	private static void radixSort(DynamicArray<Integer> arr, int nthRadix){
		//Stores the numbers for the values of each radix
		DynamicArray<List<Integer>> radix = new DynamicArray<List<Integer>>();
		for(int i = 0; i < 10; i++){
			// Initialize Lists
			radix.add(new List<Integer>());
		}
		if(List.ADD_AT_HEAD){
			for(int i = arr.getCurrentSize()-1; i >= 0; i--){
				// Insert at head from last to first 
				// so that when head will be closer to the first element in arr
				// Gets the value of the digit at radix and adds the number to the list at that index
				radix.get(getNthRadix(arr.get(i), nthRadix)).add(arr.get(i));
			}
		}else{
			for(int i = 0; i < arr.getCurrentSize(); i++){
				// Insert at tail from first to last
				// so that when head will be closer to the first element in arr
				// Gets the value of the digit at radix and adds the number to the list at that index
				radix.get(getNthRadix(arr.get(i), nthRadix)).add(arr.get(i));
			}
		}
		// Clears given array - make space for numbers sorted by radix
		arr.clear();
		// Iterate through each radix (0-9) and each element in their lists (starting at head)
		// Add them back to the array
		for(int i = 0; i < 10; i++){
			Node<Integer> curr = radix.get(i).head;
			while(curr != null){
				arr.add(curr.item);
				curr = curr.prev;
			}
		}
	}
	/**
	 * 
	 * @param arr - DynamicArray to be sorted
	 */
	public static void radixSort(DynamicArray<Integer> arr){
		for(int i = 1; !isInOrder(arr); i++){
			// Increases radix value until arr is sorted
			radixSort(arr, i);
		}
	}
	/**
	 * 
	 * @param num - the number whose radix we are finding
	 * @param nthRadix - the radix we are looking for
	 * @return - the nthRadix digit from the right of num
	 */
	private static int getNthRadix(int num, int nthRadix){
		for(int i = 1; i < nthRadix; i++){
			num /= 10;
		}
		return num%10;
	}
	/**
	 * 
	 * @param arr - Array to be checked
	 * @return - if arr is sorted in increasing order
	 */
	private static boolean isInOrder(DynamicArray<Integer> arr){
		for(int i = 1; i < arr.getCurrentSize(); i++){
			if(arr.get(i) < arr.get(i-1)) return false;
		}
		return true;
	}
}
public class SortDriver {

	private static final String FILE_NAME_READ = "Numbers.csv";
	private static final String FILE_NAME_ANSWER = "Numbers_Sorted.csv";
	public static void main(String[] args) {
		DynamicArray<Integer> nums = new DynamicArray<Integer>();
		DynamicArray<Integer> answer = new DynamicArray<Integer>();
		try {
			Scanner sc = new Scanner(new File(FILE_NAME_READ));
			while(sc.hasNextInt()){
				nums.add(sc.nextInt());
			}
			
			System.out.println("Before: " + nums+ "\n");
			//Start Time
			Date date= new Date();
			long start = date.getTime(); 
			Sort.radixSort(nums);	// Sort
			System.out.println("After: " + nums);
			//End Time
			date= new Date();
			long end = date.getTime();
			
			// File containing numbers sorted by excel
			sc = new Scanner(new File(FILE_NAME_ANSWER));
			while(sc.hasNextInt()){
				answer.add(sc.nextInt());
			}
			boolean sorted = true;
			// Check if file numbers are in same order as the numbers in nums
			for(int i = 0; i < answer.getCurrentSize(); i++){
				if(answer.get(i) != nums.get(i)){
					sorted = false;
					break;
				}
			}
			sc.close();
			System.out.println("\nIs sorted check: " + sorted);
			// Print Time
			System.out.println("\nTime ellapsed: "+(end-start)/1000.0 + " seconds");
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}


	}

}
