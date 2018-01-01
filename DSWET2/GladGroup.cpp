#include "GladGroup.h"

GladGroup::GladGroup(): lost(false), heapPointer() {
	gladsTree = new SplayTree<int>();
}

GladGroup::GladGroup(Wrapper<int>* pointer) :lost(false), heapPointer(pointer)
{
	gladsTree = new SplayTree<int>();
}

GladGroup::GladGroup(const GladGroup & other)
{
	lost = other.lost;
	heapPointer = other.heapPointer;
	gladsTree = new SplayTree<int>(*other.gladsTree);
}

Wrapper<int>*GladGroup::GetPointer() const {
	return heapPointer;
}

void GladGroup::SetPointer(Wrapper<int>* heapPointer) {
	this->heapPointer = heapPointer;
}

bool GladGroup::GetLost() const {
	return lost;
}

void GladGroup::SetLost() {
	this->lost = true;
}

void GladGroup::InsertToTree(int gladId, int score)
{
	gladsTree->Insert(gladId, score);
}

int GladGroup::GetSumTopK(int k) {
	return gladsTree->SumFromK(k);
}

GladGroup::~GladGroup(){
	delete gladsTree;
}
