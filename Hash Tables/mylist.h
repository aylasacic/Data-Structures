#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include<iostream>

#include "flightticket.h"

// Declaration of Node class and all MyList Methods
template<typename T> class MyList;

// NODE
template <typename T> class Node{
private:
    T data;
    Node<T>* next;
    Node<T>* prev;
    friend class MyList<T>;
    
public:
    Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr)
        :data(data), next(next), prev(prev){}
    Node():next(NULL), prev(NULL){} // Empty Node constructor for head and tail
    T& getData(){
        return data; // Return data stored in the node
    }
    Node<T> *getNext(){
        return next; // Return pointer to the next node
    }
    Node<T> *getPrev(){
        return prev; // Return pointer to the previous node
    }
};

// DOUBLY LINKED LIST
template <typename T> class MyList{
private:
    Node<T>* head;     // Pointer to the head of List
    Node<T>* tail;     // Pointer to the tail of List
    int elements;
public:
    // All methods of the Doubly Linked List
    MyList();
    ~MyList();
    bool empty() const;
    const T& front() const;
    void addBack(const T& data);
    void addFront(const T& data);
    void removeFront();
    void removeBack();
    void removeElement(T& data);
    Node<T> *getHead();
    Node<T> *getTail();
    int getElements();
    void bubbleSort();
};

#endif
