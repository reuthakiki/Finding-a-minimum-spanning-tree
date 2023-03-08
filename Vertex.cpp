#include "Vertex.h"

int Vertex::vertexWeight()
{
	return weight;
}

int Vertex::vertexValue()
{
	return vertexVal;
}

void Vertex::setVertexValue(int value)
{
	vertexVal = value;
}

void Vertex::setVertexWeight(int edgeWeight)
{
	weight = edgeWeight;
}