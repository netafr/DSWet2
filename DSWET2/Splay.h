#ifndef _SPLAY_
#define _SPLAY_
#include "stddef.h"
#include <iostream>

using namespace std;

//Generic Node class for the tree.
template <class T>
class Node {
public:
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
	T data;
	int numNodes; //Num of nodes in node's sub tree (including itself)
	int score;
	int sum;

	/* Description:   Empty Cto'r.
	* Input:         None. 
	*/
	Node<T>():data(), numNodes(1), score(), sum(){}

	/* Description:   Cto'r.
	* Input:         data - reference to generic data.
	*/
	Node<T>(const T& data, const int score) : data(data), numNodes(1), score(score), sum(score){
		left = NULL;
		right = NULL;
		parent = NULL;
	}

	/* Description:   Dto'r.
	*/
	~Node<T>() {
		if(left) delete left;
		if(right) delete right;
	}
};

//Generic Splay tree class.
template <class T>
class SplayTree {
	Node<T>* root;
	/* Description:  Updates numNodes field of given node by his sons.
	* Input:         x, pointer to node in the tree.
	* Output:        None.
	* Return Values: None.
	*/
	void UpdateNumNodes(Node<T>* x) {
		if (!x) return;
		int num_left = x->left ? x->left->numNodes : 0;
		int num_right = x->right ? x->right->numNodes : 0;
		x->numNodes = 1 + num_left + num_right;
	}
	/* Description:  Updates sum field of given node by his sons.
	* Input:         x, pointer to node in the tree.
	* Output:        None.
	* Return Values: None.
	*/
	void UpdateSum(Node<T>* x) {
		if (!x) return;
		x->sum = x->score;
		if (x->left) x->sum += x->left->sum;
		if (x->right) x->sum += x->right->sum;
	}
	/* Description:  Updates additional data of given node by his sons.
	* Input:         x, pointer to node in the tree.
	* Output:        None.
	* Return Values: None.
	*/
	void UpdateNode(Node<T>* x) {
		UpdateNumNodes(x);
		UpdateSum(x);
	}

	/* Description:   Performs "Zig" on the given Node.
	* Input:         x, pointer to node in the tree.
	* Output:        None.
	* Return Values: None.
	*/
	void Zig(Node<T>* x) {
		Node<T>* y = x->parent;
		y->left = x->right;
		if (x->right)
			x->right->parent = y;
		x->right = y;
		x->parent = y->parent;
		if (x->parent) {
			if (x->parent->left == y) {
				x->parent->left = x;
			}
			else {
				x->parent->right = x;
			}
		}
		y->parent = x;
		UpdateNode(y); //Updates additional data after fixes
		UpdateNode(x);
	}

	/* Description:   Performs "Zag" on the given Node.
	* Input:         x, pointer to node in the tree.
	* Output:        None.
	* Return Values: None.
	*/
	void Zag(Node<T>* x) {
		Node<T>* y = x->parent;
		y->right = x->left;
		if (x->left)
			x->left->parent = y;
		x->left = y;
		x->parent = y->parent;
		if (x->parent) {
			if (x->parent->left == y) {
				x->parent->left = x;
			}
			else {
				x->parent->right = x;
			}
		}
		y->parent = x;
		UpdateNode(y); //Updates additional data after fixes
		UpdateNode(x);
	}

	/* Description:   Splays the tree, fixes it using Zigs and Zags.
	* Input:         x, pointer to node in the tree, that we want to be at the root of the tree.
	* Output:        None.
	* Return Values: None.
	*/
	void Splay(Node<T>* x) {
		if (!root || x == root || !x) {
			return;
		}
		while (true) { //Actually until x has no parent. (means x became the root)
			Node<T>* parent = x->parent;
			if (!parent) {
				break;
			}
			Node<T>* grandParent = parent->parent;
			if (!grandParent) { //x is a son of the root.
				//Zig
				if (parent->left == x) {
					Zig(x);
				}
				//Zag
				else {
					Zag(x);
				}
				break;
			}
			else if (grandParent->left == parent) {
				//ZigZig
				if (parent->left == x) {
					Zig(parent);
					Zig(x);
				}
				//ZagZig
				else {
					Zag(x);
					Zig(x);
				}
			}
			else {
				if (parent->left == x) {
					//ZigZag
					Zig(x);
					Zag(x);
				}
				else {
					//ZagZag
					Zag(parent);
					Zag(x);
				}
			}
		}
		root = x;
	}

	/* Description:  Calucates the size of the tree.
	* Input:         root, pointer to the root of the tree.
	* Output:        None.
	* Return Values: The size of the tree.
	*/
	int GetSize(Node<T>* root) {
		if (!root) {
			return 0;
		}
		return GetSize(root->left) + GetSize(root->right) + 1;
	}

	/* Description:  Finds the max node in the tree.
	* Input:         root, pointer to the root of the tree.
	* Output:        None.
	* Return Values: Pointer to the data of the max Node.
	*/
	T* FindMax(Node<T>* root) {
		if (!root) return NULL;
		if (!root->right) {
			return &(root->data);
		}
		Node<T>* max = root->right;
		while (max->right) {
			max = max->right;
		}
		Splay(max);
		return &(max->data);
	}

	/* Description:  Performs a certain action on each node, inorder (helper function).
	* Input:         root, pointer to the root of the tree.
					 a, class instance with operator ().
	* Output:        None.
	* Return Values: None.
	*/
	template <class Action>
	void GenericInorder(Node<T>* root,  Action a) {
		if (!root) return;
		GenericInorder(root->left, a);
		a((root->data));
		GenericInorder(root->right, a);
	}

	/* Description:  Fills the tree from array, inorder.
	* Input:         root, pointer to the root of the tree.
					 arr, array of type T (data).
					 i, current index in the array.
	* Output:        None.
	* Return Values: The last index in the array that was inserted.
	*/
	int FillInorder(Node<T>* root, T* arr, int i) {
		if (!root) return i;
		i = FillInorder(root->left, arr, i);
		root->data = arr[i++];
		i = FillInorder(root->right, arr, i);
		return i;
	}

	/* Description:  Helper function for the copy cto'r, recursivley copies the nodes.
	* Input:         toCopy, pointer to the first node to copy in the tree.
					 parent, parent of the current node.
	* Output:        None.
	* Return Values: Returns the root of the new tree.
	*/
	Node<T>* RecCopy(const Node<T>* toCopy, Node<T>* parent) {
		if (!toCopy) {
			return NULL;
		}
		Node<T>* root = new Node<T>(toCopy->data, toCopy->score);
		root->numNodes = toCopy->numNodes;
		root->sum = toCopy->sum;
		root->parent = parent;
		root->left = RecCopy(toCopy->left, root);
		root->right = RecCopy(toCopy->right, root);
		return root;
	}
	/* Description:  Sums the scores of all nodes with index bigger or equal to k
	* Input:         x - pointer to root of current sub tree
					 k, index to start the sum from
	* Output:        None.
	* Return Values: Returns the sum of scores of nodes with index bigger or equal to k
	*/
	int SumFromK(Node<T>* x, int k) {
		//Same algorithm as find rank k, when turning left will sum up right sub-tree
		int num_left = x->left ? x->left->numNodes : 0;
		if (num_left == k - 1) {
			if (x->right)
				return x->score + x->right->sum;
			else
				return x->score;
		}
		if (num_left > k - 1) {
			if (x->right)
				return SumFromK(x->left, k) + x->score + x->right->sum;
			else
				return SumFromK(x->left, k) + x->score;
		}
		return SumFromK(x->right, k - num_left - 1);
	}

public:
	/* Description:  Empty cto'r.
	* Input:         None.
	*/
	SplayTree<T>() {
		root = NULL;
	}

	/* Description:  Copy cto'r.
	* Input:         toCopy, the tree to copy.
	* Output:        None.
	*/
	SplayTree<T>(const SplayTree<T>& toCopy) {
		root = RecCopy(toCopy.root, NULL);
	}

	/* Description:  Returns the root of the tree.
	* Input:         None.
	* Output:        None.
	* Return Values: Pointer to the root node.
	*/
	Node<T>* GetRoot() {
		return this->root;
	}

	/* Description:  Inserts new node with the given data.
	* Input:         newData, reference to T data.
	* Output:        None.
	* Return Values: Bool, if the insertion was successful.
	*/
	bool Insert(const T& newData, int score) {
		Node<T>* temp = Find(newData);
		if(temp) {
			return false;
		}
		try {
			Node<T>* x = new Node<T>(newData, score);
			if (!root) { //If the tree is empty.
				root = x;
				return true;
			}
			Node<T>* tempRoot = root;
			while (true) //Inserts node and keeps tree as BST.
			{
				//Updates additional data in the insertion path
				tempRoot->numNodes++;
				tempRoot->sum += score;
				if (x->data < tempRoot->data) { //If is on left-subtree
					if (!tempRoot->left) { //If no left son
						tempRoot->left = x;
						x->parent = tempRoot;
						break;
					}
					else { 
						tempRoot = tempRoot->left;
					}
				}
				else { //If is on right-subtree
					if (!tempRoot->right) { //If no right son
						tempRoot->right = x;
						x->parent = tempRoot;
						break;
					}
					else {
						tempRoot = tempRoot->right;
					}
				}
			}
			Splay(x); //Fix the tree, x will be the root.
			return true;
		}
		catch (std::bad_alloc& ba) { //If there was allocation error.
			return false;
		}
	}

	/* Description:  Finds the node with the given data.
	* Input:         toFind, reference to T data.
	* Output:        None.
	* Return Values: The node we searched for, if none was found returns NULL.
	*/
	Node<T>* Find(const T& toFind) {
		Node<T>* tempRoot = root;
		Node<T>* prev = NULL;
		while (tempRoot) {
			if (toFind == tempRoot->data) { //If it's the root
				break;
			}
			else if (toFind < tempRoot->data) { //If it's on the left-subtree
				prev = tempRoot;
				tempRoot = tempRoot->left;
			}
			else { //If it's on the right-subtree
				prev = tempRoot;
				tempRoot = tempRoot->right;
			}
		}
		if(tempRoot) {
			Splay(tempRoot); //Fixes the tree
		}
		else {
			Splay(prev); //If not found splay the closest node
		}
		if (root == tempRoot) { //If the splaying was successful
			return root;
		}
		return NULL;
	}

	/* Description:  Deletes the node with the given data.
	* Input:         toFind, reference to T data.
	* Output:        None.
	* Return Values: If the deletion was successful.
	*/
	bool Delete(const T& toFind) {
		Node<T>* toDelete = Find(toFind);
		if (!toDelete) { //If we didn't find it
			return false;
		} //Note: toDelete splayed and now is the root.
		if (!toDelete->left) { //If no left subtree
			root = toDelete->right;
			if (root) //If right subtree wasnt null
				root->parent = NULL;
		}
		else { //If has left subtree
            //The maximum node in left subtree will become the new root.
            //Finding max in left sub tree will splay it to left sub tree's root
			SplayTree<T> leftSubTree;
			leftSubTree.root= toDelete->left;
            leftSubTree.root->parent = NULL;
			leftSubTree.FindMax();
			root = leftSubTree.GetRoot();
			root->right = toDelete->right;
			leftSubTree.root=NULL;
			if (toDelete->right)
				toDelete->right->parent = root;
		}
		toDelete->right = NULL;
		toDelete->left = NULL;
		delete(toDelete);
		UpdateNode(root);
		return true;
	}

	/* Description:  Performs action on each node, inorder.
	* Input:         a, class instance with operator ().
	* Output:        None.
	* Return Values: None.
	*/
	template <class Action>
	void GenericInorder(Action a) {
		GenericInorder(root, a);
	}

	/* Description:  Fills the tree from array, inorder.
	* Input:         arr, array of T.
	* Output:        None.
	* Return Values: None.
	*/
	void FillInorder(T* arr) {
		FillInorder(root, arr, 0);
	}

	/* Description:  Finds the max node in the tree.
	* Input:         None.
	* Output:        None.
	* Return Values: Pointer to the max node's data.
	*/
	T* FindMax() {
		return FindMax(root);
	}

	/* Description:  Put's the tree's data inorder into array.
	* Input:         arr, array of T.
					 size, the size of the array.
					 root, pointer to the node that is the root of the tree.
					 index, current index in the arrray.
					 p, instance of class, with boolean operator ().
	* Output:        The arrary arr will contain the data of the nodes in the tree, inorder.
	* Return Values: The last index in the tree.
	*/
	template <class Predicate>
	int ConvertToArray(T* arr, int size, Node<T>* root, int index, Predicate p) {
		if (!root) return index;
		index = ConvertToArray(arr, size-1, root->left, index, p);
		if (p(root->data)) {
			arr[index++] = root->data;
		}
		index = ConvertToArray(arr, size-1, root->right, index, p);
		return index;
	}

	/* Description:  Returns pointer to the data of the node with the given data.
	* Input:         toFind, refernce to T (data).
	* Output:        None.
	* Return Values: Pointer to the data of the node, if it doesn't exist returns NULL.
	*/
	T* GetData(const T& toFind) {
		Node<T>* node = Find(toFind);
		return (node) ? &node->data : NULL;
	}

	/* Description:  Returns the size of the tree.
	* Input:         None.
	* Output:        None.
	* Return Values: Size of the tree.
	*/
	int GetSize() {
		return GetSize(root);
	}
	/* Description:  Returns the sum of top k nodes. if k is bigger than size of
	 				 tree or the tree is empty, will return -1.
	* Input:         k - integer representing how many nodes to sum from top
	* Output:        None.
	* Return Values: Sum of best k nodes
	*/
	int SumTopK(int k) {
		if (!root || k > root->numNodes) {
			return -1;
		}
		return SumFromK(root, root->numNodes - k + 1);
	}

	/* Description:  Dto'r.
	*/
	~SplayTree() {
		delete root;
	}
};

#endif

