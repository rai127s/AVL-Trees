#pragma once
#include <iomanip>
#include <iostream>
using namespace std;

template <class ItemType>
struct TreeNode
{
	ItemType info;
	TreeNode* left;
	TreeNode* right;
	char bf;
};

template<class ItemType>
class TreeType
{
public:
	TreeNode<ItemType>* root;
	TreeType();
	void InsertItem(ItemType item);
	void PT();
	void SearchItem(ItemType item);
	
private:
	void Print(TreeNode<ItemType>* digit);
	bool Search(TreeNode<ItemType>* digit, ItemType item);

};

template<class ItemType>
TreeType<ItemType>::TreeType()
{
	root = NULL;
}

template <class ItemType>
void TreeType<ItemType> ::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller;
	Insert(root, item, taller);
}

template <class ItemType>
void Insert(TreeNode<ItemType>*& tree, ItemType item, bool& taller)
// Inserts item into tree.
// Post:	item is in tree; search property is maintained.
{
	if (tree == NULL)
	{					// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->left = NULL;
		tree->right = NULL;
		tree->info = item;
		tree->bf = 'E';
		taller = true;
	}
	else if (item == tree->info)
	{
		cerr << "Duplicate key is not allowed in AVL tree." << endl;
	}
	else if (item < tree->info)
	{
		Insert(tree->left, item, taller);
		if (taller)
			switch (tree->bf)
			{
			case 'L': LeftBalance(tree, taller); break;
			case 'E': tree->bf = 'L'; break;
			case 'R': tree->bf = 'E'; taller = false; break;
			}
	}
	else if (item > tree->info)
	{
		Insert(tree->right, item, taller);
		if (taller)
			switch (tree->bf)
			{
			case 'R': RightBalance(tree, taller); break;
			case 'E': tree->bf = 'R'; break;
			case 'L': tree->bf = 'E'; taller = false; break;
			}
	}
}


template <class ItemType>
void RightBalance(TreeNode<ItemType>*& tree, bool& taller)
{
	TreeNode<ItemType>* rs = tree->right;
	TreeNode<ItemType>* ls;

	switch (rs->bf)
	{
	case 'R':	tree->bf = rs->bf = 'E';
		RotateLeft(tree);
		taller = false;
		break;
	case 'E':	cerr << "Tree already balanced " << endl;
		break;
	case 'L':	ls = rs->left;
		switch (ls->bf)
		{
		case 'R':	tree->bf = 'L';
			rs->bf = 'E';
			break;
		case 'E':	tree->bf = rs->bf = 'E';
			break;
		case 'L':	tree->bf = 'E';
			rs->bf = 'R';
			break;
		}
		ls->bf = 'E';
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}
}

template <class ItemType>
void LeftBalance(TreeNode<ItemType>*& tree, bool& taller)
{
	TreeNode<ItemType>* ls = tree->left;
	TreeNode<ItemType>* rs;

	switch (ls->bf)
	{
	case 'L':	tree->bf = ls->bf = 'E';
		RotateRight(tree);
		taller = false;
		break;
	case 'E':	cerr << "Tree already balanced " << endl;
		break;
	case 'R':	rs = ls->right;
		switch (rs->bf)
		{
		case 'L':	tree->bf = 'R';
			ls->bf = 'E';		break;
		case 'E':	tree->bf = ls->bf = 'E';	break;
		case 'R':	tree->bf = 'E';
			ls->bf = 'L';		break;
		}
		rs->bf = 'E';
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}



template <class ItemType>
void RotateLeft(TreeNode<ItemType>*& tree)
{
	TreeNode<ItemType>* rs;

	if (tree == NULL)
		cerr << "Cannot rotate an empty tree in RotateLeft"
		<< endl;
	else if (tree->right == NULL)
		cerr << "Cannot make an empty subtree the root in RotateLeft" << endl;
	else
	{
		rs = tree->right;
		tree->right = rs->left;
		rs->left = tree;
		tree = rs;
	}
}

template <class ItemType>
void RotateRight(TreeNode<ItemType>*& tree)
{
	TreeNode<ItemType>* ls;

	if (tree == NULL)
		cerr << "Cannot rotate an empty tree in RotateRight"
		<< endl;
	else if (tree->left == NULL)
		cerr << "Cannot make an empty subtree the root in RotateRight" << endl;
	else
	{
		ls = tree->left;
		tree->left = ls->right;
		ls->right = tree;
		tree = ls;
	}
};

template <class ItemType>
void TreeType<ItemType>::PT()
{
	cout << "Root node: " << root->info << " \tbalance factor: " << root->bf;
	Print(root);

}

template <class ItemType>
void TreeType<ItemType>::Print(TreeNode<ItemType>* digit)
{
	if (digit != NULL)
	{
		cout << " \tNode: " << digit->info << " \tbalance factor: " << digit->bf;
		if (digit->left != NULL)
		{
			cout << " \tMoving Left\n";
			Print(digit->left);
			cout << "Returning to Node " << digit->info << " from its left subtree\n\n";
		}

		else
		{
			cout << " \nLeft subtree is empty ";
		}

		cout << " \tNode: " << digit->info << " \tbalance factor: " << digit->bf;

		if (digit->right != NULL)
		{
			cout << " \tMoving right\n";
			Print(digit->right);
			cout << "Returning to Node " << digit->info << " from its right subtree\n\n";
		}

		else
		{
			cout << " \nRight subtree is empty\n\n";
		}
	}
}

template <class ItemType>
void TreeType<ItemType> ::SearchItem(ItemType item)
{
	Search(root, item);
}

template <class ItemType>
bool TreeType<ItemType>::Search(TreeNode<ItemType>* digit, ItemType item)
{
	if (digit == NULL)
	{
		return false;
	}

	if (digit->info == item)
	{
		cout << "Item has been found \n\n";
	}

	else if (digit->info != item)
	{
		cout << "Item has not been found\n";
		Search(digit->left, item);
		Search(digit->right, item);
	}
}
