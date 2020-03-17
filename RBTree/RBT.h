#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

// class RBTree implements the operations in Red Black Tree
template <class T, class V>
class RBTree {
private:

	// data structure that represents a node in the tree
	struct Node {
		T data; // holds the key
		V value; //holds the value
		Node* parent; // pointer to the parent
		Node* left; // pointer to left child
		Node* right; // pointer to right child
		bool isRed; // true -> Red, false -> Black
	};
	typedef Node* NodePtr;
	NodePtr root;
	NodePtr NIL;

	// initializes the nodes with appropirate values
	// all the pointers are set to point to the null pointer
	void initializeNULLNode(NodePtr node, NodePtr parent) {
		node->data = 0;
		node->value = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->isRed = false;
	}

void clearHelper(NodePtr root)
	{	
		if (root != NIL)
		{
			clearHelper(root->left);
			clearHelper(root->right);
			delete root;
		}

		
	}


	void preOrderHelper(NodePtr node) {
		if (node != NIL) {
			cout << node->data << " ";
			cout << node->value << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	void inOrderHelper(NodePtr node, bool keys, bool values) {
		if (node != NIL) {
			inOrderHelper(node->left, keys, values);
			if (keys == true)
				cout << node->data << endl;
			if (values == true)
				cout << node->value << endl;
			inOrderHelper(node->right, keys, values);
		}
	}

	void postOrderHelper(NodePtr node) {
		if (node != NIL) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout << node->data << " ";
			cout << node->value << " ";
		}
	}

	bool searchTreeHelper(NodePtr node, T key) {
		if (node == NIL || key == node->data) {
			if (node == NIL){
				cout << "The tree does not contain key " << key << endl;
				return false;
			}
			else {
				cout << "The tree does contain " << key << ". Its value is " << node->value << endl;
				return true;
			}
		}

		if (key < node->data) {
			return this->searchTreeHelper(node->left, key);
		}
		return this->searchTreeHelper(node->right, key);
	}

	// fix the rb tree modified by the delete operation
	void fixDelete(NodePtr instead_scnd) {
		NodePtr sibling;
		while (instead_scnd != root && instead_scnd->isRed == false) {
			if (instead_scnd == instead_scnd->parent->left) {
				sibling = instead_scnd->parent->right;
				if (sibling->isRed == true) {
					// case 3.1
					sibling->isRed = false;
					instead_scnd->parent->isRed = true;
					leftRotate(instead_scnd->parent);
					sibling = instead_scnd->parent->right;
				}

				if (sibling->left->isRed == false && sibling->right->isRed == false) {
					// case 3.2
					sibling->isRed = true;
					instead_scnd = instead_scnd->parent;
				}
				else {
					if (sibling->right->isRed == false) {
						// case 3.3
						sibling->left->isRed = false;
						sibling->isRed = true;
						rightRotate(sibling);
						sibling = instead_scnd->parent->right;
					}

					// case 3.4
					sibling->isRed = instead_scnd->parent->isRed;
					instead_scnd->parent->isRed = false;
					sibling->right->isRed = false;
					leftRotate(instead_scnd->parent);
					instead_scnd = root;
				}
			}
			else {
				sibling = instead_scnd->parent->left;
				if (sibling->isRed == true) {
					// case 3.1
					sibling->isRed = false;
					instead_scnd->parent->isRed = true;
					rightRotate(instead_scnd->parent);
					sibling = instead_scnd->parent->left;
				}

				if (sibling->left->isRed == false && sibling->right->isRed == false) {
					// case 3.2
					sibling->isRed = true;
					instead_scnd = instead_scnd->parent;
				}
				else {
					if (sibling->left->isRed == false) {
						// case 3.3
						sibling->right->isRed = false;
						sibling->isRed = true;
						leftRotate(sibling);
						sibling = instead_scnd->parent->left;
					}

					// case 3.4
					sibling->isRed = instead_scnd->parent->isRed;
					instead_scnd->parent->isRed = false;
					sibling->left->isRed = false;
					rightRotate(instead_scnd->parent);
					instead_scnd = root;
				}
			}
		}
		instead_scnd->isRed = false;
	}

	//replacing first node with second node
	void rbTransplant(NodePtr first_node, NodePtr scnd_node) {
		if (first_node->parent == nullptr) {
			root = scnd_node;
		}
		else if (first_node == first_node->parent->left) {
			first_node->parent->left = scnd_node;
		}
		else {
			first_node->parent->right = scnd_node;
		}
		scnd_node->parent = first_node->parent;
	}

	void deleteNodeHelper(NodePtr node, T key) {
		// find the node containing key
		NodePtr cur = NIL;
		NodePtr instead_scnd, instead_first;
		bool found = false;
		while (node != NIL) {
			if (node->data == key) {
				cur = node;
				found = true;
			}
			if (node->data <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (found == false && node == NIL) {
			throw "There's no key like that";
			return;
		}
	


		instead_first = cur;
		bool instead_original_color = instead_first->isRed;
		if (cur->left == NIL) {
			instead_scnd = cur->right;
			rbTransplant(cur, cur->right);
		}
		else if (cur->right == NIL) {
			instead_scnd = cur->left;
			rbTransplant(cur, cur->left);
		}
		else {
			instead_first = minimum(cur->right);
			instead_original_color = instead_first->isRed;
			instead_scnd = instead_first->right;
			if (instead_first->parent == cur) {
				instead_scnd->parent = instead_first;
			}
			else {
				rbTransplant(instead_first, instead_first->right);
				instead_first->right = cur->right;
				instead_first->right->parent = instead_first;
			}

			rbTransplant(cur, instead_first);
			instead_first->left = cur->left;
			instead_first->left->parent = instead_first;
			instead_first->isRed = cur->isRed;
		}
		delete cur;
		if (instead_original_color == false) {
			fixDelete(instead_scnd);
		}
	}

	// fix the red-black tree
	void fixInsert(NodePtr key) {
		NodePtr uncle;
		while (key->parent->isRed == true) {
			if (key->parent == key->parent->parent->right) {
				uncle = key->parent->parent->left; // uncle
				if (uncle->isRed == true) {
					// case 3.1 - 
					uncle->isRed = false;
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					key = key->parent->parent;
				}
				else {
					if (key == key->parent->left) {
						// case 3.2.2 - 
						key = key->parent;
						rightRotate(key);
					}
					// case 3.2.1 - 
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					leftRotate(key->parent->parent);
				}
			}
			else {
				uncle = key->parent->parent->right; 

				if (uncle->isRed == true) {
					// mirror case 3.1 - 
					uncle->isRed = false;
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					key = key->parent->parent;
				}
				else {
					if (key == key->parent->right) {
						// mirror case 3.2.2 - 
						key = key->parent;
						leftRotate(key);
					}
					// mirror case 3.2.1
					key->parent->isRed = false;
					key->parent->parent->isRed = true;
					rightRotate(key->parent->parent);
				}
			}
			if (key == root) {
				break;
			}
		}
		root->isRed = false;
	}

	void printHelper(NodePtr root, string indent, bool last) {
		// print the tree structure on the screen
		if (root != NIL) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "     ";
			}
			else {
				cout << "L----";
				indent += "|    ";
			}

			string sColor = root->isRed ? "RED" : "BLACK";
			cout << root->data << " " << root->value << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
		// cout<<root->left->data<<endl;
	}

public:
	RBTree() {
		NIL = new Node;
		NIL->isRed = false;
		NIL->left = nullptr;
		NIL->right = nullptr;
		root = NIL;
	}

	// Pre-Order traversal
	// Node->Left Subtree->Right Subtree
	void preorder() {
		preOrderHelper(this->root);
	}

	// In-Order traversal
	// Left Subtree -> Node -> Right Subtree
	void inorder(bool keys, bool values) {
		inOrderHelper(this->root, keys, values);
	}

	// Post-Order traversal
	// Left Subtree -> Right Subtree -> Node
	void postorder() {
		postOrderHelper(this->root);
	}

	// search the tree for the key k
	// and return the corresponding node
	bool find(T k) {
		return searchTreeHelper(this->root, k);
	}

	// find the node with the minimum key
	NodePtr minimum(NodePtr node) {
		while (node->left != NIL) {
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	NodePtr maximum(NodePtr node) {
		while (node->right != NIL) {
			node = node->right;
		}
		return node;
	}

	// find the successor of a given node
	NodePtr successor(NodePtr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != NIL) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		NodePtr y = x->parent;
		while (y != NIL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	NodePtr predecessor(NodePtr x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left != NIL) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != NIL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// rotate left at node x
	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != NIL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != NIL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// insert the key to the tree in its appropriate position
	// and fix the tree
	void insert(T key, V value) {
		// Ordinary Binary Search Insertion
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->value = value;
		node->left = NIL;
		node->right = NIL;
		node->isRed = true; // new node must be red

		NodePtr items_parent = nullptr;
		NodePtr item = this->root;

		while (item != NIL) {
			items_parent = item;
				
			if (node->data < item->data) {
				item = item->left;
			}
			else {
				item = item->right;
			}
		}

		node->parent = items_parent;
		if (items_parent == nullptr) {
			root = node;
		}
		else if (node->data < items_parent->data) {
			items_parent->left = node;
		}
		else {
			items_parent->right = node;
		}

		// if new node is a root node, simply return
		if (node->parent == nullptr) {
			node->isRed = false;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == nullptr) {
			return;
		}

		// Fix the tree
		fixInsert(node);
	}

	NodePtr getRoot() {
		return this->root;
	}

	// delete the node from the tree
	void remove(T data) {
		deleteNodeHelper(this->root, data);
	}

	// print the tree structure on the screen
	void Print() {
		if (root != NIL) {
			printHelper(this->root, "", true);
		}
		else {
			try {
				if (root == NIL)
					throw "The tree is empty";
			}
			catch (const char* msg)
			{
				cout << msg << endl;
			}
		}
		
	}

	void clear()
	{
		if (root != NIL) {
			clearHelper(this->root);
			this->root = NIL;
		}
		else
		{
			try {
				if (root == NIL)
					throw "The tree is empty";
			}
			catch (const char* msg)
			{
				cout << msg << endl;

			}
		}
		
	}

	

	void get_keys() {
		inorder(true, false);
	}

	void get_values() {
		inorder(false, true);
	}

};
