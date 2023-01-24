
#include<iostream>
#include<list>
#include"LinkedList.h"
using namespace std;

class Graph
{

public:
	bool** adjMatrix;
	int numVertices = 0;

	Graph(){}
	Graph(int numvertices)
	{
		numVertices = numvertices;

		adjMatrix = new bool*[numvertices];

		for (int i = 0; i < numVertices; i++)
		{
			adjMatrix[i] = new bool[numvertices];

		}

		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
			{
				adjMatrix[i][j] = false;
			}
		}





	}

	void addEdge(int i, int j)
	{
		adjMatrix[i-1][j-1] = true;
		adjMatrix[j-1][i - 1] = true;
	}


	void removeEdge(int i, int j)
	{
		adjMatrix[i - 1][j - 1] = false;
		adjMatrix[j - 1][i - 1] = false;
	}

	bool isEdge(int i, int j)
	{
		if (adjMatrix[i - 1][j - 1] == true && adjMatrix[j - 1][i - 1] == true)
		{

			return true;
		}
		return false;
	}
	void print()
	{
		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < numVertices; j++)
			{
				cout << adjMatrix[i][j] << " ";
			}
			cout << endl;
		}

		
	}









};



class Graph2
{
public:
	Linkedlist* adjlist;
	int  n;

	Graph2(int v)
	{
		n = v;
		adjlist = new Linkedlist[v];


	}

	Node* createVertex(string d)
	{
		Node* vertex = new Node();
		vertex->city = d;
		return vertex;
	}

	void addEdge(string src, string dest)
	{
		adjlist[0].inserttohead(src);

	}

	void print()
	{
		for (int i = 0; i < n; i++)
		{
			cout << i << "-->";
			adjlist[i].PrintList();
			cout << endl;
		}
		cout << endl;
	}

	~Graph2()
	{
		for (int i = 0; i < n; i++)
		{
			Linkedlist current = adjlist[i];
			while (!current.isempty())
			{
				Node* temp = current.head;
				while (temp != NULL)
				{
					Node* temp2 = temp;
					temp = temp->next;
					delete temp2;
				}

			}
		}
	}







};