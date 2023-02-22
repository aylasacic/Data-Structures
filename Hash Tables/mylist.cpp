#include "mylist.h"
#include "flighthashtable.h"
#include "flightticket.h"

#include<iostream>
#include<fstream>

using namespace std;

// MyList constructor
template <typename T> MyList<T>::MyList(){
    // Head and tail node initialised and their next and prev pointers assigned;
    head = new Node<T>();
    tail = new Node<T>();
    head -> next = tail;
    tail -> prev = head;
    elements = 0;
}

// MyList deconstructor
template <typename T> MyList<T>::~MyList(){
    while(!empty())
        removeFront();
    
    delete head;
    delete tail;
}

// Is the list empty?
template <typename T> bool MyList<T>::empty() const{
    return head -> next == tail;
}

// Return first element of the list
template <typename T> const T& MyList<T>::front() const{
    return head -> next -> data;
}

// Add element to the back of the list
template <typename T> void MyList<T>::addBack(const T& data){
    Node<T> *new_node = new Node<T>(data);
    new_node -> next = tail;
    tail -> prev -> next = new_node;
    new_node -> prev = tail -> prev;
    tail -> prev = new_node;
    elements++;
}

// Add element to the front of the list
template <typename T> void MyList<T>::addFront(const T& data){
    Node<T> *new_node = new Node<T>(data);
    new_node -> next = head -> next;
    head -> next -> prev = new_node;
    head -> next = new_node;
    new_node -> prev = head;
}

// Remove element from the front of the list
template <typename T> void MyList<T>::removeFront(){
    if(empty()){
        return;
    }
    else{
        Node<T> *old_node = head -> next;
        head -> next -> next -> prev = head;
        head -> next = head -> next -> next;
        delete old_node;
        elements--; // Decreading the number of elements after deletion
    }
}

// Remove element from the back of the list
template <typename T> void MyList<T>::removeBack(){
    if(empty()){
        return;
    }
    else{
        Node<T> *old_node = tail -> prev;
        tail -> prev -> prev -> next = tail;
        tail -> prev = tail -> prev -> prev;
        delete old_node;
        elements--; // Decreading the number of elements after deletion
    }
}

// Remove element with certain ID that is provided by the Admin
template <typename T> void MyList<T>::removeElement(T& data){
    Node<T> *current = head -> next;
    while(current -> next != NULL ){
        if(current -> data.getValue() == data.getValue()){
            Node<T> *old_node = current;
            current = current -> next;
            current -> prev = old_node -> prev;
            old_node -> prev -> next = current;
            delete old_node; // Decreasing the number of elements after deletion
            elements--;
            cout << "You have successfully deleted the record!" << endl;
            break;
        }
        current = current -> next;
    }
}

// Return head of the list
template <typename T> Node<T>* MyList<T>::getHead(){return head;}

// Return tail of the list
template <typename T> Node<T>* MyList<T>::getTail(){return tail;}

// Return number of elements of the list
template <typename T> int MyList<T>::getElements(){return elements;}

// Bubble sort used for sorting instances based on the IDs before outputting to the file
template <typename T> void MyList<T>::bubbleSort(){
    Node<T> *current;
    T temp; // Temporary variable for storing data
    bool flag = true;
    while(flag == true){
        current = head -> next;
        flag = false; // Flag set to false each sort. If it stays false, no sorting happened, so the loop stops.
        while(current -> next -> next != NULL){
            if(current -> data.getValue().getCoD() > current -> next -> data.getValue().getCoD()){
                // Switch the data between the two nodes that are compared
                temp = current -> data;
                current -> data = current -> next -> data;
                current -> next -> data = temp;
                flag = true;
            }
            current = current -> next;
        }
    }
}

// Template classes for storing Hash_Node objects
template class MyList<HashNode>;
