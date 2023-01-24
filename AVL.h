#include<iostream>
using namespace std;

class Node
{
public:
	int data = 0;
	Node* left;
	Node* right;
	int height = 0;
	Node()
	{
		data = 0;
		left = NULL;
		right = NULL;
		height = 0;
	}

	
};


int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int findHeight(Node* N)
{
	if (N == NULL)
	{
		return 0;
	}
	else
	{
		return N->height;
	}
}

int balanceFactor(Node* N)
{
	if (N == NULL)
	{
		return 0;
	}
	else
	{
		return findHeight(N->left) - findHeight(N->right);

	}
}





class AVL
{
	Node* parent = NULL;
public:

	AVL() { parent = NULL; }


	Node* NewNode(int key)
	{
		Node* newNode = new Node();
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = 1;
		newNode->data = key;

		return newNode;
	}

	Node* RightRotate(Node* N)
	{

		Node* temp = N->left;
		Node* temp2 = N->right;

		temp->right = N;
		N->left = temp2;


		N->height = max(findHeight(N->left), findHeight(N->right)) + 1;

		temp->height = max(findHeight(temp->left), findHeight(temp->right)) + 1;

		return temp;
	}


	Node* LeftRotate(Node* N)
	{
		Node* temp = N->right;
		Node* temp2 = temp->left;

		temp->left = N;
		N->right = temp2;


		N->height = max(findHeight(N->left), findHeight(N->right)) + 1;

		temp->height = max(findHeight(temp->left), findHeight(temp->right)) + 1;

		return temp;

	}

	Node* insertNode(Node* N, int key)
	{

		if (N == NULL)
		{
			 N = NewNode(key);
		}
		else if (key < N->data)
		{
			N->left = insertNode(N->left, key);
		}
		else if (key > N->data)
		{
			N->right = insertNode(N->right, key);
		}

		N->height = 1 + max(findHeight(N->left), findHeight(N->right));

		int balance = balanceFactor(N);

		cout << balance << endl;

		if (balance != 0)
		{
			// LEFT LEFT 
			if (balance > 1 && key < N->left->data)
			{
				return RightRotate(N);
			}


			// RIGHT RIGHT
			if (balance < -1 && key > N->right->data)
			{
				return LeftRotate(N);
			}

			// LEFT RIGHT
			if (balance > 1 && key > N->left->data)
			{
				N->left = LeftRotate(N->left);
				return RightRotate(N);
			}

			// Right Left
			if (balance < -1 && key < N->right->data)
			{
				N->right = RightRotate(N->right);
				return LeftRotate(N);
			}
		}
		return N;
	}

	Node* nodeWithMimumValue(Node* node)
	{
		Node* current = node;
		while (current->left != NULL)
		{
			current = current->left;
		}
		return current;
	}





	Node* DeleteNode(Node* N, int key)
	{

		if (N == NULL)
		{
			return N;
		}
		if (key < N->data)
		{
			N->left = DeleteNode(N->left, key);
		}

		else if (key > N->data)
		{
			N->right = DeleteNode(N->right, key);
		}
		else
		{
			if (N->left == NULL || N->right == NULL)
			{
				Node* temp = N->left ? N->left : N->right;

				if (temp == NULL)
				{
					temp = N;
					N = NULL;
				}
				else
				{
					*N = *temp;
				}
				free(temp);
			}
			else
			{
				Node* temp = nodeWithMimumValue(N->right);
				N->data = temp->data;
				N->right = DeleteNode(N->right, temp->data);

			}
		}
		if (N == NULL)
		{
			return N;
		}


		N->height = 1 + max(findHeight(N->left), findHeight(N->right));

		int balance = balanceFactor(N);

		if (balance > 1) 
		{
			if (balanceFactor(N->left) >= 0) 
			{
				return RightRotate(N);
			}
			else 
			{
				N->left = LeftRotate(N->left);
				return RightRotate(N);
			}
		}

		if (balance < -1) 
		{
			if (balanceFactor(N->right) <= 0)
			{
				return LeftRotate(N);
			}
			else 
			{
				N->right = RightRotate(N->right);
				return LeftRotate(N);
			}
		}






		return N;
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












};


