#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <math.h>
#include "Graph.h"
#include "Vertex.h"
#include "PriorityQueue.h"
#include "UnionFind.h"
#include "Kruskal.h"
#include "Prim.h"
using namespace std;
#define MAXCHAR 100


int GetInputNandM(char* lineFromFile, fstream& outputFile);
int* GetEdgeLine(char* lineFromFile, int numOfVertex ,fstream& outputFile);
int* GetEdgeLineWithoutWeight(char* lineFromFile, int numOfVertex, fstream& outputFile);
bool isEmptyFile(std::fstream& pFile);
void wrongInput();



int main(int argc, char** argv)
{
	fstream inputFile;
	inputFile.open(argv[1]);
	fstream outputFile;
	outputFile.open(argv[2]);
	char* lineFromFile = new char[MAXCHAR];
	string Line;
	if (isEmptyFile(inputFile))
	{
		wrongInput();	// file is empty
	}

	if (inputFile.eof() != true)
	{
		getline(inputFile, Line);		//get one line to Line from inputfile
		lineFromFile = _strdup(Line.c_str()); //convert string to char*
	}
	int n = GetInputNandM(lineFromFile, outputFile); //n is number of vertex

	if (inputFile.eof() != true)
	{
		getline(inputFile, Line);		//get one line to Line from inputfile
		lineFromFile = _strdup(Line.c_str()); ////convert string to char*
	}
	int m = GetInputNandM(lineFromFile,outputFile); // m is number of edges

	Graph graph(n);
	Kruskal kruskalAlgo(m, n - 1, n);
	Prim primAlgo;
	graph.SetNumberOfVertice(n);
	graph.SetNumberOfEdges(m);
	int* uvLine = new int[2];
	int indexFile = 0;  // 
	while (inputFile.eof() != true)		//while the file isnt empty go over the file 
	{
		int uVertex, vVertex, weight;
		int* uvwLine = new int[3]; 
		indexFile++;
		if (indexFile <= m ) //for over the edges
		{
			getline(inputFile, Line);
			lineFromFile = _strdup(Line.c_str());
			uvwLine = GetEdgeLine(lineFromFile, graph.GetNumberOfVertice(), outputFile);
			graph.SetVertexList(uvwLine[0], uvwLine[1], uvwLine[2]);
		}
		else if (indexFile == m + 1)	//the edge how need to remove
		{
			getline(inputFile, Line);
			lineFromFile = _strdup(Line.c_str());
			uvLine = GetEdgeLineWithoutWeight(lineFromFile, graph.GetNumberOfVertice(), outputFile);
		}
		else
		{
			outputFile << " invalid input" << endl;
			wrongInput();
		}
		delete uvwLine;
	}
	if (indexFile < m + 1)	//num of edges is less of m
	{
		outputFile << " invalid input" << endl;
		wrongInput();
	}
	kruskalAlgo.insertToAllEdge(graph);		//build array edge for kruskal algo
	if (!graph.linkTestInTheGraph(graph))	//linking test for the graph
	{
		cout << "No MST. " << endl;		//print sum of MST with kruskal to screen Without change
		outputFile << "No MST. " << endl;	//print sum of MST with kruskal to file Without change
		exit(1);
	}
	kruskalAlgo.FindMinSpreadingTree(&kruskalAlgo, graph);	//find MST with kruskal algo
	int kruskal = kruskalAlgo.printKruskalWeight(kruskalAlgo.getF(), kruskalAlgo.getSizeEdge());	//calcuate sum of MST

	Vertex* prim = primAlgo.FindMinSpreadingTree(&graph);	//find MST with prim algo
	int primWeight = primAlgo.calcuateWeight(prim, n);	//calcuate sum of MST

	Vertex u(uvLine[0] -1, NULL);
	Vertex v(uvLine[1] -1, NULL);
	graph.IsAdjacent(u, v);		//check if the egde exist
	Graph::vertexList* ptrEdge = nullptr;
	Graph::vertexList* ptrNext = nullptr;
	int tempWeight = graph.checkEdgeInKruskalAlgo(graph, uvLine, ptrEdge, ptrNext);
	v.setVertexWeight(tempWeight);	//the edge part of Kruskal's minimal spreading tree
	Graph::vertexList uVertexNode(u);
	Graph::vertexList vVertexNode(v, ptrEdge, ptrNext, true);
	graph.RemoveEdge(uVertexNode, vVertexNode);		//Remove Edge 
	int kruskalSecond;
	if (tempWeight == INT16_MIN) {	//the edge was not part of Kruskal's minimal spreading tree
		kruskalSecond = kruskal;
	}
	else {
		bool isBridge = graph.linkTestInTheGraph(graph);	//linking test for the graph after remove edge
		if (isBridge)
		{
			kruskalAlgo.RemoveEdge(kruskalAlgo, uvLine, tempWeight);	// remove the edge
			kruskalAlgo.clearAllEdge(graph);	//clear the checkVisit member in the graph how was true in kruskal algo at thr first running
			kruskalAlgo.setIndex(0);		//initialize the index
			kruskalAlgo.FindMinSpreadingTree(&kruskalAlgo, graph);	//find MST after remove the edge with kruskal
			kruskalSecond = kruskalAlgo.printKruskalWeight(kruskalAlgo.getF(), kruskalAlgo.getSizeEdge());	//calcuate sum of MST
		}
		cout << "Kruskal ", cout << kruskal << endl;	//print sum of MST with kruskal to screen
		outputFile << "Kruskal " << kruskal << endl;	//print sum of MST with kruskal to file

		cout << "Prim " << primWeight << endl;	//print sum of MST with prim to screen
		outputFile << "Prim " << primWeight << endl;	//print sum of MST with prim to file

		if (!isBridge)
		{
			cout << "No MST. " << endl;		//print sum of MST with kruskal to screen Without change
			outputFile << "No MST. " << endl;	//print sum of MST with kruskal to file Without change
			exit(1);
		}

		cout << "Kruskal ", cout << kruskalSecond << endl;	//print sum of MST with kruskal to screen after remove edge
		outputFile << "Kruskal " << kruskalSecond << endl;	//print sum of MST with kruskal to file after remove edge
	}
	inputFile.close();
	delete lineFromFile;
}


bool isEmptyFile(std::fstream& pFile)
{
	return pFile.peek() == std::fstream::traits_type::eof();
}

void wrongInput()
{
	cout << " invalid input" << endl;
	exit(1);
}


int* GetEdgeLineWithoutWeight(char* lineFromFile,int numOfVertex, fstream& outputFile)
{
	int* edge = new int[2];
	int i = 0, j = 0, x = 0;
	int allCharInLine = strlen(lineFromFile);	
	char* ptrLine = new char[allCharInLine];
	ptrLine[0] = '\0';
	while (j <= allCharInLine && i < 2)
	{
		ptrLine[x] = lineFromFile[j];
		if (lineFromFile[j] == ' ' || (j == allCharInLine && lineFromFile[j] == '\0'))
		{
			ptrLine[x] = '\0';
			x = -1;
			edge[i] = GetInputNandM(ptrLine, outputFile);
			ptrLine[0] = '\0';
			if (edge[i] < 1 || edge[i] > numOfVertex)
			{
				outputFile << " invalid input" << endl;
				wrongInput();
			}
			i++;
		}
		else if (ptrLine[x] != ' ')
		{
			if (ptrLine[x] == '-' || ptrLine[x] < '0' || ptrLine[x] > '9')
			{
				outputFile << " invalid input" << endl;
				wrongInput();
			}
		}
		x++;
		j++;
	}
	if (allCharInLine > j) {
		outputFile << " invalid input" << endl;
		wrongInput();
	}

	return edge;
}


int* GetEdgeLine(char* lineFromFile, int numOfVertex ,fstream& outputFile)
{
	int* edge = new int[3];
	int i = 0, j = 0, x = 0;
	int allCharInLine = strlen(lineFromFile);		
	char* ptrLine = new char[allCharInLine];
	while (j <= allCharInLine && i < 3)
	{
		ptrLine[x] = lineFromFile[j];
		if (i == 2) 
		{
			if (x == 0) 
			{
				if (ptrLine[x] != '-') 
				{
					if (ptrLine[x] < '0' || ptrLine[x] > '9')
					{
						outputFile << " invalid input" << endl;
						wrongInput();
					}
				}
			}
			else 
			{
				if (j != allCharInLine) 
				{
					if (ptrLine[x] < '0' || ptrLine[x] > '9' )
					{
						outputFile << " invalid input" << endl;
						wrongInput();
					}
				}
			}

		}
		//i is 1 or 0
		else if (ptrLine[x] != ' ') 
		{
			if (ptrLine[x] == '-' || ptrLine[x] < '0' || ptrLine[x] > '9') 
			{
				outputFile << " invalid input" << endl;
				wrongInput();
			}
		}
		if (lineFromFile[j] == ' ' || (j == allCharInLine && lineFromFile[j] == '\0'))
		{
			ptrLine[x] = '\0';
			x = -1;
			edge[i] = GetInputNandM(ptrLine, outputFile);
			ptrLine[0] = '\0';
			if (i == 0 || i == 1)
			{
				if (edge[i] <1 || edge[i] > numOfVertex) 
				{
					outputFile << " invalid input" << endl;
					wrongInput();
				}
			}
			i++;
		}
		x++;
		j++;
	}
	if (allCharInLine > j) {
		outputFile << " invalid input" << endl;
		wrongInput();
	}

	return edge;
}


int GetInputNandM(char* lineFromFile, fstream& outputFile)
{
	int i = 0, temp, sum = 0, p = 0;
	p = strlen(lineFromFile) - 1;		
	while (lineFromFile != 0 && p >= 0)
	{
		temp = (int)lineFromFile[i] - 48;
		if (temp < 0 || temp > 9)
		{
			outputFile << " invalid input" << endl;
			wrongInput();
		}
		sum += temp;
		if (p > 0) {
			sum *= 10;
		}
		i++;
		p--;
	}

	return sum;
}