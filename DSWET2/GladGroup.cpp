#include "GladGroup.h"

GladGroup::GladGroup(): lost(false), heapPointer() {
	for (int i = 0; i < MAX_SCORE+1; i++)
	{
		scoreHist[i] = 0;
	}
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

void GladGroup::AddToHist(int score) {
	scoreHist[score]++;
}

int GladGroup::GetSumTopK(int k) {
	int remain = k, score = 0;
	for (int i = MAX_SCORE; i >= 0 && remain > 0; --i)
	{
		if (scoreHist[i] > remain) {
			remain = 0;
			score += k * i;
			break;
		}
		remain -= scoreHist[i];
		score += scoreHist[i] * i;
	}
	return score;
}

GladGroup::~GladGroup(){}
