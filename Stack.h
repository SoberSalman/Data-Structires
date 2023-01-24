#pragma once
#include<iostream>
using namespace std;


template <typename T>
class stack {
public:
	stack();
	void push(T);
	T pop();
	T Top();
	bool isEmpty();
	void printStack();
	void clear();
	int size = 0;

private:
	struct node {
		node() { next = NULL; }
		T data;
		node* next;
	}*top;

};

template <typename T>
stack<T>::stack() {
	top = NULL;
}
template <typename T>
void stack<T>::push(T x)
{
	node* newNode = new node;
	newNode->data = x;

	if (top != NULL) {
		newNode->next = top;
		top = newNode;
		size++;
	}
	else {
		newNode->next = NULL;
		top = newNode;
		size++;
	}


}

template <typename T>
T stack<T>::pop()
{
	if (isEmpty()) {
		cout << "Stack is Empty" << endl;
	}
	else {
		T data = top->data;
		node* temp = top;
		top = top->next;
		delete temp;
		return data;
		size--;
	}
}

template <typename T>
T stack<T>::Top()
{
	if (top != NULL)
	{
		return top->data;
	}
	return top->data;
}

template <typename T>
bool stack<T>::isEmpty() {
	if (top == NULL)
	{
		return true;
	}
	return false;

}

template <typename T>
void stack<T>::printStack()
{
	node* temp = top;
	while (temp != NULL)
	{
		cout << temp->data;
		temp = temp->next;
	}
}


template <typename T>
void stack<T>::clear()
{
	while (top != NULL)
	{
		pop();
	}
}
