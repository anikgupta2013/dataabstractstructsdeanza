/*
 * Name: Anik Gupta
 * Course: CIS 22C
 * Lab1 - Linked Lists
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

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
	
	private final boolean ADD_AT_HEAD = false;
	
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


public class LinkedListsDriver {

public static String FILE_NAME = "Words.txt";
	
	public static void ReadFile(List<String> linkedList){
		try {
			Scanner sc = new Scanner(new File(FILE_NAME));
			while(sc.hasNextLine()){
				linkedList.add(sc.nextLine());
			}
			sc.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}  
	
	public static void main(String[] args){
		List<String> linkedList = new List<String>();
		
		System.out.println("Reading Words from File:");
		ReadFile(linkedList);
		System.out.println(linkedList + "\n");
		
		//Test Code 
		
		
		System.out.println("Get frequency of the: " + linkedList.getFrequencyOf("the"));
		System.out.println("Contains box: " + linkedList.contains("box"));
		System.out.println("Remove box: " + linkedList.remove("box"));
		System.out.println(linkedList + "\n");
		System.out.println("Remove dfadfsf: " + linkedList.remove("dfadfsf"));
		System.out.println(linkedList + "\n");
		System.out.println("Contains dfadfsf: " + linkedList.contains("dfadfsf"));
		System.out.println("Get frequency of box: " + linkedList.getFrequencyOf("box"));
		System.out.println("Contains box: " + linkedList.contains("box"));
		System.out.println("Remove supper: " + linkedList.remove("supper"));
		System.out.println(linkedList + "\n");
		System.out.println("Remove the: " + linkedList.remove("the"));
		System.out.println(linkedList + "\n");
		
		
		
		System.out.println("All done!");
	}

}
