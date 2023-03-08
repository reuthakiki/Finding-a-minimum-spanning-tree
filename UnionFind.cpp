#include "UnionFind.h"

UnionFind::UnionFind() {
	elementArr = nullptr;
	numOfElemnt = 0;
}
UnionFind::UnionFind(int numOfElemnt)
{
	setNumOfElemnt(numOfElemnt);
	setElementArr(numOfElemnt);
	for (int i = 0; i < numOfElemnt; i++)
	{
		elementArr[i].parent = -1;
		elementArr[i].size = 0;
	}
}

void UnionFind::setNumOfElemnt(int num) {
	numOfElemnt = num;
}

void UnionFind::setElementArr(int num) {
	elementArr = new Element[num];
}

void UnionFind::MakeSet(int i)
{
	elementArr[i].parent = i;
	elementArr[i].size = 1;
}

int UnionFind::Find(int i)
{
	if (elementArr[i].parent == i)
	{
		return i;
	}
	else
	{
		return (elementArr[i].parent = Find(elementArr[i].parent));
	}
}

void UnionFind::Union(int repx, int repy)
{
	if (elementArr[repx].size > elementArr[repy].size)
	{
		elementArr[repy].parent = repx;
		elementArr[repx].size += elementArr[repy].size;
	}
	else
	{
		elementArr[repx].parent = repy;
		elementArr[repy].size += elementArr[repx].size;
	}
}