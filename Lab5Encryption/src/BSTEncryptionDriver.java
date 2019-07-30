/*
 * Name: Anik Gupta
 * Course: CIS 22C
 * Lab5 - Encryption (Huffman Encoding Algorithm)
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Scanner;

class Node implements Comparable<Node>{
	private char key;   // 'A'
    private int frequency;  // 2134
    private String encrypt; // "1101011"
    
    public Node(char key, int frequency, String encrypt){
    	this.setKey(key);
    	this.setFrequency(frequency);
    	this.setEncrypt(encrypt);
    }
    
	@Override
	public int compareTo(Node o) {
		return this.frequency-o.frequency;
	}

	@Override
	public String toString(){
		return key + " (" + frequency + "): " + encrypt;
	}
	public int getFrequency() {
		return frequency;
	}

	public void setFrequency(int frequency) {
		this.frequency = frequency;
	}
	
	public char getKey() {
		return key;
	}

	public void setKey(char key) {
		this.key = key;
	}

	public String getEncrypt() {
		return encrypt;
	}

	public void setEncrypt(String encrypt) {
		this.encrypt = encrypt;
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
		//System.out.println("\n-->insert: " + x);
		while (true) 
		{
			//System.out.println(currentNode);
			if(root == null){
				root = new TreeNode<T>(x);
				return;
			}
			else if (x.compareTo(currentNode.data) < 0) 
			{
				//System.out.println(" <<< Left ");
				if(currentNode.left == null){
					currentNode.left = new TreeNode<T>(x);
					return;
				}
				currentNode = currentNode.left;
			}
			else
			{
				//System.out.println(" Right >>> ");
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
		//System.out.println("Remove: " + x);
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
		//System.out.println("Search: " + x);
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
	/*void printArray()
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
	}*/
}
class Encryption{
	static String BSTEncrypt(String input, BinarySearchTree<Node> bst){
		// ArrayList to store frequency of characters.
		ArrayList<Node> pairs = new ArrayList<Node>();
		for(int i = 0; i < input.length(); i++){
			boolean contains = false;
			int j = 0;
			for(; j < pairs.size(); j++){
				if(pairs.get(j).getKey() == input.charAt(i)){
					contains = true;
					break;
				}

			}
			if(contains){
				pairs.get(j).setFrequency(pairs.get(j).getFrequency()+1); // increase frequency if arraylist contains key
			}
			else{
				pairs.add(new Node(input.charAt(i), 1, "")); // otherwise make a new element
			}
		}
		// Insert elements into BST by frequency	
		for(int i = 0; i < pairs.size(); i++){
			bst.insert(pairs.get(i));
		}
		//Assign encrypt values
		assignEncrypt(bst.root, "");
		
		//Create encrypted message - can be made faster if using a hashtable with key = character and value = encryption
		String output = "";
		//Start Time
		Date date= new Date();
		long start = date.getTime(); 
		for(int i = 0; i < input.length(); i++){
			output += getEncrypt(bst.root, input.charAt(i));
		}
		//End Time
		date= new Date();
		long end = date.getTime();
		// Print Time
		System.out.println("\nTime ellapsed: "+(end-start)/1000.00 + " seconds");
		return output;
	}
	
	static String BSTDecrypt(String input, BinarySearchTree<Node> bst){
		TreeNode<Node> root = bst.root;
		String output = "";
		for(int i = 0; i < input.length(); i++){
			switch(input.charAt(i)){
				case '0' : 	root = root.left;
						   	break;
				case '1' : 	root = root.right;
							break;
				case '~' : 	output += root.data.getKey();
							root = bst.root;
							break;
				default  :	System.out.println("Invalid encrypted key");
							root = bst.root;
							break;
			}
		}
		return output;
	}
	
	// Assigns the encrypt variable for each Node in the BST
	private static void assignEncrypt(TreeNode<Node> root, String enc){
		if(root.left != null){
			assignEncrypt(root.left, enc+"0"); // if left node exists - recurse and and a 0 to signify left
		}
		root.data.setEncrypt(enc + "~"); // set the encrypt with the end token ~
	
		if(root.right != null){
			assignEncrypt(root.right, enc+"1"); // if right node exists - recurse and and a 1 to signify right
		}
	}
	
	private static String getEncrypt(TreeNode<Node> root, char c){
		if(root != null){
			if(root.data.getKey() != c){
				return getEncrypt(root.left, c) + getEncrypt(root.right, c); // Look in the left and right sub trees
			}
			else{
				return root.data.getEncrypt(); // Node with key c is the root
			}
		}
		return ""; // Node with key c not found
	}
}
public class BSTEncryptionDriver {
	public static File fileIn = new File("Speech.txt");
	public static File fileEncrypt = new File("Speech_encrypt.txt");
	public static File fileDecrypt = new File("Speech_decrypt.txt");
	
	public static void main(String[] args) {
		BinarySearchTree<Node> bst = new BinarySearchTree<Node>();
		
		try {
			Scanner in = new Scanner(fileIn);
			String input = "";
			while(in.hasNextLine()){
				input += in.nextLine() + '\n';
	
			}
			in.close();
			//Start Time
			Date date= new Date();
			long start = date.getTime(); 
			
			String encrypted = Encryption.BSTEncrypt(input, bst);
			String decrypted = Encryption.BSTDecrypt(encrypted, bst);
			//End Time
			date= new Date();
			long end = date.getTime();
			// Print Time
			System.out.println("\nTime ellapsed: "+(end-start)/1000.0 + " seconds");
			
			FileWriter enc = new FileWriter(fileEncrypt);
			enc.write(encrypted);
			enc.close();
			
			FileWriter dec = new FileWriter(fileDecrypt);
			dec.write(decrypted);
			dec.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
