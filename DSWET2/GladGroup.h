#ifndef _GROUP_
#define _GROUP_

#define MAX_SCORE 100

#include "Wrapper.h"
class GladGroup
{
	bool lost;
	Wrapper<int>* heapPointer;
	int scoreHist[MAX_SCORE + 1];

public:
	/* Description:  Empty cto'r.
	*  Input:         None.
	*/
	GladGroup();

	/* Description:   cto'r.
	*  Input:         pointer, a pointer to the heap.
	*/
	GladGroup(Wrapper<int>* pointer);

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

	/* Description:  Adds a glad's score to the hist.
	   Input:	     score, the glad's score.
	   Return Value: None.
	*/
	void AddToHist(int score);

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

