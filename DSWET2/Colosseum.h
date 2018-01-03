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

	Colosseum(int n, int* trainingGroupsIds);

	StatusType addTrainingGroup(int trainingGroupId);

	StatusType addGladiator(int gladiatorId, int score, int trainingGroup);

	StatusType trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2);

	StatusType getMinTrainingGroup(int* trainingGroup);

	~Colosseum();
};
#endif

