

class BinarySearchTreeArray
{
	
	Integer[] array;
	int size;
	
	public BinarySearchTreeArray(int s)
	{
		size = s;
		size = reSize(size);
		array = new Integer[size];
		for (int x = 0; x < size; x++) 
			array[x] = null;
	}
	int reSize(int x) 
	{
		int value = (int) Math.pow(2, x);
		return value;
	}
	void insert(int x) 
	{
		int currentIndex = 0;
		System.out.println("\n-->insert: " + x);
		while (true) 
		{
			if (array[currentIndex] == null) 
			{
				array[currentIndex] = x;
				System.out.println("Inserted @ index: " + currentIndex);
				break;
			}
			else if (x < array[currentIndex]) 
			{
				currentIndex = (2 * currentIndex + 1);
				System.out.println(" <<< Left " + currentIndex);
			}
			else  
			{
				currentIndex = (2 * currentIndex + 2);
				System.out.println(" Right >>> " + currentIndex);
			}
		}
	}
	void search(int x) 
	{
		System.out.println("Search: " + x);
		int currentIndex = 0;
		while (true) 
		{
			if (array[currentIndex] == null) 
			{
				System.out.println("Not found");
				break;
			}
			if (array[currentIndex] == x) 
			{
				System.out.println("Found at index: " + currentIndex);
				break;
			}
			else if (x < array[currentIndex]) 
			{
				System.out.println(" <<< Left ");
				currentIndex = (2 * currentIndex + 1);
			}
			else 
			{
				System.out.println(" >>> Right ");
				currentIndex = (2 * currentIndex + 2);
			}
		}
	}
	// Prints the levels
	void parent(int x) 
	{
		while (x != 0) 
		{
			x = (x - 1) / 2;
			System.out.print("---|");
		}
	}
	// Small to large
	// Will be on the final - write this function iteratively
	void inOrder(int currentIndex) 
	{
		if (array[currentIndex] != null) 
		{
			inOrder(2 * currentIndex + 1);
			parent(currentIndex);
			System.out.println(array[currentIndex]);
			inOrder(2 * currentIndex + 2);
		}
	}
	// Print branches  - Depth-First Search - DFS
	void preOrder(int currentIndex)
	{
		if (array[currentIndex] != null)
		{
			parent(currentIndex);
			System.out.println(array[currentIndex] + " " );
			preOrder(2 * currentIndex + 1);
			preOrder(2 * currentIndex + 2);
		}
	}
	// Backwards DFS - from bottom of each branch
	void postOrder(int currentIndex) 
	{
		if (array[currentIndex] != null) 
		{
			postOrder(2 * currentIndex + 1);
			postOrder(2 * currentIndex + 2);
			parent(currentIndex);
			System.out.println(array[currentIndex] + " " );
		}
	}
	void printArray()
	{
		int exp = 0;
		int sum = (int)(Math.pow(2, exp));
		int power = sum;
		for (int i = 0; i < size; i++)
		{
			if (i == sum)
			{
				System.out.println("| ");
				exp++;
				power = (int)(Math.pow(2, exp));
				sum += power;
			}
			if (array[i] != null)// if(array[i])
			{
				System.out.print(array[i] + " ");
			}
			else
			{
				System.out.print(". ");
			}
		}
		System.out.println();
	}
};

public class BinarySearchTreeArrayDriver {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] array = { 42, 68, 35, 1, 70, 25, 79, 59, 63, 65 };
		//int size = sizeof(array) / sizeof(array[0]);
		int size = array.length;
		int asize = (int) (Math.log(size*size) / Math.log(2));
		BinarySearchTreeArray bst = new BinarySearchTreeArray(asize);
		for (int i = 0; i < size; i++)
			bst.insert(array[i]);
		System.out.println();
		System.out.println("Inorder");
		bst.inOrder(0);
		System.out.println("Preorder");
		bst.preOrder(0);
		System.out.println("Postorder");
		bst.postOrder(0);
		System.out.println("\nSearch");
		bst.search(65);
		System.out.println("\nIn memory");
		bst.printArray();

	}

}
