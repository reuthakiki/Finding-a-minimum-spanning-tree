#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "UnionFind.h"
#include "Graph.h"
using namespace std;

class Kruskal
{
private:
	struct EdgeSet
	{
		int edgeOfVertex[2];	//array of vertex on edge
		int weightEdge;		//weight of edge

		//ctor
		EdgeSet(int* vertexWeight) 
		{
			edgeOfVertex[0] = vertexWeight[0],
			edgeOfVertex[1] = vertexWeight[1],
			weightEdge = vertexWeight[2];
		}
		EdgeSet() :edgeOfVertex(), weightEdge() {}
	};

	EdgeSet* allEdge;	//array of all edges
	EdgeSet* F;		//array of MST in kruskal
	UnionFind UF;	
	int numOfVertex;
	int index;	//index for F
	int sizeEdge;	//size of MST
	int sizeAllEdge;	//size of allEdge array
	bool firstRunning;	//check if this thr first run befor remove edge

public:
	Kruskal();
	Kruskal(int numOfEdge, int numEdgeMinSpreadTree, int numVertex);
	EdgeSet* FindMinSpreadingTree(Kruskal* tree, Graph& g);
	EdgeSet insertToF(int u, int v, int w);
	void insertToAllEdge(Graph& g);
	void clearAllEdge(Graph& g);
	void printArray(EdgeSet arrAllEdge[], int size);
	int printKruskalWeight(EdgeSet F[], int size);
	void quickSort(EdgeSet arrAllEdge[], int low, int high);
	int partition(EdgeSet arrAllEdge[], int low, int high);
	void swap(EdgeSet* a, EdgeSet* b);
	void RemoveEdge(Kruskal& kruskalAlgo,int* uvLine, int weight);

	//setter
	void setSizeAllEdge(int size);
	void setIndex(int i);
	void setfirstRunning(bool change);

	//getter
	EdgeSet* getF();
	EdgeSet* getAllEdge();
	int getSizeEdge();
	int getsizeAllEdge();
};

