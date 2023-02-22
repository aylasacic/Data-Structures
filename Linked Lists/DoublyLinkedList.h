#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include<iostream>

// Declaration of Node class and all Doubly Linked List Methods
template<typename T> class DoublyLinkedList;

// NODE
template <typename T> class Node{
private:
    T data;
    Node<T>* next;
    Node<T>* prev;
    template <typename U> friend class DoublyLinkedList;
    
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
template <typename T> class DoublyLinkedList{
private:
    Node<T>* head;     // Pointer to the head of List
    Node<T>* tail;     // Pointer to the tail of List
    Node<T>* currentMember; // Pointer to the current member
    int elements;
public:
    // All methods of the Doubly Linked List
    DoublyLinkedList();
    ~DoublyLinkedList();
    bool empty() const;
    const T& front() const;
    void addBack(const T& data);
    void addFront(const T& data);
    void removeFront();
    void removeBack();
    void removeElement(int ID);
    Node<T> *getHead();
    Node<T> *getTail();
    Node<T> *getCurrentMember();
    int getElements();
    void setCurrentMember(int ID);
    void saveData(std::string path);
    void bubbleSort();
};

#endif
