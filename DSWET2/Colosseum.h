#ifndef _COLOSEEUM_
#define _COLOSEEUM_

#include "Splay.h"
#include "GladGroup.h"
#include "HashTable.h"
#include "Heap.h"
#include "library2.h"
class Colosseum
{
	SplayTree<int>* gladsTree;
	HashTableN<GladGroup>*  groupsTable;
	Heap* activeGroups;
public:

	/* Description:  C'tor.
	*  Input:        n, size of the array.
					 trainingGroupdsIds, int array of the id's of the groups given.
	*/
	Colosseum(int n, int* trainingGroupsIds);

	/* Description: Adds a group to the system and returns the status of the operation.
	   Input:		trainingGroupId, the id of the new group.
	   Return Value: INVALID_INPUT if trainingGroupId<0, FAILURE if the group is already in the system.
	*/
	StatusType addTrainingGroup(int trainingGroupId);

	/* Description: Adds a gladiator to the system and returns the status of the operation.
	   Input:		gladiatorId, the id of the new gladiator.
					score, the score of the new gladiator.
					trainingGroup, the id of the new gladiator's group.
	   Return Value: INVALID_INPUT if trainingGroupId<0 or score<0 or trainingGroup<0, FAILURE if the gladiator is already in the system or
						the given training group doesn't exist.
	*/
	StatusType addGladiator(int gladiatorId, int score, int trainingGroup);

	/* Description: Makes 2 groups fight (according to the instructions) and returns the status of the operation.
	   Input:		trainingGroup1, the id of the first group that fights.
					trainingGroup2, the id of the second group that fights.
					k1, number of fighting gladiators from the first group.
					k2, number of fighting gladiators from the second group.
	   Return Value: INVALID_INPUT if trainingGroup1<0 or trainingGroup2<0 or k1<=0 or k2<=0 , FAILURE if at least one of the groups doesn't exist,
					 or if they are the same, or if at least one of them can't fight.
	*/
	StatusType trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);

	/* Description: Outputs to the parameter the id of the active group with minimal id and returns the status of the operation.
	   Input:		trainingGroup, pointer to the output parameter.
	   Return Value: INVALID_INPUT if trainingGroup is NULL.
	*/
	StatusType getMinTrainingGroup(int* trainingGroup);

	~Colosseum();
};
#endif

