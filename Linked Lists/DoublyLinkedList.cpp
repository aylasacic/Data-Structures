// Header files
#include "User.h"
#include "Admin.h"
#include "Member.h"
#include "FitnessClass.h"
#include "DoublyLinkedList.h"

#include<iostream>
#include<fstream>

using namespace std;

// DoublyLinkedList constructor
template <typename T> DoublyLinkedList<T>::DoublyLinkedList(){
    // Head and tail node initialised and their next and prev pointers assigned;
    head = new Node<T>();
    tail = new Node<T>();
    head -> next = tail;
    tail -> prev = head;
    elements = 0; // Number of elements in the list
    currentMember = head; // Current member used for certain Member functions when retreiving the ID
}

// DoublyLinkedList deconstructor
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList(){
    while(!empty())
        removeFront();
    
    delete head;
    delete tail;
}

// Is the list empty?
template <typename T> bool DoublyLinkedList<T>::empty() const{
    return head -> next == tail;
}

// Return first element of the list
template <typename T> const T& DoublyLinkedList<T>::front() const{
    return head -> next -> data;
}

// Add element to the back of the list
template <typename T> void DoublyLinkedList<T>::addBack(const T& data){
    Node<T> *new_node = new Node<T>(data);
    new_node -> next = tail;
    tail -> prev -> next = new_node;
    new_node -> prev = tail -> prev;
    tail -> prev = new_node;
    elements++;
}

// Add element to the front of the list
template <typename T> void DoublyLinkedList<T>::addFront(const T& data){
    Node<T> *new_node = new Node<T>(data);
    new_node -> next = head -> next;
    head -> next -> prev = new_node;
    head -> next = new_node;
    new_node -> prev = head;
}

// Remove element from the front of the list
template <typename T> void DoublyLinkedList<T>::removeFront(){
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
template <typename T> void DoublyLinkedList<T>::removeBack(){
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
template <typename T> void DoublyLinkedList<T>::removeElement(int ID){
    Node<T> *current = head -> next;
    while(current -> next != NULL){
        if(current -> data.getID() == ID){
            Node<T> *old_node = current;
            current = current -> next;
            current -> prev = old_node -> prev;
            old_node -> prev -> next = current;
            delete old_node; // Decreasing the number of elements after deletion
            elements--;
            break;
        }
        current = current -> next;
    }
}

// Return head of the list
template <typename T> Node<T>* DoublyLinkedList<T>::getHead(){return head;}

// Return tail of the list
template <typename T> Node<T>* DoublyLinkedList<T>::getTail(){return tail;}

// Return current member of the list
template <typename T> Node<T>* DoublyLinkedList<T>::getCurrentMember(){return currentMember;}

// Return number of elements of the list
template <typename T> int DoublyLinkedList<T>::getElements(){return elements;}

// Set the current user/member of the program
template <typename T> void DoublyLinkedList<T>::setCurrentMember(int ID){
    currentMember = head;
    Node<T> *current = head -> next;
    while(current -> next != NULL){
        if(current -> data.getID() == ID){
            currentMember = current;
        }
        current = current -> next;
    }
}

// Save data contained in each node. This method is used together with each output method of the three classes: Admin, Member and Fitness Class
template <typename T> void DoublyLinkedList<T>::saveData(string path){
    Node<T> *current = head -> next;
    
    ofstream fileout(path);
    fileout.close();
    
    while(current -> next != NULL){
        current -> data.output();
        current = current -> next;
    }
}

// Bubble sort used for sorting instances based on the IDs before outputting to the file
template <typename T> void DoublyLinkedList<T>::bubbleSort(){
    Node<T> *current;
    T temp; // Temporary variable for storing data
    bool flag = true;
    while(flag == true){
        current = head -> next;
        flag = false; // Flag set to false each sort. If it stays false, no sorting happened, so the loop stops.
        while(current -> next -> next != NULL){
            if(current -> data.getID() > current -> next -> data.getID()){
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

// Template classes for storing Admin, Member and FitnessClass objects
template class DoublyLinkedList<Admin>;
template class DoublyLinkedList<Member>;
template class DoublyLinkedList<FitnessClass>;
