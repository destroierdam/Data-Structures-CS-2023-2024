#include <iostream>
#include "HashTable.hpp"

int main() {
	HashTable<int, int> table;
	table[5] = 1;
	table[10] = 7;
}