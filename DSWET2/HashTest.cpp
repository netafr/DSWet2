#include <stdlib.h>
#include <stdio.h>
#include "HashTable.h"

int main() {
	HashTableN<int> table(5);
	cout << table.Member(5, 5) << endl; //0
	cout << table.Insert(5, 5) << endl; //1
	cout << table.Member(5, 5) << endl; //1
	for (int i = 0; i < 5; ++i) {
		cout << table.Insert(i, i) << endl; //1
	}
	cout << table.Insert(10, 15) << endl; //1
	for (int i = 0; i < 5; ++i) {
		cout << table.Insert(i+10, i+10) << endl; //1
	}
	system("pause");
	return 0;
}