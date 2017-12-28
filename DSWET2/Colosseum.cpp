#include "Colosseum.h"



Colosseum::Colosseum(int n, int* trainingGroupsIds) : gladsTree(), groupsTable(), activeGroups() {
	gladsTree = new SplayTree<int>();
	groupsTable = new HashTableN<GladGroup>(n);
	//Complete
	activeGroups = new Hash();
}


Colosseum::~Colosseum()
{
}
