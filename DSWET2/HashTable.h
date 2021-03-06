#ifndef _HASH_
#define _HASH_

#include "List.h"
#include "Wrapper.h"

#define FACTOR 2


template <class T>
class HashTableN;

template <class T>
class InsertToNew {
	HashTableN<T>* insertTo; //Pointer to Array of pointers to lists
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
	List< Wrapper<T> >** table; //Array of pointers to lists

	/* Description: Resizes (makes it bigger) the table size.
	 * Input: None
	 */
	void Resize() {
		maxSize *= FACTOR;
		List< Wrapper<T> >** oldTable = table; //Save old for copying
		table = new List< Wrapper<T> >*[maxSize]; //Allocate new bigger array
		for (int i = 0; i < maxSize; ++i)
		{
			table[i] = NULL; //Zero it out
		}
		int oldSize = currSize;
		currSize = 0;
		for (int j = 0; j < oldSize; ++j) { //Copy existing data
			if (oldTable[j]) {
				InsertToNew<T> insertToNew(this);
				oldTable[j]->GenericIteration(insertToNew); //Go over the tree and insert the old values into the new table
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
		table = new List< Wrapper<T> >*[maxSize];
		for (int i = 0; i < maxSize; ++i)
		{
			table[i] = NULL;
		}
	}

	/* Description:  Finds the node with the given data.
	* Input:         toFind, reference to T data.
					 key, the key of the T;
	* Output:        None.
	* Return Values: Pointer to the node if exists, otherwise NULL.
	*/
	T* Member(const T& toFind ,int key) {
		int hash = key % maxSize;
		if (table[hash] == NULL) {
			return NULL;
		}
		Wrapper<T>* member = table[hash]->GetData(Wrapper<T>(toFind, key));
		if (!member) {
			return NULL;
		}
		return &(member->GetData());
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
			table[hash] = new List< Wrapper<T> >();
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