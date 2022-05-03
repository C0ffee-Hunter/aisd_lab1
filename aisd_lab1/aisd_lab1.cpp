#include <iostream>
#include "Class.h"

int main()
{
	int value = 50, key[] = { 55,40,65,60,75,57 };
	Map map;
	List maplist;
	for (int i = 0; i < 6; i++) {
		map.insert(key[i], key[i]);
	}
	map.print();
}