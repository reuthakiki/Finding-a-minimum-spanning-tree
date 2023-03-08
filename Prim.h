#pragma once
#include "PriorityQueue.h"
#include "Graph.h"

class Prim
{
public:
	Prim() {} //ctor
	Vertex* FindMinSpreadingTree(Graph* graph);
	int calcuateWeight(Vertex* parentList, int n);
};

