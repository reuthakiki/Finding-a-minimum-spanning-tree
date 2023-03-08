#include "PriorityQueue.h"
using namespace std;


//ctor by flued
PriorityQueue::PriorityQueue(int max) 
{
	data = new Vertex[max];
	maxsize = max;
	heapsize = 0;
	allocated = 1;
}

PriorityQueue::PriorityQueue() 
{
	data = nullptr;
	maxsize = 0; //max size of heap
	heapsize = 0; //current size of heap
	allocated = 0; // 1 if heap allocated memory
}

//Build Heap by floyd
void PriorityQueue::Build(Vertex nodeArr[], int size) 
{
	heapsize = maxsize = size;
	data = nodeArr;
	allocated = 0;
	for (int i = size / 2 - 1; i >= 0; i--)
		FixHeap(i);
}

//dtor
PriorityQueue::~PriorityQueue() 
{
	if (allocated)
		delete[] data;
	data = nullptr;
}

//finding min value in queue
Vertex PriorityQueue::Min()
{
	return data[0];
}

Vertex PriorityQueue::DeleteMin()
{
	Vertex min = data[0];
	heapsize--;
	data[0] = data[heapsize];
	FixHeap(0);
	return(min);
}

void PriorityQueue::insert(Vertex* item)
{
	if (heapsize == maxsize)	//PriorityQueue is full!
	{
		return;
	}
	else
	{
		int i = heapsize;
		heapsize++;
		while ((i > 0) && (data[Parent(i)].vertexWeight() > item->vertexWeight()))
		{
			data[i] = data[Parent(i)];
			i = Parent(i);
		}
		data[i] = *item;
	}
}

int PriorityQueue::Left(int Node) 
{
	return (2 * Node + 1);
}

int PriorityQueue::Right(int Node) 
{
	return (2 * Node + 2);
}


int PriorityQueue::Parent(int Node) 
{
	return (Node - 1) / 2;
}


void PriorityQueue::FixHeap(int vertexNode)
{
	int left = Left(vertexNode);
	int right = Right(vertexNode);
	int min = vertexNode;

	if (left<heapsize && data[left].vertexWeight()<data[vertexNode].vertexWeight())
	{
		min = left;
	}
	else
	{
		min = vertexNode;
	}

	if (right < heapsize && data[right].vertexWeight()<data[min].vertexWeight())
	{
		min = right;
	}

	if (min!=vertexNode)
	{
		swap(&(data[vertexNode]), &(data[min]));
		FixHeap(min);
	}
}

void PriorityQueue::swap(Vertex* first, Vertex* second)
{
	Vertex temp = *first;
	*first = *second;
	*second = temp;
}

void PriorityQueue::MakeEmpty() 
{
	delete[] data;
	heapsize = 0;
	allocated = 1;
}

bool PriorityQueue::IsEmpty() 
{
	if (heapsize == 0)
		return false;
}

// Decreases value of key at index 'place' to newKey.  It is assumed that
// newKey is smaller than harr[place].
void PriorityQueue::decreaseKey(int place, int newKey)
{
	data[place].setVertexWeight(newKey);
	while (place != 0 && data[Parent(place)].vertexWeight() > data[place].vertexWeight())
	{
		swap(&(data[place]), &(data[Parent(place)]));
		place = Parent(place);
	}
}