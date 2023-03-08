#include "Kruskal.h"
#include <iostream>
#include <fstream>


Kruskal::Kruskal(int numOfEdge, int numEdgeMinSpreadTree, int numVertex) 
{
    UF.setNumOfElemnt(numVertex);  //numVertex=n
    UF.setElementArr(numVertex);
    allEdge = new EdgeSet[numOfEdge];  //numOfEdge = m
    F = new EdgeSet[numEdgeMinSpreadTree]; //numEdgeMinSpreadTree = n-1
    sizeAllEdge = numOfEdge;
    sizeEdge = numEdgeMinSpreadTree;
    numOfVertex = numVertex;
    index = 0;
    firstRunning = true;
}


Kruskal::Kruskal() 
{
    F = nullptr;
    allEdge = nullptr;
    sizeAllEdge = 0;
    sizeEdge = 0;
    numOfVertex = 0;
    index = 0;
    firstRunning = true;
}

void Kruskal::RemoveEdge(Kruskal& kruskalAlgo, int* uvLine,int weight) {
    int index;
    for (int i = 0; i < sizeAllEdge; i++) {
        if (kruskalAlgo.allEdge[i].edgeOfVertex[0] == uvLine[0] -1 && 
            kruskalAlgo.allEdge[i].edgeOfVertex[1] == uvLine[1] -1 &&
            kruskalAlgo.allEdge[i].weightEdge == weight) {
            index = i;
            break;
        }
    }
    if (index < sizeAllEdge)
    {
        // reduce size of array and move all
        // elements on space ahead
        kruskalAlgo.setSizeAllEdge(kruskalAlgo.getsizeAllEdge() - 1);
        for (int j = index; j < kruskalAlgo.getsizeAllEdge(); j++)
            allEdge[j] = allEdge[j + 1];
    }
}

void Kruskal::setSizeAllEdge(int size) {
    sizeAllEdge = size;
}


Kruskal::EdgeSet* Kruskal::FindMinSpreadingTree(Kruskal* tree, Graph& g)
{
    //F <- edgeSet; in ctor
    //DisijoinSets UF; in ctor
    if (firstRunning == true) {
        quickSort(tree->allEdge, 0, sizeAllEdge - 1); //sort allEdge
        setfirstRunning(false);
    }
    UF.setNumOfElemnt(numOfVertex);
    UF.setElementArr(numOfVertex);

    for (int i = 0; i < tree->numOfVertex; i++) 
    {
        UF.MakeSet(i);
    }

    for (int j = 0; j < tree->sizeAllEdge; j++) 
    {
        int u = UF.Find(tree->allEdge[j].edgeOfVertex[0]);
        int v = UF.Find(tree->allEdge[j].edgeOfVertex[1]);
        int w = tree->allEdge[j].weightEdge;
        if (u != v) 
        {
            Graph::vertexList* currentAdj = g.AdjacencyListOfGraph[u].next;
            while (currentAdj != nullptr) {
                if (currentAdj->vertex.vertexValue() == v && currentAdj->vertex.vertexWeight() == w) {
                    currentAdj->checkVisit = true;
                    currentAdj->ptrVertex->checkVisit = true;
                }
                currentAdj = currentAdj->next;
            }

            F[index] = insertToF(tree->allEdge[j].edgeOfVertex[0], tree->allEdge[j].edgeOfVertex[1], w);
            index++;
            UF.Union(u, v);
        }
    }
    return F;
}

void Kruskal::setIndex(int i) 
{
    index = i;
}

void Kruskal::setfirstRunning(bool change) {
    firstRunning = change;
}

Kruskal::EdgeSet Kruskal::insertToF(int u, int v, int w) 
{
    int* newEdgeWeight = new int[3];
    newEdgeWeight[0] = u;
    newEdgeWeight[1] = v;
    newEdgeWeight[2] = w;
    EdgeSet newEdge(newEdgeWeight);
    return newEdge;
}


void Kruskal::insertToAllEdge(Graph& g)
{
    int index = 0;
    for (int i = 0; i < numOfVertex; i++) {
        Graph::vertexList* AdjacencyList = g.GetNeighborListInVertex(i);
        while (AdjacencyList != nullptr) {
            if (!AdjacencyList->checkVisit) {
                allEdge[index].edgeOfVertex[0] = i;
                allEdge[index].edgeOfVertex[1] = AdjacencyList->vertex.vertexValue();
                allEdge[index].weightEdge = AdjacencyList->vertex.vertexWeight();
                AdjacencyList->checkVisit = true; 
                g.SetcheckVisit(AdjacencyList->ptrVertex);
                index++;
                AdjacencyList = AdjacencyList->next;
            }
            else
            {
                AdjacencyList = AdjacencyList->next;
            }
        }
    }
}

void Kruskal::clearAllEdge(Graph& g)
{
    int index = 0;
    for (int i = 0; i < numOfVertex; i++) {
        Graph::vertexList *AdjacencyList = g.GetNeighborListInVertex(i);
        while (AdjacencyList != nullptr) {
            if (AdjacencyList->checkVisit) {
                AdjacencyList->checkVisit = false;
                AdjacencyList = AdjacencyList->next;
            }
            else
            {
                AdjacencyList = AdjacencyList->next;
            }
        }
    }
}


// A utility function to swap two elements
void Kruskal::swap(EdgeSet* a, EdgeSet* b)
{
    int* tempA = new int[3];
    tempA[0] = a->edgeOfVertex[0];
    tempA[1] = a->edgeOfVertex[1];
    tempA[2] = a->weightEdge;
    EdgeSet t(tempA);
    a->edgeOfVertex[0] = b->edgeOfVertex[0];
    a->edgeOfVertex[1] = b->edgeOfVertex[1];
    a->weightEdge = b->weightEdge;
    b->edgeOfVertex[0] = t.edgeOfVertex[0];
    b->edgeOfVertex[1] = t.edgeOfVertex[1];
    b->weightEdge = t.weightEdge;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int Kruskal::partition(EdgeSet arrAllEdge[], int start, int end)
{
    int pivot = arrAllEdge[start].weightEdge;

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arrAllEdge[i].weightEdge <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(&arrAllEdge[pivotIndex], &arrAllEdge[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) 
    {

        while (arrAllEdge[i].weightEdge <= pivot) 
        {
            i++;
        }

        while (arrAllEdge[j].weightEdge > pivot) 
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) 
        {
            swap(&arrAllEdge[i++], &arrAllEdge[j--]);
        }
    }

    return pivotIndex;
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void Kruskal::quickSort(EdgeSet arrAllEdge[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    /* pi is partitioning index, arr[p] is now
    at right place */
    int pi = partition(arrAllEdge, start, end);

    // Separately sort elements before
    // partition and after partition
    quickSort(arrAllEdge, start, pi - 1);
    quickSort(arrAllEdge, pi + 1, end);

}

Kruskal::EdgeSet* Kruskal::getF()
{
    return F;
}

Kruskal::EdgeSet* Kruskal::getAllEdge() {
    return allEdge;
}

int Kruskal::getSizeEdge() 
{
    return sizeEdge;
}

int Kruskal::getsizeAllEdge() {
    return sizeAllEdge;
}

void Kruskal::printArray(EdgeSet F[], int size)
{
    int i;
    for (i = 0; i < size; i++) 
    {
        std::cout << "edge: ", cout << F[i].edgeOfVertex[0] << " ";
        std::cout << F[i].edgeOfVertex[1] << " ";
        std::cout << "weight: ", cout << F[i].weightEdge << endl;
    }
    std::cout << std::endl;
}

int Kruskal::printKruskalWeight(EdgeSet F[], int size) 
{
    int sum = 0;
    for (int i = 0; i < size; i++) 
    {
        sum += F[i].weightEdge;
    }
    return sum;
    /*cout << "Kruskal: ", cout << sum << endl;*/
}