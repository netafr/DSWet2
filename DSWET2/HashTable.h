#ifndef _HASH_
#define _HASH_

#include "Splay.h"
#include "Wrapper.h"

const int FACTOR = 2;


template <class T>
class HashTableN;

template <class T>
class InsertToNew {
	HashTableN<T>* insertTo; //Pointer to Array of pointers to trees
	public:
		InsertToNew(HashTableN<T>* insertTo): insertTo(insertTo) {}
		void operator() (Wrapper<T>& treeNode) {
			insertTo->Insert(treeNode.GetData(), treeNode.GetKey());
		}
};


template <class T>
class HashTableN
{
	int maxSize;
	int currSize;
	SplayTree< Wrapper<T> >** table; //Array of pointers to trees

	 /* Description: Resizes (makes it bigger) the table size.
	 * Input: None
	 */
	void Resize() {
		maxSize *= FACTOR;
		SplayTree< Wrapper<T> >** oldTable = table; //Save old for copying
		table = new SplayTree< Wrapper<T> >*[maxSize]; //Allocate new bigger array
		for (int i = 0; i < maxSize; ++i)
		{
			table[i] = NULL; //Zero it out
		}
		int oldSize = currSize;
		currSize = 0;
		for (int j = 0; j < oldSize; ++j) { //Copy existing data
			if (oldTable[j]) {
				InsertToNew<T> insertToNew(this);
				oldTable[j]->GenericInorder(insertToNew); //Go over the tree and insert the old values into the new table
				//delete tree;
			}
		}
		for (int k = 0; k < currSize; ++k)
		{
			if (oldTable[k])
				delete oldTable[k];
		}
		delete[] oldTable;
	}

public:

	/* Description:  Empty cto'r.
	* Input:         n, initial size.
	*/
	HashTableN(int n): maxSize(n), currSize() {
		table = new SplayTree< Wrapper<T> >*[maxSize];
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
		if (!table[hash]->Find(Wrapper<T>(toFind,key))) {
			return false;
		}
		return true;
	}

	/* Description:  Inserts new element with the given data and key.
	* Input:         toInsert, reference to T data.
					 key, the key of toInsert.
	* Output:        None.
	* Return Values: Bool, if the insertion was successful.
	*/
	bool Insert(const T& toInsert, int key) {
		if (Member(toInsert, key)) {
			return false;
		}
		int hash = key % maxSize;
		if (table[hash] == NULL) {
			table[hash] = new SplayTree< Wrapper<T> >();
			table[hash]->Insert(Wrapper<T>(toInsert, key));
		}
		else {
			table[hash]->Insert(Wrapper<T>(toInsert, key));
		}
		currSize++;
		if (currSize >= maxSize) {
			Resize();
		}
		return true;
	}

	/* Description:   Dto'r.
	*/
	~HashTableN() {
		for (int i = 0; i < maxSize; ++i)
		{
			if(table[i])
				delete table[i];
		}
		delete[] table;
	}
};
#endif