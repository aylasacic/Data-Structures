#ifndef VECTOR_H
#define VECTOR_H
#include<iostream>
#include "contact.h"

// Vector used from Lab 7 of Data structures Section 3.
// All comments in this file were made by Professor Khalid Mengal

template<typename T> class MyVector;

template<typename T>
class MyVector
{
    private:
        T *data;                                // Pointer to int(array) to store elements
        int size;                               // Current size of vector (number of elements in vector)
        int capacity;                           // Capacity of vector
    public:
        MyVector();                             // No argument constructor
        MyVector(int cap);                      // One Argument Constructor
        ~MyVector();                            // Destructor
        void push_back(T element);              // Add an element at the end of vector
        void erase(int index);                  // Removes an element from the index
        int getSize() const;                    // Return current size of vector
        int getCapacity() const;                // Return capacity of vector
        bool empty() const;                     // Return true if the vector is empty, False otherwise
        T &at(int idx);
        void printData();
};

#endif

