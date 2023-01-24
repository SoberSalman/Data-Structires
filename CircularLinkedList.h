#include<iostream>
using namespace std;
class node
{
public:
    int data = 0;
	node* next;


};

class CircularLinkedList
{
	node* head= NULL;
    node* tail = NULL;



public:

    CircularLinkedList(){}

    bool insert(int n)
    {
        node* temp = new node();
        temp->data = n;

        if (head == NULL)
        {
            tail = temp;
            head = temp;

            temp->next = temp;
            return true;

        }
        else
        {
            tail->next = temp;
            temp->next = head;
            tail = temp;
            return true;

        }
    
    }


    node* Deletenode(int key)
    {
       
        if (head == NULL)
            return head;


       
        if (head->data == key && head->next == head)
        {
            free(head);
            head = NULL;
            return head;
        }

        node* last = head, * d;

       
        if ((head)->data == key)
        {

           
            while (last->next != head)
                last = last->next;

           
            
            last->next = (head)->next;
            free(head);
            head = last->next;
            return head;
        }

      
        while (last->next != head && last->next->data != key)
        {
            last = last->next;
        }

      
        if (last->next->data == key)
        {
            d = last->next;
            last->next = d->next;
            free(d);
            return head;
        }
        else
            cout << "no such keyfound";
        return head;
    }

    void printList()
    {
        node* temp = new node();
        temp = head;

        // If linked list is not empty
        if (temp != NULL) {

            // Print nodes till we reach first node again
            do {
                cout << temp->data << " ";
                temp = temp->next;
            } while (temp != head);
        }
    }





};