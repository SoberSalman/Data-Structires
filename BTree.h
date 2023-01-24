#pragma once
#include <iostream>
#include "LinkedList.h"
#include <fstream>
#include <string>
#include <cctype>

using namespace std;


template<typename T>
struct BTreeNode {


	T* keys;
	BTreeNode** Children;
	Linkedlist* locations;
	string filename = "";
	int numKeys;
	bool isLeaf;
	int minDegree;



	BTreeNode(int n, bool leaf) {

		minDegree = n;
		isLeaf = leaf;

		keys = new T[2 * minDegree - 1];
		Children = new BTreeNode * [2 * minDegree];
		locations = new Linkedlist[2 * minDegree - 1];

		numKeys = 0;

	}

	void nameFiles(string s) {

		int i = 0;
		for (i = 0; i < numKeys; i++) {

			if (!isLeaf) {

				Children[i]->nameFiles(s);

			}

		}

		filename = s;
		filename += to_string(keys[0]) + "-" + to_string(keys[numKeys - 1]) + ".txt";

		if (!isLeaf) {

			Children[i]->nameFiles(s);

		}

	}

	void nameFiless(string s) {

		int i = 0;
		for (i = 0; i < numKeys; i++) {

			if (!isLeaf) {

				Children[i]->nameFiless(s);

			}

		}

		filename = s;
		filename += keys[0] + "-" + keys[numKeys - 1] + ".txt";

		if (!isLeaf) {

			Children[i]->nameFiless(s);

		}

	}

	void traverse() {

		int i = 0;

		for (i = 0; i < numKeys; i++) {

			if (!isLeaf) {

				Children[i]->traverse();

			}

			//cout << " " << keys[i];

		}

		ofstream fout(filename);

		for (i = 0; i < numKeys; i++)
		{

			if (!isLeaf) {

				fout << Children[i]->filename << endl;

			}

		}

		LNode* temp;

		for (int i = 0; i < numKeys; i++) {

			temp = locations[i].gethead();

			for (int j = 0; j < locations[i].size; j++) {

				fout << temp->getdata() << endl;
				temp = temp->getnode();

			}

			fout << endl;

		}

		fout.close();


		if (!isLeaf) {

			Children[i]->traverse();

		}

	}

	void traverse2(T num1, T num2) {

		int i = 0;
		for (i = 0; i < numKeys; i++) {

			if (!isLeaf) {

				Children[i]->traverse2(num1, num2);

			}

			Linkedlist l = locations[i];
			LNode* lol = l.gethead();
			string location = "";
			string filename = "";
			int lineNum = -1;
			string temp = "";
			int countedStuff = 0;
			string data = "";

			if (keys[i] >= num1 && keys[i] <= num2) {

				for (int i = 0; i < l.size; i++) {

					location = lol->getdata();

					//cout << location << endl;

					countedStuff = 0;

					for (int j = 0; j < location.length(); j++) {

						if (location[j] != ',') {

							temp += location[j];

						}

						else {

							if (countedStuff == 0) {

								filename = temp;
								temp = "";
								countedStuff++;

							}

						}

					}

					lineNum = stoi(temp);

					temp = "";

					lol = lol->getnode();

					ifstream fin(filename);

					for (int i = 0; i < lineNum; i++) {

						getline(fin, data);

					}

					cout << data << endl;

					fin.close();

				}

			}


		}

		if (!isLeaf) {

			Children[i]->traverse2(num1, num2);

		}

	}


	BTreeNode* search(T n) {

		int i = 0;

		while (i < numKeys && n > keys[i]) {

			i++;

		}
		if (keys[i] == n) {

			return this;

		}

		if (isLeaf) {

			return NULL;

		}

		return Children[i]->search(n);

	}


	T findKey(T n) {

		int index = 0;

		while (keys[index] < n && index < numKeys) {

			index++;

		}

		return index;

	}

	void insertWhenNotFull(T n) {

		int i = numKeys - 1;

		if (isLeaf) {

			while (i >= 0 && keys[i] > n) {

				keys[i + 1] = keys[i];
				i--;

			}

			keys[i + 1] = n;
			numKeys++;

		}

		else {

			while (i >= 0 && keys[i] > n) {

				i--;

			}

			if (Children[i + 1]->numKeys == 2 * minDegree - 1) {

				splitChild(i + 1, Children[i + 1]);

				if (keys[i + 1] < n) {

					i++;

				}

			}

			Children[i + 1]->insertWhenNotFull(n);

		}

	}

	void splitChild(int n, BTreeNode* b) {

		BTreeNode* newNode = new BTreeNode(b->minDegree, b->isLeaf);
		newNode->numKeys = minDegree - 1;

		for (int i = 0; i < minDegree - 1; i++) {

			newNode->keys[i] = b->keys[i + minDegree];

		}

		if (b->isLeaf == false) {

			for (int i = 0; i < minDegree; i++) {

				newNode->Children[i] = b->Children[i + minDegree];

			}

		}

		b->numKeys = minDegree - 1;

		for (int i = numKeys; i >= n + 1; i--) {

			Children[i + 1] = Children[i];

		}

		Children[n + 1] = newNode;

		for (int i = numKeys - 1; i >= n; i--) {

			keys[i + 1] = keys[i];

		}

		keys[n] = b->keys[minDegree - 1];

		numKeys++;

	}

	void remove(T k) {

		int index = findKey(k);

		if (index < numKeys && keys[index] == k) {

			if (isLeaf) {

				removeFromLeaf(index);

			}

			else {

				removeFromInnerNode(index);

			}

		}

		else {

			if (isLeaf) {

				//Key does not exist in this tree
				return;

			}

			bool isPresent = false;

			if (index == numKeys) {

				isPresent == true;

			}

			else {

				isPresent == false;

			}

			if (Children[index]->numKeys < minDegree) {

				fill(index);

			}

			if (isPresent && index > numKeys) {

				Children[index - 1]->remove(k);

			}

			else {

				Children[index]->remove(k);

			}

		}

	}

	void removeFromLeaf(int index) {

		for (int i = index + 1; i < numKeys; i++) {

			keys[i - 1] = keys[i];

		}

		numKeys--;

	}

	void removeFromInnerNode(int index) {

		T child = keys[index];

		if (Children[index]->numKeys >= minDegree) {

			T behind = getBehind(index);
			keys[index] = behind;
			Children[index]->remove(behind);

		}

		else if (Children[index - 1]->numKeys >= minDegree) {

			T nextOne = getNext(index);
			keys[index] = nextOne;
			Children[index + 1]->remove(nextOne);

		}

		else {

			merge(index);
			Children[index]->remove(child);

		}

		return;

	}

	T getBehind(int index) {

		BTreeNode<T>* currentNode = Children[index];

		while (currentNode->isLeaf == false) {

			currentNode = currentNode->Children[currentNode->numKeys];

		}

		return currentNode->keys[currentNode->numKeys - 1];

	}

	T getNext(int index) {


		BTreeNode<T>* currentNode = Children[index];

		while (currentNode->isLeaf == false) {

			currentNode = currentNode->Children[0];

		}

		return currentNode->keys[0];

	}

	void fill(int index) {

		if (index != 0 && Children[index - 1]->numKeys >= minDegree) {

			takeBehind(index);

		}

		else if (index != numKeys && Children[index + 1]->numKeys >= minDegree) {

			takeFront(index);

		}

		else {

			if (index != numKeys) {

				merge(index);

			}

			else {

				merge(index - 1);

			}

		}

	}

	void takeBehind(int index) {

		BTreeNode<T>* child = Children[index];
		BTreeNode<T>* sibling = Children[index - 1];


		for (int i = child->numKeys - 1; i >= 0; i--) {

			child->keys[i + 1] = child->keys[i];

		}

		if (child->isLeaf == false) {

			for (int i = child->numKeys; i >= 0; i--) {

				child->Children[i + 1] = child->Children[i];

			}

		}

		child->keys[0] = keys[index - 1];

		if (child->isLeaf == false) {

			child->Children[0] = sibling->Children[sibling->numKeys];

		}

		keys[index - 1] = sibling->keys[sibling->numKeys - 1];

		child->numKeys += 1;
		sibling->numKeys -= 1;

	}

	void takeFront(int index) {

		BTreeNode<T>* child = Children[index];
		BTreeNode<T>* sibling = Children[index + 1];

		child->keys[child->numKeys] = keys[index];

		if (child->isLeaf == false) {

			child->Children[(child->numKeys) + 1] = sibling->Children[0];

		}

		keys[index] = sibling->keys[0];

		for (int i = 1; i < sibling->numKeys; i++) {

			sibling->keys[i - 1] = sibling->keys[i];

		}

		if (sibling->isLeaf == false) {

			for (int i = 1; i < sibling->numKeys; i++) {

				sibling->Children[i - 1] = sibling->Children[i];

			}

		}

		child->numKeys += 1;
		sibling->numKeys -= 1;

	}

	void merge(int index) {

		BTreeNode<T>* child = Children[index];
		BTreeNode<T>* sibling = Children[index + 1];

		child->keys[minDegree - 1] = keys[index];

		for (int i = 0; i < sibling->numKeys; i++) {

			child->keys[i + minDegree] = sibling->keys[i];

		}

		if (child->isLeaf == false) {

			for (int i = 0; i <= sibling->numKeys; i++) {

				child->Children[i + minDegree] = sibling->Children[i];

			}

		}

		for (int i = index + 2; i <= numKeys; i++) {

			Children[i - 1] = Children[i];

		}

		child->numKeys += sibling->numKeys + 1;
		numKeys--;

		delete(sibling);

	}

};

template<typename R>
class BTree {

	BTreeNode<R>* root;
	int minDegree;

public:

	BTree(int n)
	{

		root = NULL;
		minDegree = n;

	}

	void nameFiles(string s) {

		if (root != NULL) {

			root->nameFiles(s);

		}

	}

	void nameFiless(string s) {

		if (root != NULL) {

			root->nameFiless(s);

		}

	}

	void traverse() {

		if (root != NULL) {

			root->traverse();

		}

	}

	void traverse2(R num1, R num2) {

		if (root != NULL) {

			root->traverse2(num1, num2);

		}

	}


	BTreeNode<R>* search(R k) {

		if (root == NULL) {

			return NULL;

		}

		else {

			return root->search(k);

		}

	}

	void insert(R k) {

		if (root == NULL) {

			root = new BTreeNode<R>(minDegree, true);
			root->keys[0] = k;
			root->numKeys = 1;

		}

		else {

			if (root->numKeys == 2 * minDegree - 1) {

				BTreeNode<R>* s = new BTreeNode<R>(minDegree, false);

				s->Children[0] = root;

				s->splitChild(0, root);

				int i = 0;

				if (s->keys[0] < k) {

					i++;

				}

				s->Children[i]->insertWhenNotFull(k);

				root = s;

			}

			else {

				root->insertWhenNotFull(k);

			}

		}

	}

	void remove(R k) {

		if (root == NULL) {

			return;

		}

		root->remove(k);

		if (root->numKeys == 0) {

			BTreeNode<R>* temp = root;

			if (root->isLeaf == true) {

				root == NULL;

			}

			else {

				root = root->Children[0];

			}

			delete temp;

		}

	}

};