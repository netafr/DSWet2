#ifndef _HASH_
#define _HASH_

#include "Splay.h"

const int DEFAULT_SIZE = 128;
const int FACTOR = 2;


template <class T>
class InsertToNew {
	SplayTree<T>*** insertTo; //Pointer to Array of pointers to trees
	public:
		InsertToNew(SplayTree<T>*** insertTo): insertTo(insertTo) {}
		void operator() (T& treeNode) {
			table->HashInsert(treeNode);
		}
};


template <class T>
class HashTable
{
	int maxSize;
	int currSize;
	SplayTree<T>** table; //Array of pointers to trees

	void Resize() {
		maxSize *= FACTOR;
		SplayTree<T>** oldTable = table; //Save old for copying
		table = new T*[maxSize]; //Allocate new bigger array
		for (int i = 0; i < maxSize; ++i)
		{
			table[i] = NULL; //Zero it out
		}
		int oldSize = currSize;
		currSize = 0;
		for (int j = 0; j < oldSize; ++j) { //Copy existing data
			if (oldTable[j]) {
				SplayTree<T>* tree = oldTable[j];
				InsertToNew insertToNew(&table);
				tree->GenericInorder(insertToNew); //Go over the tree and insert the old values into the new table
				delete tree;
			}
		}
		delete[] oldTable;
	}

public:

	/* Description:  Empty cto'r.
	* Input:         None.
	*/
	HashTable(): maxSize(DEFAULT_SIZE), currSize() {
		table = new SplayTree<T>*[maxSize];
		for (int i = 0; i < maxSize; ++i)
		{
			table[i] = NULL;
		}
	}

	/* Description:  Finds the node with the given data.
	* Input:         toFind, reference to T data.
					 key, the key of the T;
	* Output:        None.
	* Return Values: Whether or not the given T with the given key exists in the table.
	*/
	bool Member(const T& toFind ,int key) {
		int hash = key % maxSize;
		if (table[hash] == NULL) {
			return false;
		}
		SplayTree<T>* treeToSearch = table[hash];
		if (!treeToSearch->Find(toFind)) {
			return false;
		}
		return true;
	}

	void Insert(const T& toInsert, int key) {
		int hash = key % maxSize;
		if (table[hash] == NULL) {
			table[hash] = new SplayTree<T>*();
			table[hash].
		}
	}
	~HashTable() {
	}
};
#endif