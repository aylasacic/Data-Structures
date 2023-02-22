#include "myvector.h"
#include "contact.h"
#include<iostream>

using namespace std;

// Two constructors for the vector class
template <typename T> MyVector<T>::MyVector(){
    size = 0;
    capacity = 1;
    data = new T[1]; // creates an array of size 1
}

template <typename T> MyVector<T>::MyVector(int cap){
    size = 0;
    capacity = cap;
    data = new T[cap];
}

template <typename T> MyVector<T>::~MyVector(){
    delete [] data;
}

template <typename T> void MyVector<T>:: push_back(T element){
    // If there is no space, reserve space for the insert
    if(capacity == size){
        T *new_data = data;
        data = new T[2 * capacity];
        for(int i = 0; i < capacity; i++){
            data[i] = new_data[i];
        }

        // delete the data from before
        delete [] new_data;
        
        // increase capacity by 2
        capacity = 2 * capacity;
    }
    
    // add element at the first available index, i.e. end of vector
    data[size++] = element;
}

template <typename T> void MyVector<T>::erase(int index){
    if(index < 0 || index > size){
        // if index is out of range, throw exception
        throw out_of_range("Index out of range!");
    }
    
    // Create new array to store the data after deleting the element at desired index
    T *prev_data = data;
    data = new T[capacity];
    for(int i = index; i < size; i++){
        prev_data[i] = prev_data[i + 1]; // Move the deleted element to the far right (zero)
    }
    
    for(int j = 0; j < size - 1; j++){
        data[j] = prev_data[j]; // Move all data to new array so that no 0 (zeros) can be seen after deletion
    }
    size--;
    
    // delete previous data
    delete [] prev_data;
}

// method for returning the size of the array
template <typename T> int MyVector<T>::getSize() const{
    return size;
}

// method for returning the capacity of the array
template <typename T> int MyVector<T>::getCapacity() const{
    if(empty()){
        return 0;
    }
    return capacity;
}

// Method for checking whether the array is empty
template <typename T> bool MyVector<T>::empty() const{
    return size == 0;
}

// Method for returning the value at the desired index of the array
template <typename T> T& MyVector<T>::at(int idx){
    return data[idx];
}

// Method for printing the data within array, used in the ContactBST methods
template <typename T> void MyVector<T>::printData(){
    for(int i = 0; i < size; i++){
        cout << i + 1 << ". " << data[i].getFName() << " " << data[i].getLName()
             << ", " << data[i].getEmail() << ", " << data[i].getPhone() << ", " 
             << data[i].getCity() << ", " << data[i].getCountry() << endl;
    }
}

template class MyVector<Contact>;
