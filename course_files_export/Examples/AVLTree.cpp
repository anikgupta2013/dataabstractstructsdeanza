#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include<array>
#include"ConsoleColor.h"

using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>(T d) { data = d; }
}; 

template <typename T>
class BinaryTree
{
	Node<T>* root;
public:
	BinaryTree() { root = NULL; }
	Node<T>* getRoot() { return root; }
	void setRoot(Node<T>* np) { root = np; }
	int height(Node<T>* temp)
	{
		int h = 0;
		if (temp != NULL)
		{
			int l_height = height(temp->left);
			int r_height = height(temp->right);
			int max_height = max(l_height, r_height);
			h = max_height + 1;
		}
		return h;
	}
	int diff(Node<T>* temp)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int b_factor = l_height - r_height;
		return b_factor;
	}
	// Left - Right Rotation
	Node<T>* lr_rotation(Node<T>* parent)
	{
		cout << green << "lr_rotation: " << parent->data << endl;
		Node<T>* tempL = parent->left;
		parent->left = rr_rotation(tempL);
		return ll_rotation(parent);
	}
	// Right- Left Rotation
	Node<T>* rl_rotation(Node<T>* parent)
	{
		cout << yellow << "rl_rotation: " << parent->data << endl;
		Node<T>* temp = parent->right;
		parent->right = ll_rotation(temp);
		return rr_rotation(parent);
	}
	// Right- Right Rotation
	Node<T>* rr_rotation(Node<T>* parent)
	{
		cout << yellow << "rr_rotation: " << parent->data << endl;
		Node<T>* temp = parent->right;
		parent->right = temp->left;
		temp->left = parent;
		return temp;
	}
	// Left- Left Rotation
	Node<T>* ll_rotation(Node<T>* parent)
	{
		cout << green << "ll_rotation: " << parent->data << endl;
		Node<T>* temp = parent->left;
		parent->left = temp->right;
		temp->right = parent;
		return temp;
	}
	void Validate(Node<T>* pnode, string s)
	{
		if (pnode)
			cout << s << "\t0x" << hex << pnode << '\t' << dec << pnode->data << endl;
		else
			cout << s << '\t' << "NULL" << endl;
	}
	void ValidateNode(Node<T>* pnode, string s)
	{
		if (pnode)
		{
			Validate(pnode,"parent");
			Validate(pnode->left,"left");
			Validate(pnode->right,"right");
		}
		else
			cout << s << '\t' << "NULL" << endl;
	}

	// Balancing AVL Tree
	Node<T>* balance(Node<T>* temp)
	{
		int bal_factor = diff(temp);
		if (bal_factor > 1)
		{
			if (diff(temp->left) > 0)
				temp = ll_rotation(temp);
			else
				temp = lr_rotation(temp);
		}
		else if (bal_factor < -1)
		{
			if (diff(temp->right) > 0)
				temp = rl_rotation(temp);
			else
				temp = rr_rotation(temp);
		}
		return temp;
	}
	// Insert Element into the tree
	Node<T>* insert(Node<T>* root, int value)
	{
		if (root == NULL)
		{
			cout << blue << "inserting root-- " << value << endl;
			root = new Node<T>(value);
			root->left = NULL;
			root->right = NULL;
			return root;
		}
		else if (value < root->data)
		{
			cout << blue << "inserting left<< " << value << endl;
			root->left = insert(root->left, value);
			root = balance(root);
		}
		else if (value >= root->data)
		{
			cout << blue << "inserting rite>> " << value << endl;
			root->right = insert(root->right, value);
			root = balance(root);
		}
		return root;
	}
	void display(Node<T>* ptr, int level=1)
	{
		if (ptr != NULL)
		{
			display(ptr->right, level + 1);
			cout << blue << endl;
			if (ptr == root)
				cout << "Root -> ";
			for (int i = 0; i < level && ptr != root; i++)
				cout << "        ";
			cout << ptr->data;
			display(ptr->left, level + 1);
		}
	}
	void inorder(Node<T> *tree)
	{
		if (tree == NULL)
			return;
		inorder(tree->left);
		Validate(tree, "");
		inorder(tree->right);
	}
	void preorder(Node<T>* tree)
	{
		if (tree == NULL)
			return;
		cout << tree->data << "  ";
		preorder(tree->left);
		preorder(tree->right);

	}
	void postorder(Node<T>* tree)
	{
		if (tree == NULL)
			return;
		postorder(tree->left);
		postorder(tree->right);
		cout << tree->data << "  ";
	}
};

void main()
{
	BinaryTree<int> tree;
	array<int,10> alist = { 42, 68, 35, 1, 70, 25, 79, 59, 63, 65 };
	for (int x = 0; x < alist.size(); x++)
	{
		tree.setRoot(tree.insert(tree.getRoot(), alist[x]));
		tree.display(tree.getRoot());
		cout << "\n\n------------------------------------------------------------\n";
	}
	cout << "\nInorder ------------------------------------------------------------\n";
	tree.inorder(tree.getRoot());
}