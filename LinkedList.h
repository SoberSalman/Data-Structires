#pragma once
#pragma once
#include<iostream>
using namespace std;

class Node
{
public:
	int data = 0;
	Node* next = NULL;

	Node()
	{
	}

	Node(int n)
	{
		data = n;
	}

	void setdata(int n)
	{
		data = n;
	}

	int getdata()
	{
		return data;
	}

	void setnode(Node* node)
	{
		next = node;
	}

	Node* getnode()
	{
		return next;
	}
};


class Linkedlist
{
	Node* head = NULL;
public:
	int size = 0;
	Linkedlist()
	{
		head;
	}

	bool insert(int d)
	{
		if (head == NULL)
		{
			Node* newnode = new Node();
			newnode->setdata(d);
			newnode->setnode(NULL);
			head = newnode;
			size++;
			return true;


		}
		else
		{

			Node* newnode = head;

			while (newnode->getnode() != NULL)
			{
				newnode = newnode->getnode();
			}

			Node* temp = new Node(d);

			newnode->setnode(temp);
			size++;
			return true;
		}

	}


	bool inserttohead(int n)
	{
		Node* newnode = new Node();
		newnode->setdata(n);
		newnode->setnode(head);
		head = newnode;
		size++;

		return true;

	}

	bool isempty()
	{
		if (head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool search(int d)
	{
		if (head == NULL)
		{
			return false;
		}

		Node* newnode = new Node();

		newnode = head;





		while (newnode->getnode() != NULL)
		{
			if (newnode->getdata() == d)
			{
				return true;
			}
			newnode = newnode->getnode();
		}
		return false;
	}

	int getelementat(int a)
	{
		if (head == false)
		{
			return 0;
		}

		Node* newnode = new Node();

		newnode = head;

		if (a == 0)
		{
			return newnode->getdata();
		}
		if (a == 1)
		{
			newnode = newnode->getnode();
			return newnode->getdata();
		}

		for (int i = 0; i < size; i++)
		{
			if (i == a)
			{
				return newnode->getdata();
			}
			newnode->getdata();
		}


	}

	bool update(int a, int b)
	{

		Node* newnode = new Node();

		newnode = head;


		while (newnode->getnode() != NULL)
		{
			if (newnode->getdata() == a)
			{
				newnode->setdata(b);
				return true;
			}
			newnode = newnode->getnode();
		}
		return false;


	}


	bool insertAtindex(int d, int index)
	{
		int counter = 0;
		Node* newnode = new Node();
		newnode = head;

		while (newnode->getnode() != NULL)
		{
			if (counter == index - 1)
			{
				newnode->setdata(d);
				return true;
			}
			newnode = newnode->getnode();
			counter++;
		}

		return false;
	}







	bool deletenode(int d)
	{
		if (head == NULL)
		{
			return false;
		}

		Node* newnode = new Node();
		Node* tempnode = new Node();

		newnode = head;
		tempnode = NULL;

		while (newnode->getnode() == NULL)
		{
			tempnode = newnode;
			newnode = newnode->getnode();

			if (newnode->getdata() == d)
			{
				tempnode->setnode(newnode->getnode());
				delete newnode;
				size--;
				return true;

			}
		}

		head = tempnode;

		return false;
	}


	Linkedlist MergeList(Linkedlist L1, Linkedlist L2)
	{

		int* arr = new int[20];

		int i = 0;

		while (L1.head != NULL)
		{
			arr[i] = L1.head->getdata();
			i++;
			L1.head = L1.head->getnode();
		}

		while (L2.head != NULL)
		{
			arr[i] = L2.head->getdata();
			i++;
			L2.head = L2.head->getnode();
		}

		int temp = 0;


		for (int a = 0; a < i; a++)
		{
			for (int j = 0; j < i - 1; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}

		Linkedlist L;

		for (int x = 0; x < i; x++)
		{
			L.insert(arr[x]);
		}

		L.PrintList();


		return L;



	}





	void PrintList()
	{
		while (head != NULL)
		{
			cout << head->getdata() << " ";
			head = head->getnode();
		}
	}





};

