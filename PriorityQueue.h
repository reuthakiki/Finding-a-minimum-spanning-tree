#pragma once
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include "Vertex.h"

class PriorityQueue
{
private:
	Vertex* data;
	int maxsize; //max size of heap
	int heapsize; //current size of heap
	int allocated; // 1 if heap allocated memory
	static int Left(int vertexnode);	//left son
	static int Right(int vertexnode);	//right son
	static int Parent(int vertexnode);
	void FixHeap(int node);
public:
	PriorityQueue();
	friend class Graph;
	void swap(Vertex* first, Vertex* second);
	PriorityQueue(int max);
	void Build(Vertex nodeArr[], int size); //Build Heap by floyd
	~PriorityQueue();
	void MakeEmpty();
	bool IsEmpty();
	Vertex Min();
	Vertex DeleteMin();
	void insert(Vertex* item);
	void decreaseKey(int place, int newKey);
};