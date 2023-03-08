#include "Graph.h"


using namespace std;
//ctor
Graph::Graph()
{
	AdjacencyListOfGraph = nullptr;
	numOfVertex = 0;
	pos = nullptr;
}

Graph::Graph(int inumOfVertex)
{
	AdjacencyListOfGraph = new vertexList[inumOfVertex]; //the array size is numOfVertex
	numOfVertex = inumOfVertex;
	pos = new vertexList * [inumOfVertex];
	MakeEmptyGraph(numOfVertex);
}

void Graph::MakeEmptyGraph(int numOfVertex)
{
	for (int i = 0; i < numOfVertex; i++)
	{
		AdjacencyListOfGraph[i].vertex.vertexVal = -1;
		AdjacencyListOfGraph[i].vertex.weight = NULL;
		AdjacencyListOfGraph[i].checkVisit = false;
		AdjacencyListOfGraph[i].ptrVertex = nullptr;
		AdjacencyListOfGraph[i].next = nullptr;
	}
}

bool Graph::IsAdjacent(Vertex uVertex, Vertex vVertex)
{
	vertexList* currentPtr = AdjacencyListOfGraph[uVertex.vertexVal].next;
	while (currentPtr != nullptr)
	{
		if (currentPtr->vertex.vertexVal == vVertex.vertexVal)
		{
			return true;
		}
		currentPtr = currentPtr->next;
	}

	edgeDoesntExist();
}

void Graph::edgeDoesntExist()
{
	wrongInput();
}

void Graph::wrongInput()
{
	std::cout << "wrong input" << std::endl;
	exit(1);
}

bool Graph::CheckInputVertexValueValidity(int value) {
	bool validity = false;
	if (value > 0 && value <= numOfVertex) {
		validity = true;
	}
	return validity;
}

Graph::vertexList* Graph::GetAdjList(Vertex uVertex) {
	return AdjacencyListOfGraph[uVertex.vertexVal].next;
}

Vertex Graph::CreateNewVertex(int vertexValue)
{
	Vertex newVertex(vertexValue - 1, NULL); //entering suitable value to array value
	return newVertex;
}

Vertex Graph::CreateNewVertex(int vertexValue, int vertexWeight)
{
	Vertex newVertex(vertexValue - 1, vertexWeight); //entering suitable value to array value
	return newVertex;
}

Graph::vertexList Graph::CreateNewVertexList(int vertexValue)
{
	Vertex newVertex = CreateNewVertex(vertexValue); //create u vertex
	vertexList newVertexList(newVertex); //entering suitable value to array value
	return newVertexList;
}

void Graph::AddEdge(Vertex uVertex, Vertex vVertex, int edgeWeight) {
	vertexList* newNeighbor1 = CreatNewNeighbor(vVertex, edgeWeight);
	vertexList* newNeighbor2 = CreatNewNeighbor(uVertex, edgeWeight);
	newNeighbor1->next = AdjacencyListOfGraph[uVertex.vertexVal].next;
	newNeighbor2->next = AdjacencyListOfGraph[vVertex.vertexVal].next;
	newNeighbor1->ptrVertex = newNeighbor2;
	newNeighbor2->ptrVertex = newNeighbor1;
	AdjacencyListOfGraph[uVertex.vertexVal].next = newNeighbor1;
	AdjacencyListOfGraph[vVertex.vertexVal].next = newNeighbor2;

}

int Graph::CountDigits(int number) {
	int counterDigits = 0;
	while (number != 0) {
		counterDigits++;
		number /= 10;
	}
	return counterDigits;
}

//function helps print graph
void Graph::PrintSpaces(int i_VertexNumberOfDigits, int i_NumberOfVeticesDigits) {
	int numberOfSpacesToPrint = i_NumberOfVeticesDigits - i_VertexNumberOfDigits;
	for (int i = 0; i < numberOfSpacesToPrint; i++) {
		cout << " ";
	}
}

void Graph::PrintGraph() {

	cout << endl;
	for (int i = 0; i < numOfVertex; i++)
	{
		int numberOfVeticesDigits = CountDigits(numOfVertex);
		int vertexIValueDigits = CountDigits(AdjacencyListOfGraph[i].vertex.vertexVal + 1);
		vertexList* currentPtr = AdjacencyListOfGraph[i].next;
		while (currentPtr != nullptr)
		{
			PrintSpaces(vertexIValueDigits, numberOfVeticesDigits);
			cout << "     " <<
				AdjacencyListOfGraph[i].vertex.vertexVal + 1 << "     ";
			int CurrentPtrValueDigits = CountDigits(currentPtr->vertex.vertexVal + 1);
			PrintSpaces(CurrentPtrValueDigits, numberOfVeticesDigits);

			cout << currentPtr->vertex.vertexVal + 1 << endl;
			currentPtr = currentPtr->next;
		}
	}
	cout << endl;
}


Graph::vertexList* Graph::CreatNewNeighbor(Vertex VertexValue, int edgeWeight) {
	vertexList* newNeighbor = new vertexList();
	newNeighbor->vertex.vertexVal = VertexValue.vertexVal;
	newNeighbor->vertex.weight = edgeWeight;
	newNeighbor->ptrVertex = nullptr;
	newNeighbor->checkVisit = false;
	newNeighbor->next = nullptr;
	return newNeighbor;
}

void Graph::RemoveEdge(vertexList uVertex, vertexList vVertex)
{
	vertexList* currentPtr = AdjacencyListOfGraph[uVertex.vertex.vertexVal].next;
	if (currentPtr->vertex.vertexVal == vVertex.vertex.vertexVal)
	{
		vertexList* ptr1 = currentPtr->ptrVertex;
		RemoveEdgeOneDirection(uVertex, vVertex);
		RemoveEdgeOneDirection(vVertex, *ptr1);
	}
	else
	{
		bool notFound = true;
		while (currentPtr != nullptr && notFound)
		{
			if (currentPtr->next->vertex.vertexVal == vVertex.vertex.vertexVal)		
			{
				currentPtr = currentPtr->next;
				vertexList* ptr2 = currentPtr->ptrVertex;
				RemoveEdgeOneDirection(uVertex, vVertex);
				RemoveEdgeOneDirection(vVertex, *ptr2);
				notFound = false;
			}
			currentPtr = currentPtr->next;
		}
	}
}

void Graph::SetcheckVisit(vertexList* ptr) {
	ptr->checkVisit = true;
}


void Graph::RemoveEdgeOneDirection(vertexList uVertex, vertexList vVertex)
{
	vertexList* currentPtr = AdjacencyListOfGraph[uVertex.vertex.vertexVal].next;
	if (currentPtr->vertex.vertexVal == vVertex.vertex.vertexVal)
	{
		AdjacencyListOfGraph[uVertex.vertex.vertexVal].next = currentPtr->next;
		currentPtr->next = nullptr;
		currentPtr->ptrVertex = nullptr;
		delete currentPtr;
	}
	else {
		bool notFound = true;
		while (currentPtr != nullptr && notFound)
		{
			if (currentPtr->next->vertex.vertexVal == vVertex.vertex.vertexVal)
			{
				vertexList* temp = currentPtr->next;
				currentPtr->next = currentPtr->next->next;
				notFound = false;
				temp->next = nullptr;
				temp->ptrVertex = nullptr;
				delete temp;
			}
			currentPtr = currentPtr->next;
		}
	}
}

int Graph::IsEmpty()
{
	if (numOfVertex == 0)
		return 1;
	else return 0;
}

int Graph::checkEdgeInKruskalAlgo(Graph& graph,int* uvLine, vertexList* ptr, vertexList* ptrNext) {
	int tempWeight = INT16_MIN;		//the edge was not in first time on kruskal algo
	Graph::vertexList* currentPtr = graph.AdjacencyListOfGraph[uvLine[0] -1].next;
	while (currentPtr != nullptr) {
		if (currentPtr->vertex.vertexValue() == uvLine[1]-1 && currentPtr->checkVisit == true) {
			tempWeight = currentPtr->vertex.vertexWeight();
			ptr = currentPtr->ptrVertex;
			ptrNext = currentPtr->next;
		}
		currentPtr = currentPtr->next;
	}
	return tempWeight;
}

int Graph::AddEdge(int uVertex, int vVertex, int weight) 
{
	Vertex v = CreateNewVertex(vVertex);
	Vertex u = CreateNewVertex(uVertex);

	if (!(CheckInputVertexValueValidity(uVertex) && CheckInputVertexValueValidity(vVertex))) {
		wrongInput();
	}
	else 
	{
		vertexList* newNeighbor = CreatNewNeighbor(v, weight);
		newNeighbor->next = AdjacencyListOfGraph[u.vertexVal].next;
		AdjacencyListOfGraph[u.vertexVal].next = newNeighbor;
		return 1;
	}
}

Graph::vertexList* Graph::GetNeighborList()
{
	return AdjacencyListOfGraph;
}

Graph::vertexList* Graph::GetNeighborListInVertex(int vertex)
{
	return AdjacencyListOfGraph[vertex].next;
}
Vertex* Graph::GetNeighborList(int vertexValue)
{
	int lenOfList = 0;
	int i = 0;
	vertexList* list = AdjacencyListOfGraph[vertexValue].next;
	Vertex* res = nullptr;

	if (list == nullptr)
		return res;

	do
	{
		lenOfList++;
		list = list->next;
	} while (list != nullptr);

	res = new Vertex[lenOfList];
	list = AdjacencyListOfGraph[vertexValue].next;
	do
	{
		res[i].setVertexValue(list->vertex.vertexValue());
		res[i].setVertexWeight(list->vertex.vertexWeight());
		i++;
		list = list->next;
	} while (list != nullptr);

	return res;
}

int Graph::GetLenOfNeighborList(int vertexValue)
{
	int lenOfList = 0;
	int i = 0;
	vertexList* list = AdjacencyListOfGraph[vertexValue].next;

	do
	{
		lenOfList++;
		list = list->next;
	} while (list != nullptr);

	return lenOfList;
}

int Graph::GetNumberOfVertice() 
{
	return numOfVertex;
}

int Graph::GetNumberOfEdges() {
	return numOfEdges;
}

//dtor
Graph::~Graph()
{
	for (int i = 0; i < numOfVertex; i++)
	{
		vertexList* currentPtr = AdjacencyListOfGraph[i].next;
		while (currentPtr != nullptr)
		{
			vertexList* toDelete = currentPtr;
			currentPtr = currentPtr->next;
			toDelete->next = nullptr;
			toDelete->ptrVertex = nullptr;
			delete toDelete;
		}
	}
	delete[] AdjacencyListOfGraph;
}

bool Graph::linkTestInTheGraph(Graph& g)
{	
	bool check = true;	//Check if there is a route from vertex 0 to all
	int sum = DFSAlgorithm(); //running bfs from starting vertex
	if (sum == 1) {
		return check;
	}
	else {
		check = false;
		return check;
	}
}


int Graph::DFSAlgorithm()
{
	int* color = new int[numOfVertex];	// 0=white, 1=gray, 2=black
	int countLinkComponent = 0;
	//INIT
	for (int i = 0; i < numOfVertex; i++) {
		color[i] = 0;
	}
	//MAIN LOOP
	for (int i = 0; i < numOfVertex; i++) {
		if (color[i] == 0) {
			Visit(i, color);
			countLinkComponent++;
		}
	}

	return countLinkComponent;
}

void Graph::Visit(int vertex, int* color) {
	color[vertex] = 1;	//besin processing of u
	Graph::vertexList* currentAdj = AdjacencyListOfGraph[vertex].next;
	while (currentAdj != nullptr) {
		if (color[currentAdj->vertex.vertexVal] == 0) {
			Visit(currentAdj->vertex.vertexVal, color);
		}
		currentAdj = currentAdj->next;
	}
	color[vertex] = 2;

}

void Graph::SetNumberOfVertice(int numberVer) {
	numOfVertex = numberVer;
}

void Graph::SetNumberOfEdges(int numberEdges) {
	numOfEdges = numberEdges;
}

void Graph::SetVertexList(int u, int v, int weight)
{
	vertexList uVertexList, vVertexList;
	if (AdjacencyListOfGraph[u - 1].next == nullptr) //u has not initialized yet
	{
		uVertexList = CreateNewVertexList(u);
		AdjacencyListOfGraph[u - 1] = uVertexList;
	}
	if (AdjacencyListOfGraph[v - 1].next == nullptr) //u has not initialized yet
	{
		vVertexList = CreateNewVertexList(v);
		AdjacencyListOfGraph[v - 1] = vVertexList;
	}
	Vertex uVertex = CreateNewVertex(u);
	Vertex vVertex = CreateNewVertex(v);
	AddEdge(uVertex, vVertex, weight);

}