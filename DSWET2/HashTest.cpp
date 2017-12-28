#include <stdlib.h>
#include <stdio.h>
#include "HashTable.h"
#include "GladGroup.h"

int main() {
	//Hash int test
	/*HashTableN<int> table(5);
	cout << table.Member(5, 5) << endl; //0
	cout << table.Insert(5, 5) << endl; //1
	cout << table.Member(5, 5) << endl; //1
	for (int i = 0; i < 5; ++i) {
		cout << table.Insert(i, i) << endl; //1
	}
	cout << table.Insert(10, 15) << endl; //1
	for (int i = 0; i < 5; ++i) {
		cout << table.Insert(i+10, i+10) << endl; //1
	}*/

	//Group hist check
	GladGroup g;
	g.AddToHist(90);
	g.AddToHist(50);
	cout << g.GetSumTopK(1) << endl; //90
	cout << g.GetSumTopK(2) << endl; //140
	g.AddToHist(90);
	g.AddToHist(90);
	g.AddToHist(90);
	cout << g.GetSumTopK(3) << endl; //270
	cout << g.GetSumTopK(10) << endl; //410
	system("pause");
	return 0;
}