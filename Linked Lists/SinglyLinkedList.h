#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H
#include<iostream>

// Singly Linked List class used for Stack in FitnessClass

// NODE
class SingleNode{
private:
    int data;
    SingleNode* next;
        
public:
    SingleNode(int data): data(data), next(NULL)
    {}
    friend class SinglyLinkedList;
};

// SINGLY LINKED LSIT
class SinglyLinkedList{
private:
    SingleNode* head; // Pointer to the head of list
public:
    SinglyLinkedList (){
        this -> head = NULL;
    }
    
    // Destructor
    ~SinglyLinkedList (){
        while(!isEmpty())
            removeFromFront();
        head = NULL;
    }
    
    // Is the list empty?
    bool isEmpty() const{
        return head == NULL;
    }
    
    // Return front element of the list
    int& getFront(){
        return head -> data;
    }
    
    // Add element to the front of the list
    void addToFront(int elem){
        SingleNode* newNode = new SingleNode(elem);
        newNode -> next = head;
        head = newNode;
    }
    
    // Remove element from the front of the list
    void removeFromFront(){
        SingleNode *oldNode = head;
        head = head->next;
        delete oldNode;
    }
};

#endif
