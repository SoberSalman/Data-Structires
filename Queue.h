#pragma once
#include<iostream>
#include "Stack.h"
using namespace std;



template <typename T>
class Queue
{

	struct node
	{
	public:
		T data = 0;
		node* next = NULL;
	} *front, * rear;

public:
	int size = 0;
	Queue()
	{
		front = NULL;
		rear = NULL;
	}



	void enque(T d) // insert at end
	{
		if (rear == NULL)
		{
			node* temp = new node();
			temp->data = d;
			temp->next = NULL;
			rear = temp;
			front = rear;
			size++;
		}
		else
		{
			node* temp = new node();
			rear->next = temp;
			temp->data = d;
			temp->next = NULL;
			rear = temp;
			size++;
		}
	}

	T Front()
	{
		return front->data;
	}




	T deque()
	{
		node* temp = new node();
		temp = front;
		if (temp == NULL)
		{
			cout << "Memory leak";
			return 0;
		}
		else
		{
			if (temp->next != NULL)
			{
				T save = front->data;
				temp = temp->next;
				//cout << "Element deleted from Queue is : " << front->data << endl;
				free(front);
				front = temp;
				size--;
				return save;

			}
			else
			{
				T save;
				//cout << "Element deleted from Queue is : " << front->data << endl;
				save = front->data;
				free(front);
				front = NULL;
				rear = NULL;
				size--;
				return save;
			}
		}
	}


	void reverseQueue()
	{
		stack<T> Stack;
		while (!isEmpty()) {
			Stack.push(Front());
			deque();
		}

		while (!Stack.isEmpty()) {
			enque(Stack.Top());
			Stack.pop();
		}
	}







	void PrintQueue()
	{
		node* temp = new node();
		temp = front;
		if (front == NULL && rear == NULL)
		{
			cout << "Queue is empty" << endl;
		}
		else
		{
			while (temp != NULL)
			{
				cout << temp->data->data << " ";
				temp = temp->next;
				break;
			}
			//cout << endl;
		}
	}

	bool isEmpty()
	{
		if (front == NULL && rear == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}




};