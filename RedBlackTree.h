#include <iostream>
#include"LinkedList.h"
using namespace std;


template <typename R>
struct RBTNode
{
    R data;
    Linkedlist FileName;
    string Location;
    RBTNode* parent;
    RBTNode* left;
    RBTNode* right;
    int color;
};



template <typename T>

class RBT
{

    RBTNode<T>* root;
    RBTNode<T>* Nil;




    // Preorder
    void preOrderHelper(RBTNode<T>* temp)
    {
        if (temp == NULL)
        {
            return;
        }
        ofstream fout(temp->Location, ios::app);

        if (temp->left != NULL)
            fout << temp->left->Location << "\n";
        else
            fout << "NULL" << "\n";
        if (temp->right != NULL)
            fout << temp->right->Location << "\n";
        else
            fout << "NULL" << "\n";


        LNode* newnode = temp->FileName.gethead();

        for (int i = 0; i < temp->FileName.size; i++)
        {
            //cout << newnode->getdata() << endl;
            fout << newnode->getdata() << "\n";
            newnode = newnode->getnode();
        }








        //printnode(temp->left);

        fout.close();
        preOrderHelper(temp->left);
        preOrderHelper(temp->right);
    }

    // Inorder
    void inOrderHelper(RBTNode<T>* node)
    {
        if (node != Nil) {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    // Post order
    void postOrderHelper(RBTNode<T>* node) {
        if (node != Nil) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }


    RBTNode<T>* searchTreeHelper(RBTNode<T>* node, T key, string filename, string location)
    {
        if (node == Nil || key == node->data)
        {
            node->Location = location;
            node->FileName.insert(filename);
            return node;
        }

        if (key < node->data)
        {

            return searchTreeHelper(node->left, key, filename, location);
        }
        return searchTreeHelper(node->right, key, filename, location);
    }

    // For balancing the tree after deletion
    void deleteFix(RBTNode<T>* x)
    {
        RBTNode<T>* s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(RBTNode<T>* u, RBTNode<T>* v)
    {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(RBTNode<T>* node, int key) {
        RBTNode<T>* z = Nil;
        RBTNode<T>* x, y;
        while (node != Nil) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == Nil) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == Nil) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == Nil) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            deleteFix(x);
        }
    }

    // For balancing the tree after insertion
    void insertFix(RBTNode<T>* k)
    {
        RBTNode<T>* u;
        while (k->parent->color == 1)
        {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }



public:
    RBT()
    {
        Nil = new RBTNode<T>;
        Nil->color = 0;
        Nil->left = nullptr;
        Nil->right = nullptr;
        root = Nil;
    }

    void preorder() {
        preOrderHelper(this->root);
    }

    void inorder() {
        inOrderHelper(this->root);
    }

    void postorder() {
        postOrderHelper(this->root);
    }

    RBTNode<T>* searchTree(T k, string filename, string location)
    {
        return searchTreeHelper(this->root, k, filename, location);
    }

    RBTNode<T> minimum(RBTNode<T> node)
    {
        while (node->left != Nil) {
            node = node->left;
        }
        return node;
    }

    RBTNode<T> maximum(RBTNode<T> node) {
        while (node->right != Nil) {
            node = node->right;
        }
        return node;
    }

   

    void leftRotate(RBTNode<T>* x)
    {
        RBTNode<T>* y = x->right;
        x->right = y->left;
        if (y->left != Nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBTNode<T>* x) {
        RBTNode<T>* y = x->left;
        x->left = y->right;
        if (y->right != Nil) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(T key, string filename, string location)
    {
        RBTNode<T>* node = new RBTNode<T>();
        node->parent = nullptr;
        node->data = key;
        node->left = Nil;
        node->right = Nil;
        node->color = 1;
        node->FileName.insert(filename);
        node->Location = location;

        RBTNode<T>* y = nullptr;
        RBTNode<T>* x = this->root;

        while (x != Nil) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->data < y->data) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    RBTNode<T>* getRoot()
    {
        return this->root;
    }

    void deleteNode(int data)
    {
        deleteNodeHelper(this->root, data);
    }

    void printTree()

    {
        if (root)
        {
            printHelper(this->root, "", true);
        }
    }



    RBTNode<T>* Find(RBTNode<T>* node, T key)
    {
        if (node == Nil || key == node->data)
        {
            return node;
        }

        if (key < node->data)
        {

            return Find(node->left, key);
        }


        return Find(node->right, key);

    }
};