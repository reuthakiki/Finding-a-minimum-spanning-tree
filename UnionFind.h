#pragma once
#include <iostream>
#include <fstream>
#include <string>


typedef struct
{
	int parent; //index of parent
	int size;	//size of tree
}Element;

class UnionFind
{
private:
	Element* elementArr;
	int numOfElemnt;

public:
	//ctor
	UnionFind();
	UnionFind(int numOfElemnt);

	//dtor
	~UnionFind() { delete elementArr; }

	void MakeSet(int x);
	int Find(int x);
	void Union(int repx, int repy);
	void setNumOfElemnt(int num);
	void setElementArr(int num);
};