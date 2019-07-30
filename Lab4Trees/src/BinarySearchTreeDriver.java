/*
 * Name: Anik Gupta
 * Course: CIS 22C
 * Lab4 - Trees
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


class TreeNode<T extends Comparable<T>>{
	T data;
	TreeNode<T> left;
	TreeNode<T> right;
	public TreeNode(){
		data = null;
		left = null;
		right = null;
	}
	public TreeNode(T data){
		this.data = data;
		left = null;
		right = null;
	}
	public String toString(){
		return data.toString();
		
	}
}
class BinarySearchTree<T extends Comparable<T>>{

	
	TreeNode<T> root;
	int size;
	
	public BinarySearchTree()
	{
		size = 0;
		root = null;
	}
	public BinarySearchTree(T rootVal){
		size = 1;
		root = new TreeNode<T>(rootVal);
	}
	void insert(T x) 
	{
		size++;
		TreeNode<T> currentNode = root;
		System.out.println("\n-->insert: " + x);
		while (true) 
		{
			System.out.println(currentNode);
			if(root == null){
				root = new TreeNode<T>(x);
				return;
			}
			else if (x.compareTo(currentNode.data) < 0) 
			{
				System.out.println(" <<< Left ");
				if(currentNode.left == null){
					currentNode.left = new TreeNode<T>(x);
					return;
				}
				currentNode = currentNode.left;
			}
			else
			{
				System.out.println(" Right >>> ");
				if(currentNode.right == null){
					currentNode.right = new TreeNode<T>(x);
					return;
				}
				currentNode = currentNode.right;
			}
		}

	}
	//Should be able to remove the root as well
	boolean remove(T x){
		System.out.println("Remove: " + x);
		TreeNode<T> currentNode = root;
		boolean rightNode = false;
		if(size > 0){
			while (true) 
			{
				// Removes root
				if(root.data.equals(x)){
					TreeNode<T> largest = root;
					if(largest.left != null){
						if(largest.left.right != null){
							largest = largest.left;
							while(largest.right.right != null){
								largest = largest.right;
							}
							root.data = largest.right.data;
							largest.right = null;
						}
						else{
							largest.left.right = root.right;
							root = largest.left;
						}
					}
					else{
						root = root.right;
					}
					size--;
					return true;
				}
				else if(currentNode.left != null && currentNode.left.data.equals(x)){
					rightNode = false;
					//System.out.println("\t" + currentNode.data + "\n" + currentNode.left.data + "\t\t" + currentNode.right.data);
					break;
				}
				else if (currentNode.right != null && currentNode.right.data.equals(x)){
					rightNode = true;
					break;
				}
				else if(currentNode.left != null && x.compareTo(currentNode.data) < 0){
					currentNode = currentNode.left;
					//System.out.println("\t" + currentNode.data + "\n" + currentNode.left.data);
				}
				else if(currentNode.right != null && x.compareTo(currentNode.data) > 0){
					currentNode = currentNode.right;
					//System.out.println("\t" + currentNode.data + "\n" + "\t\t" + currentNode.right.data);
				}
				else{
					return false;
				}
			}
			if(rightNode){
				if(currentNode.right.data.equals(x) && currentNode.right.left == null && currentNode.right.right == null){
					// Node to be removed is a right child and has no children of its own
					currentNode.right = null;
				}
				else if(currentNode.right.data.equals(x) && currentNode.right.left == null && currentNode.right.right != null){
					// Node to be removed is a right child and has a right child of its own
					currentNode.right = currentNode.right.right;
				}
				else if(currentNode.right.data.equals(x) && currentNode.right.right == null && currentNode.right.left != null){
					// Node to be removed is a right child and has a left child of its own
					currentNode.right = currentNode.right.left;
				}
				//Node to be removed has both children
				else if(currentNode.right.data.equals(x)){ 
					// Node to be removed is a right child and has 2 children
					TreeNode<T> largest = currentNode.right;
					if(largest.left.right != null){
						largest = largest.left;
						while(largest.right.right != null){
							largest = largest.right;
						}
						// Largest is now 1 level above the element with the largest data
						currentNode.right.data = largest.right.data;//(largest value of a node on currentNode.right.left);
						largest.right = null;
					}
					else{
						largest.left.right = currentNode.right.right;
						currentNode.right = largest.left;
					}
				}
			}
			else{ // Left Child
				// Node to be removed has no child
				if(currentNode.left.data.equals(x) && currentNode.left.left == null && currentNode.left.right == null){
					// Node to be removed is a left child and has no children of its own
					currentNode.left = null;
				}
				
				//Node to be removed has 1 child
				else if(currentNode.left.data.equals(x) && currentNode.left.left == null && currentNode.left.right != null){
					// Node to be removed is a left child and has a right child of its own
					currentNode.left = currentNode.left.right;
				}
				else if(currentNode.left.data.equals(x) && currentNode.left.right == null && currentNode.left.left != null){
					// Node to be removed is a left child and has a left child of its own
					currentNode.left = currentNode.left.left;
				}
				else{
					// Node to be removed is a left child and has 2 children
					TreeNode<T> largest = currentNode.left;
					if(largest.left.right != null){
						largest = largest.left;
						while(largest.right.right != null){
							largest = largest.right;
						}
						// Largest is now 1 level above the element with the largest data
						currentNode.left.data = largest.right.data;//(largest value of a node on currentNode.right.left);
						largest.right = null;
					}
					else{
						largest.left.right = currentNode.left.right;
						currentNode.left = largest.left;
					}
				}
			}
			return true;
		}
		else{
			return false;
		}
	}
	void search(T x) 
	{
		System.out.println("Search: " + x);
		TreeNode<T> currentNode = root;
		while (true) 
		{
			if (currentNode == null) 
			{
				System.out.println("Not found");
				break;
			}
			if (currentNode.data.equals(x))
			{
				System.out.println("Found");
				break;
			}
			else if (x.compareTo(currentNode.data) < 0) 
			{
				currentNode = currentNode.left;
				System.out.println(" <<< Left ");
			}
			else  
			{
				currentNode = currentNode.right;
				System.out.println(" Right >>> ");
			}
		}
	}
	// Small to large
	// Will be on the final - write this function iteratively
	void inOrder(TreeNode<T> r) 
	{
		if(r != null){
			inOrder(r.left);
			System.out.print(r.data + " ");
			inOrder(r.right);
		}
	}
	void inOrderIterative(TreeNode<T> r){
		TreeNode<T> parent = r;
		Stack<TreeNode<T>> stack = new Stack<TreeNode<T>>();
		while(parent != null || stack.size() != 0){
			if(parent != null){
				stack.add(parent);
				parent = parent.left;
			}
			else{
				parent = stack.pop();
				System.out.print(parent + " ");
				parent = parent.right;
			}
		}
	}
	// Print branches  - Depth-First Search - DFS
	void preOrder(TreeNode<T> r)
	{
		if (r != null)
		{
			System.out.print(r.data + " " );
			preOrder(r.left);
			preOrder(r.right);
		}
	}
	// Backwards DFS - from bottom of each branch
	void postOrder(TreeNode<T> r) 
	{
		if (r != null) 
		{
			postOrder(r.left);
			postOrder(r.right);
			System.out.print(r.data + " " );
		}
	}
	// Written using queue
	void printArray()
	{
		Queue<TreeNode<T>> queue = new Queue<TreeNode<T>>();
		TreeNode<T> currentNode = root;
		queue.add(currentNode);
		boolean done = false;
		while(!done){
			int length = queue.size();
			for(int i = 0; i < length; i++){
				if(queue.first().left != null){
					queue.add(queue.first().left);
				}
				if(queue.first().right != null){
					queue.add(queue.first().right);
				}
				System.out.print(queue.dequeue() + " ");
				
			}
			System.out.println();

			done = queue.size() == 0;
		}
	}
	boolean isBinarySearchTree(TreeNode<T> r){
		boolean hasLeft = false;
		boolean hasRight = false;
		if(r == null){
			return true;
		}
		if(r.left != null){
			hasLeft = true;
		}
		if(r.right != null){
			hasRight = true;
		}
		boolean output = true;
		if(hasRight && r.right.data.compareTo(r.data) < 0){
			output = false;
		}
		if(hasLeft && r.left.data.compareTo(r.data) > 0){
			output = false;
		}
		if(!output) return false;
		return isBinarySearchTree(r.left) && isBinarySearchTree(r.right);
	}
}
public class BinarySearchTreeDriver {
	private static final String FILE_NAME_READ = "Numbers.csv";
	private static final String FILE_NAME_ANSWER = "Numbers_Sorted.csv";
	public static void main(String[] args){
		//int[] array = { 42, 68, 35, 1, 70, 25, 79, 59, 63, 65};
		BinarySearchTree<Integer> bst = new BinarySearchTree<Integer>();
		try {
			Scanner sc = new Scanner(new File(FILE_NAME_READ));
			while(sc.hasNextInt()){
				bst.insert(sc.nextInt());
			}
			sc.close();
		}catch(FileNotFoundException e) {
			e.printStackTrace();
		}
		/*for (int i = 0; i < array.length; i++){
			bst.insert(array[i]);
		}*/
		/*bst.printArray();
		System.out.println();
		bst.inOrder(bst.root);
		
		System.out.println();
		bst.preOrder(bst.root);
		System.out.println();
		bst.postOrder(bst.root);
		System.out.println("\nSearch");
		bst.search(65);
		System.out.println(bst.remove(70));
		bst.printArray();
		bst.inOrder(bst.root);*/
		System.out.println("\nIterative");
		bst.inOrderIterative(bst.root);
		try {
			
			Scanner sc1 = new Scanner(new File(FILE_NAME_ANSWER));
			System.out.println("\nSorted");
			while(sc1.hasNextLine()){
				System.out.print(sc1.nextLine() + " ");
			}
			System.out.println();
			sc1.close();
		}catch(FileNotFoundException e) {
			e.printStackTrace();
		}
		//System.out.println(bst.isBinarySearchTree(bst.root));
	}
}
