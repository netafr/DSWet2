#ifndef _COLOSEEUM_
#define _COLOSEEUM_

#include "Splay.h"
#include "GladGroup.h"
#include "HashTable.h"
#include "Heap.h"

typedef enum {
	SUCCESS = 0,
	FAILURE = -1,
	ALLOCATION_ERROR = -2,
	INVALID_INPUT = -3
} StatusType;

class Colosseum
{
	SplayTree<int>* gladsTree;
	HashTableN<GladGroup>*  groupsTable;
	Heap activeGroups;
public:

	Colosseum();

	StatusType addTrainingGroup(int trainingGroupId);

	StatusType addGladiator(int gladiatorId, int score, int trainingGroup);

	StatusType trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);

	StatusType getMinTrainingGroup(int* trainingGroup);

	~Colosseum();
};
#endif

