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
	void DeleteItem(ItemType item);

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

template <class ItemType>
void TreeType<ItemType> ::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	bool shorter;
	Delete(root, item, shorter);
}

template <class ItemType>
void Delete(TreeNode<ItemType>*& tree, ItemType item, bool& shorter)
{
	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Delete(tree->left, item, shorter);
			// Look in left subtree.
			if (shorter)
				switch (tree->bf)
				{
				case 'L': tree->bf = 'E'; break;
				case 'E': tree->bf = 'R'; shorter = false;
					break;
				case 'R': DelRightBalance(tree, shorter);
				} // END SWITCH	
		}
		else if (item > tree->info)
		{
			Delete(tree->right, item, shorter);
			// Look in right subtree.
			if (shorter)
				switch (tree->bf)
				{
				case 'L': DelLeftBalance(tree, shorter);
				break;				case 'E': tree->bf = 'L'; shorter = false; 							break;
				case 'R': tree->bf = 'E'; break;
				} // END SWITCH
		}
		else
			DeleteNode(tree, shorter);
		// Node found; call DeleteNode.
	} // END if (tree != NULL)
	else
	{
		cout << "\nNOTE: " << item
			<< " not in the tree so cannot be deleted.\n\n";
	}
}


template <class ItemType>
void DeleteNode(TreeNode <ItemType>*& tree, bool& shorter)
// Delete the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no longer in the tree. // If tree is a leaf node or has only one non-NULL child pointer, the node 
// pointed to by tree is deleted; otherwise, the user's data is replaced by its
// logical predecessor and the predecessor's node is deleted.
{
	ItemType data;	TreeNode <ItemType>* tempPtr;
	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
		shorter = true;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
		shorter = true;
	}
	else
	{
		GetPredecessor(tree, data);
		tree->info = data;
		Delete(tree->left, data, shorter);
		// Delete the predecessor node
		if (shorter)
			switch (tree->bf)
			{
			case 'L': tree->bf = 'E'; break;
			case 'E': tree->bf = 'R'; shorter = false;
				break;
			case 'R': DelRightBalance(tree, shorter);
			}
	}
}

template <class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
	tree = tree->left;
	while (tree->right != NULL)
		tree = tree->right;
	data = tree->info;
}

template <class ItemType>
void DelRightBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
	TreeNode<ItemType>* rs = tree->right;
	TreeNode<ItemType>* ls;
	switch (rs->bf)
	{
	case 'R':	tree->bf = rs->bf = 'E';
		RotateLeft(tree);
		shorter = true; break;
	case 'E':	tree->bf = 'R';
		rs->bf = 'L';
		RotateLeft(tree);
		shorter = false; break;
	case 'L':	ls = rs->left;
		switch (ls->bf)
		{
		case 'R':	tree->bf = 'L';
			rs->bf = 'E'; break;
		case 'E':	tree->bf = rs->bf = 'E';
			break;
		case 'L':	tree->bf = 'E';
			rs->bf = 'R'; break;
		} // END SWITCH

		ls->bf = 'E';
		RotateRight(tree->right);
		RotateLeft(tree);
		shorter = true;
	}
}

template <class ItemType>
void DelLeftBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
	TreeNode<ItemType>* ls = tree->left;
	TreeNode<ItemType>* rs;
	switch (ls->bf)
	{
	case 'L':	tree->bf = ls->bf = 'E';
		RotateRight(tree);
		shorter = true; break;
	case 'E':	tree->bf = 'L';
		ls->bf = 'R';
		RotateRight(tree);
		shorter = false; break;
	case 'R':	rs = ls->right;
		switch (rs->bf)
		{
		case 'L':	tree->bf = 'R';
			ls->bf = 'E'; break;
		case 'E':	tree->bf = ls->bf = 'E';
			break;
		case 'R':	tree->bf = 'E';
			ls->bf = 'L'; break;
		} // END SWITCH
		rs->bf = 'E';
		RotateLeft(tree->left);
		RotateRight(tree);
		shorter = true;
	}
}