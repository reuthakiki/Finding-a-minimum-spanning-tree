#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Vertex
{
	int vertexVal;
	int weight;
	public:
	//ctor
	Vertex(int val, int weight) : vertexVal(val), weight(weight) {}
	Vertex() : vertexVal(NULL), weight(NULL) {}
	//dtor
	~Vertex() {}
	//getter
	int vertexWeight();
	int vertexValue();
	friend class Graph;
	//setter
	void setVertexValue(int value);
	void setVertexWeight(int edgeWeight);

};