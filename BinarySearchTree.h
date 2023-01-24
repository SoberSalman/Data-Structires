#pragma once
#include<iostream>
#include"Queue.h"
using namespace std;

class Node
{
public:
	int data = 0;
	Node* left;
	Node* right;
	Node()
	{
		data = 0;
		left = NULL;
		right = NULL;
	}

	friend ostream& operator <<(ostream& os, const Node& node)
	{
		os << node.data;
		return os;
	}
};

class BSTREE
{
	Node* parent;
public:
	BSTREE()
	{
		parent = NULL;
	}
	void insert(int d)
	{
		Node* newNode = new Node();
		Node* temp = new Node();
		newNode->data = d;
		newNode->left = NULL;
		newNode->right = NULL;

		if (parent == NULL)
		{
			temp->data = d;
			temp->left = NULL;
			temp->right = NULL;
			parent = temp;

			cout << "Node Inserted \n";
			return;
		}
		else
		{
			temp = parent;
			Node* temp2 = new Node();
			while (temp)
			{
				if (temp->data > d)
				{
					temp2 = temp;
					temp = temp->left;
				}
				else if (temp->data < d)
				{
					temp2 = temp;
					temp = temp->right;
				}

			}

			if (temp2->data > d)
			{
				temp2->left = newNode;
			}
			else
			{
				temp2->right = newNode;
			}
		}
	}

	bool retrieve(int d)
	{
		Node* temp = parent;
		Node* pre = NULL;
		while (temp)
		{
			if (temp->data > d)
			{
				pre = temp;
				temp = temp->left;
			}
			else if (temp->data < d)
			{
				pre = temp;
				temp = temp->right;
			}
			if (temp->data == d)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	void preOrder()
	{
		PreOrderTraversal(parent);
	}

	void PreOrderTraversal(Node* temp)
	{
		if (temp == NULL)
		{
			return;
		}

		cout << " " << temp->data;
		PreOrderTraversal(temp->left);
		PreOrderTraversal(temp->right);
	}



	void postOrder()
	{
		PostOrderTraversal(parent);
	}

	void PostOrderTraversal(Node* temp)
	{
		if (temp == NULL)
		{
			return;
		}

		PostOrderTraversal(temp->left);
		PostOrderTraversal(temp->right);

		cout << " " << temp->data;
	}



	void InOrder()
	{
		InOrderTraversal(parent);
	}

	void InOrderTraversal(Node* temp)
	{
		if (temp == NULL)
		{
			return;
		}

		InOrderTraversal(temp->left);
		cout << " " << temp->data;
		InOrderTraversal(temp->right);
	}




	void LeveLorder()
	{
		LevelOrderTraversal(parent);
	}


	void LevelOrderTraversal(Node *temp)
	{
		int counter = 0;
		if (temp == NULL)
		{
			return;
		}

		Queue <Node*> q;
		q.enque(temp);

		while (!q.isEmpty())
		{
			Node* newnode = q.Front();

			q.PrintQueue();
			q.deque();

			if (counter != 0 && counter % 2 == 0)
			{
				q.reverseQueue();
				q.PrintQueue();
				q.deque();
			}


			if (q.size == 0)
			{
				counter++;
				cout << endl;
				if (counter != 0 && counter % 2 == 0)
				{
					if (newnode->right != NULL)
					{
						q.enque(newnode->right);
					}
					if (newnode->left != NULL)
					{
						q.enque(newnode->left);
					}
				}
				else
				{
					if (newnode->left != NULL)
					{
						q.enque(newnode->left);
					}
					if (newnode->right != NULL)
					{
						q.enque(newnode->right);
					}
				}
			}	
		}
	}












};
