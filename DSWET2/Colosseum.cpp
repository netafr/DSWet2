#include "Colosseum.h"



Colosseum::Colosseum(int n, int* trainingGroupsIds) : gladsTree(), groupsTable(), activeGroups() {
	gladsTree = new SplayTree<int>();
	groupsTable = new HashTableN<GladGroup>(n);
	
	Wrapper<int>** wrapArr = new Wrapper<int>*[n];
	for (int i = 0; i < n; ++i)
	{
		wrapArr[i] = new Wrapper<int>(0, trainingGroupsIds[i]);
	}
	activeGroups = new Heap(wrapArr ,n);
	for (int j = 0; j < n; ++j)
	{
		groupsTable->Insert(GladGroup(wrapArr[j]), trainingGroupsIds[j]);
	}
	delete[] wrapArr;
}

StatusType Colosseum::addTrainingGroup(int trainingGroupId)
{
	if (trainingGroupId < 0) {
		return INVALID_INPUT;
	}
	try {
		if (groupsTable->Member(GladGroup(), trainingGroupId)) {
			return FAILURE;
		}
		Wrapper<int>* toInsert = new Wrapper<int>(0, trainingGroupId);
		activeGroups->Insert(toInsert);
		groupsTable->Insert(GladGroup(toInsert), trainingGroupId);
		return SUCCESS;
	}
	catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
}

StatusType Colosseum::addGladiator(int gladiatorId, int score, int trainingGroup)
{
	if (trainingGroup < 0 || gladiatorId < 0 || score < 0) {
		return INVALID_INPUT;
	}
	try {
		if (gladsTree->Find(gladiatorId) || !groupsTable->Member(GladGroup(), trainingGroup)) {
			return FAILURE;
		}
		gladsTree->Insert(gladiatorId, score);
		GladGroup* group = groupsTable->Member(GladGroup(), trainingGroup);
		group->InsertToTree(gladiatorId, score);
		return SUCCESS;
	}
	catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
}

StatusType Colosseum::trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2)
{
	if (k1 <= 0 || k2 <= 0 || trainingGroup1 < 0 || trainingGroup2 < 0) {
		return INVALID_INPUT;
	}
	if (trainingGroup1 == trainingGroup2 || !groupsTable->Member(GladGroup(), trainingGroup1) || !groupsTable->Member(GladGroup(), trainingGroup2)) {
		return FAILURE;
	}
	GladGroup* group1 = groupsTable->Member(GladGroup(), trainingGroup1);
	GladGroup* group2 = groupsTable->Member(GladGroup(), trainingGroup2);
	int sum1 = group1->GetSumTopK(k1);
	int sum2 = group2->GetSumTopK(k2);
	if (sum1 == -1 || sum2 == -1 || group1->GetLost() || group2->GetLost()) {
		return FAILURE;
	}
	GladGroup* losingGroup = NULL;
	if (sum1 == sum2) {
		if (trainingGroup1 < trainingGroup2) { //training Group 1 wins
			losingGroup = group2;
		}
		else { //training Group 2 wins
			losingGroup = group1;
		}
	} 
	else if (sum1 > sum2) { //training Group 1 wins
		losingGroup = group2;
	}
	else { //training Group 2 wins
		losingGroup = group1;
	}
	losingGroup->SetLost();
	activeGroups->DelKey(losingGroup->GetPointer()->GetData());
	return SUCCESS;
}

StatusType Colosseum::getMinTrainingGroup(int * trainingGroup)
{
	if (!trainingGroup) {
		return INVALID_INPUT;
	}
	*trainingGroup = activeGroups->GetMin().GetKey();
	return SUCCESS;
}


Colosseum::~Colosseum()
{
	delete gladsTree;
	delete activeGroups;
	delete groupsTable;
}
