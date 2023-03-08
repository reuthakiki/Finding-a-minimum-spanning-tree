#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include "Vertex.h"


class Graph
{
private:
public:
	struct vertexList
	{
		Vertex vertex;	 //vertex
		vertexList* ptrVertex;	// ptr vertex for unadjusted edge
		bool checkVisit;		//symbolizes an edge that was in Kruskal's MST in the first run
		vertexList* next;		//ptr to the next neighbor of vertex
		//ctor
		vertexList(Vertex ver) { vertex = ver, ptrVertex = nullptr, next = nullptr; checkVisit = false; }
		vertexList(Vertex ver, vertexList* ptr, vertexList* nextptr,bool check) 
		{
			vertex = ver, ptrVertex = ptr, next = nextptr, checkVisit = check;
		}
		vertexList() :ptrVertex(nullptr), next(nullptr) {}
	};
	
	vertexList* AdjacencyListOfGraph; // array of all vertex for adjacency List
	vertexList** pos; // pointer to edge that has not been visited 
	int numOfVertex;
	int numOfEdges;

	//ctor
	Graph();
	Graph(int numOfVertex);
	//dtor
	~Graph();
	void MakeEmptyGraph(int numOfVertex); //make graph without edge
	bool CheckInputVertexValueValidity(int value);	//check if vertex is valid
	bool IsAdjacent(Vertex uVertex, Vertex vVertex); //check if this edge exist
	vertexList* GetAdjList(Vertex uVertex);
	Vertex CreateNewVertex(int vertexValue);
	Vertex CreateNewVertex(int vertexValue, int vertexWeight);
	vertexList CreateNewVertexList(int vertexValue);
	void AddEdge(Vertex uVertex, Vertex vVertex, int edgeWeight);
	vertexList* CreatNewNeighbor(Vertex VertexValue, int edgeWeight);
	void RemoveEdge(vertexList uVertex, vertexList vVertex);	//remove edge (u,v) that means remove (u,v) and also (v,u)
	void RemoveEdgeOneDirection(vertexList uVerte, vertexList vVertex);
	int IsEmpty();
	int AddEdge(int uVertex, int vVertex, int weight);
	int checkEdgeInKruskalAlgo(Graph& graph,int* uvLine, vertexList* ptr, vertexList* ptrNext);
	void edgeDoesntExist();
	void PrintGraph();
	int CountDigits(int number);
	bool linkTestInTheGraph(Graph& g);
	int DFSAlgorithm();
	void Visit(int vertex,int* color);
	void PrintSpaces(int vertexNumberOfDigits, int numberOfVeticesDigits);
	void wrongInput();

	//getter
	Graph::vertexList* GetNeighborList();
	Vertex* GetNeighborList(int vertexValue);
	vertexList* GetNeighborListInVertex(int vertex);
	int GetNumberOfVertice();
	int GetNumberOfEdges();
	int GetLenOfNeighborList(int vertexValue);


	//setter
	void SetNumberOfVertice(int numberVer);
	void SetNumberOfEdges(int numberEdges);
	void SetVertexList(int u, int v, int weight);
	void SetcheckVisit(vertexList* ptr);
};