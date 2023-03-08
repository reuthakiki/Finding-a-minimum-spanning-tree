#include "Prim.h"

Vertex* Prim::FindMinSpreadingTree(Graph* graph)
{
    int numOfVertices = graph->GetNumberOfVertice();
    int len = 0;
    PriorityQueue Q(numOfVertices);
    bool* inTree = new bool[numOfVertices];
    Vertex* parent = new Vertex[numOfVertices];
    Vertex* weightMin = new Vertex[numOfVertices];
    Vertex u(0, INT32_MAX);

    weightMin[0].setVertexValue(0);
    weightMin[0].setVertexWeight(0);
    parent[0].setVertexValue(-1);
    parent[0].setVertexWeight(0);

    for (int i = 1; i < numOfVertices; i++)
    {
        weightMin[i].setVertexWeight(INT32_MAX);
        weightMin[i].setVertexValue(i);
        inTree[i] = false;
    }

    Q.Build(weightMin, numOfVertices);

    while (Q.IsEmpty()!=false)
    {
        u = Q.DeleteMin();
        int uVal = u.vertexValue();
        inTree[uVal] = true;
        Vertex* neighborList = graph->GetNeighborList(uVal);
        len = graph->GetLenOfNeighborList(uVal);
        for (int i = 0; i < len; i++)
        {
            int j;
            int vVal = neighborList[i].vertexValue();
            int vWeight = neighborList[i].vertexWeight();
            uVal = u.vertexValue();
            for (j = 0; j < numOfVertices; j++) {
                if (weightMin[j].vertexValue() == vVal) {
                    break;
                }
            }
            if (!inTree[vVal] && vWeight < weightMin[j].vertexWeight())
            {
                weightMin[j].setVertexWeight(vWeight);
                parent[vVal].setVertexValue(uVal);
                parent[vVal].setVertexWeight(vWeight);
                Q.decreaseKey(j, vWeight);
            }
        }
    }

    return parent;
}

int Prim::calcuateWeight(Vertex* parentList, int n)
{
    int weight = 0;
    for (int i = 0; i < n; i++)
    {
        weight += parentList[i].vertexWeight();
    }

    return weight;
}