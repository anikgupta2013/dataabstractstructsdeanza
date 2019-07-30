/*
 * Name: Anik Gupta
 * Course: CIS 22C
 * Lab2 - Double Linked Lists, Stacks and Queues
 */
//Done
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
//Done
class Node<T>{  
	T item; 	  // A data item  
	Node<T> prev; // previous node  
	Node<T> next; // next node
	public Node() {
		item = null;
		prev = null; 
		next = null;
	}
	public Node(T t) { 
		item = t;
		prev = null;
		next = null;
	}
	
}

class DoublyLinkedList<T> implements ListInterface<T> {
	
	Node<T> head;  
	Node<T> tail;
	int itemCount;           
	
	public DoublyLinkedList(){
		head = null;
		tail = null;
		itemCount = 0;
	}
	
	public DoublyLinkedList(T node){
		head = new Node<T>(node);
		tail = head;
		itemCount = 1;
	}
	
	@Override
	public boolean isEmpty() {
		return itemCount == 0;
	}
	
	public int size(){
		return itemCount;
	}
	
	@Override
	public boolean add(T newEntry) {
		if(newEntry != null){
			// Make sure user is entering proper entry
			if(isEmpty()){
				// First element added to list - head and tail are same value
				head = new Node<T>(newEntry);
				tail = head;
			}
			else{
				// Other entries added at the tail
				Node<T> entry = new Node<T>(newEntry);
				entry.next = tail;
				tail.prev = entry;
				tail = entry;
			}
			itemCount++;
			return true;
		}
		return false;
	}
	
	@Override
	public boolean remove(T anEntry) {
		Node<T> curr = tail;
		while(curr != null && !curr.item.equals(anEntry)){
			curr = curr.next;
		}
		if(curr != null){
			if(itemCount == 1){
				//Curr has no prev and next (is the only value)
				clear();
			}
			else{
				if(curr.next == null){
					//Curr = head (has no next)
					head = curr.prev;
					head.next.prev = null;
					head.next = null;
				}
				else if(curr.prev == null){
					//Curr = tail (has no prev)
					tail = curr.next;
					tail.prev.next = null;
					tail.prev = null;
				}
				else{
					//Regular case (middle of list)
					curr.prev.next = curr.next;
					curr.next.prev = curr.prev;
					curr.next = null;
					curr.prev = null;
				}
				itemCount--;
			}
			return true;	
		}
		return false;
	}
	
	@Override
	public void clear() {
		head = null;
		tail = null;
		itemCount = 0;
	}
	
	@Override
	public int getFrequencyOf(T anEntry) {
		Node<T> curr = tail;
		int count = 0;
		while(curr != null){
			if(curr.item.equals(anEntry)){
				count++;
			}
			curr = curr.next;
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
		while(curr != null){
			s+= curr.item + " ";
			curr = curr.prev;
		}
		return s;
	}
}

class Queue<T> extends DoublyLinkedList<T>{
	public Queue(){
		super();
	}
	public Queue(T first){
		super(first);
	}
	public boolean enqueue(T newEntry){
		return add(newEntry);
	}
	public T dequeue(){
		T val = first();
		if(head != null && head.prev != null){ 
			// Head exists and there is at least one more Node before it
			head = head.prev;
			head.next.prev = null;
			head.next = null;
			itemCount--;
		}else{
			// Head does not exist or only 1 element in queue left
			// Empty queue
			clear();
		}
		
		return val;
		
	}
	public T first(){
		if(head != null)return head.item;
		return null;
	}
}
class Stack<T> extends DoublyLinkedList<T>{
	public Stack(){
		super();
	}
	public Stack(T first){
		super(first);
	}
	public boolean push(T newEntry){
		return add(newEntry);
	}
	public T pop(){
		T val = top();
		if(tail != null && tail.next != null){
			// If there is a tail and one more Node after it
			tail = tail.next;
			tail.prev.next = null;
			tail.prev = null;
			itemCount--;
		}else{
			// Either no items at start or 1 item left
			// Clear the stack
			clear();
		}
		return val;
		
	}
	public T top(){
		if(tail != null) return tail.item;
		return null;
	}
}


public class DoubleLLStacksQueuesDriver {

	public static void main(String[] args) {
		//Doubly Linked List Test
		DoublyLinkedList<String> linkedList = new DoublyLinkedList<String>();
		for(char a = 'a'; a <= 'c'; a++){
			linkedList.add(a+"");
		}
		System.out.println("List: " + linkedList);
		System.out.println("List (head, tail): " + linkedList.head.item +", "+ linkedList.tail.item);
		System.out.println("List.remove(b): " + linkedList.remove("b"));
		System.out.println("List: " + linkedList);
		System.out.println("List.remove(a): " + linkedList.remove("a"));
		System.out.println("List: " + linkedList);
		System.out.println("List (head, tail): " + linkedList.head.item +", "+ linkedList.tail.item);
		System.out.println("List.remove(c): " + linkedList.remove("c"));
		System.out.println("List: " + linkedList);	
		System.out.println("List.remove(e): " + linkedList.remove("e"));
		System.out.println("List: " + linkedList);
		linkedList.add("e");
		System.out.println("List: " + linkedList);
		System.out.println("List (head, tail): " + linkedList.head.item +", "+ linkedList.tail.item);
		System.out.println();
		
		
		
		// Queue Test
		Queue<String> queue = new Queue<String>();
		for(char a = 'a'; a <= 'c'; a++){
			queue.enqueue(a+"");
		}
		System.out.println("Queue: " + queue);
		System.out.println("Queue.first(): " + queue.first());
		System.out.println("Queue.dequeue(): " + queue.dequeue());
		System.out.println("Queue: " + queue);
		System.out.println("Queue.dequeue(): " + queue.dequeue());
		System.out.println("Queue: " + queue);
		System.out.println("Queue.dequeue(): " + queue.dequeue());
		System.out.println("Queue: " + queue);
		System.out.println("Queue.dequeue(): " + queue.dequeue());
		System.out.println("Queue: " + queue);
		queue.enqueue("e");
		System.out.println("Queue: " + queue);
		
		System.out.println();
		
		
		//Stack Test
		Stack<String> stack = new Stack<String>();
		for(char a = 'a'; a <= 'c'; a++){
			stack.push(a+"");
		}
		
		System.out.println("Stack: " + stack);
		System.out.println("Stack.top(): " + stack.top());
		System.out.println("Stack.pop(): " + stack.pop());
		System.out.println("Stack: " + stack);
		System.out.println("Stack.pop(): " + stack.pop());
		System.out.println("Stack: " + stack);
		System.out.println("Stack.pop(): " + stack.pop());
		System.out.println("Stack: " + stack);
		System.out.println("Stack.pop(): " + stack.pop());
		System.out.println("Stack: " + stack);
		stack.push("e");
		System.out.println("Stack: " + stack);

	}

}
