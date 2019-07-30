#include <stdexcept>
#include <string>
#include <iostream>
#include <algorithm>
#include "ConsoleColor.h"
using namespace std;

template <typename T>
class Node
{
private:
	T        item;          
	Node<T>* left;  
	Node<T>* right;  
public:
	Node() : item(nullptr), left(nullptr), right(nullptr)
	{
	}  
	Node(T& anItem) : item(anItem), left(nullptr), right(nullptr)
	{
	}  
	Node(const T& data, Node<T>* l=nullptr, Node<T>* r=nullptr) : item(data), left(l), right(r)
	{
	} 
	void setItem(T& anItem)
	{
		item = anItem;
	}  
	T getItem() 
	{
		return item;
	}  
	bool isLeaf() 
	{
		return ((left == nullptr) && (right == nullptr));
	}
	void setleft(Node<T>* leftPtr)
	{
		left = leftPtr;
	}  
	void setright(Node<T>* rightPtr)
	{
		right = rightPtr;
	}  
	Node<T>* getleft() 
	{
		return left;
	}  		
	Node<T>* getright() 
	{
		return right;
	}  	
}; 

template <typename T>
class BinaryTree 
{
private:
	Node<T>* root;
public:
	BinaryTree() : root(nullptr) { }
	BinaryTree(T item)
	{
		root = new Node<T>(item);
	}
	BinaryTree(T item, const BinaryTree<T>* left, const BinaryTree<T>* right)
	{
		root = new Node<T>(item, copyTree(left->root), copyTree(right->root));
	}
	BinaryTree(BinaryTree<T>& treePtr)
	{
		root = copyTree(treePtr.root);
	}
	~BinaryTree()
	{
		destroyTree(root);
	}
	bool isEmpty()
	{
		return root == nullptr;
	}
	void clear()
	{
		destroyTree(root);
		root = nullptr;
	}
	T getRoot()
	{
		return root->getItem();
	}
	void setRoot(T& newItem)
	{
		if (isEmpty())
			root = new Node<T>(newItem);
		else
			root->setItem(newItem);
	}
	int getHeight(Node<T>* node) 
	{
		if (node == nullptr)
			return 0;
		else
			return 1 + max(getHeight(node->getleft()), getHeight(node->getright()));
	}  
	int getNumberOfNodes(Node<T>* node) 
	{
		if (node == nullptr)
			return 0;
		else
			return 1 + getNumberOfNodes(node->getleft()) + getNumberOfNodes(node->getright());
	}  
	Node<T>* balancedAdd(Node<T>* node, Node<T>* newNode)
	{
		if (node == nullptr)
			return newNode;
		else
		{
			Node<T>* pleft = node->getleft();
			Node<T>* pright = node->getright();
			cout << green << getHeight(pleft) << '\t';
			cout << yellow << getHeight(pright) << endl;
			if (getHeight(pleft) < getHeight(pright))
			{
				pleft = balancedAdd(pleft, newNode);
				node->setleft(pleft);
			}
			else
			{
				pright = balancedAdd(pright, newNode);
				node->setright(pright);
			} 
			return node;
		}  
	}  
	Node<T>* copyTree(const Node<T>* tree) 
	{
		Node<T>* newTree = nullptr;
		if (treePtr != nullptr)
		{
			newTree = new Node<T>(tree->getItem());
			newTree->setleft(copyTree(tree->getleft()));
			newTree->setright(copyTree(tree->getright()));
		}  
		return newTree;
	}  
	void destroyTree(Node<T>* subTree)
	{
		if (subTree != nullptr)
		{
			destroyTree(subTree->getleft());
			destroyTree(subTree->getright());
			delete subTree;
		}  
	}  
	bool add(T newData)
	{
		Node<T>* newNode = new Node<T>(newData);
		root = balancedAdd(root, newNode);
		return true;
	}  
	T getEntry(T& anEntry) 
	{
		bool isSuccessful = false;
		Node<T>* node = findNode(root, anEntry, isSuccessful);

		if (isSuccessful)
			return node->getItem();
		else
			throw NotFoundException("Entry not found in tree!");
	}  
	bool contains(T& anEntry) 
	{
		bool isSuccessful = false;
		findNode(root, anEntry, isSuccessful);
		return isSuccessful;
	}  
	void display(T& item)
	{
		cout << item << endl;
	}
	void preorderTraverse() 
	{
		preorder(root);
	} 
	void inorderTraverse() 
	{
		inorder(root);
	}  
	void postorderTraverse() 
	{
		postorder(root);
	}  
	BinaryTree<T>& operator=(BinaryTree<T>& rhs)
	{
		if (!isEmpty())
			clear();
		this = copyTree(&rhs);
		return *this;
	}  
	void preorder(Node<T>* node) 
	{
		if (node != nullptr)
		{
			T t = node->getItem();
			display(t);
			preorder(node->getleft());
			preorder(node->getright());
		} 
	}  
	void parent(int x)
	{
		while (x != 0)
		{
			x = (x - 1) / 2;
			cout << "---|";
		}
	}
	void inorder(Node<T>* node) 
	{
		if (node != nullptr)
		{
			inorder(node->getleft());
			T t = node->getItem();
			display(t);
			inorder(node->getright());
		} 
	}  
	void postorder(Node<T>* node) 
	{
		if (node != nullptr)
		{
			postorder(node->getleft());
			postorder(node->getright());
			T t = node->getItem();
			display(t);
		} 
	} 
};   

void main()
{
	BinaryTree<int> tree1;
	tree1.add(42);
	tree1.add(68);
	tree1.add(35);
	tree1.add(1);
	tree1.add(70);
	tree1.add(25);
	tree1.add(79);
	tree1.add(59);
	tree1.add(63);
	tree1.add(65);

	cout << "Tree Inorder\n";
	tree1.inorderTraverse();
}  

