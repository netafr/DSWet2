#ifndef _GROUP_
#define _GROUP_

#include "Splay.h"
#include "Wrapper.h"
class GladGroup
{
	bool lost;
	Wrapper<int>* heapPointer;
	SplayTree<int>* gladsTree;

public:
	/* Description:  Empty cto'r.
	*  Input:         None.
	*/
	GladGroup();

	/* Description:   cto'r.
	*  Input:         pointer, a pointer to the heap.
	*/
	GladGroup(Wrapper<int>* pointer);

	GladGroup(const GladGroup& other);

	/* Description:  Returns the pointer to the matching group in the heap.
	   Input:		 None.
	   Return Value: The pointer to the heap.
	   */
	Wrapper<int>* GetPointer() const;

	/* Description:  Sets the pointer to the matching group in the heap.
	   Input:		 The new pointer.
	   Return Value: None.
	*/
	void SetPointer(Wrapper<int>* heapPointer);

	/* Description:  Returns whether or not the team has lost yet.
	   Input:		 None.
	   Return Value: If the team has lost yet.
	*/
	bool GetLost() const;

	/* Description:  Sets the team status to lost.
	   Input:	     None.
	   Return Value: None.
	*/
	void SetLost();

	void InsertToTree(int gladId, int score);

	/* Description:  Returns the sum of the top K gladiators' scores.
	   Input:		 k, num of scores to sum.
	   Return Value: The wanted sum, if k is bigger than the number of glads returns -1;.
	*/
	int GetSumTopK(int k);

	/* Description:   Dto'r.
	*/
	~GladGroup();
};
#endif

