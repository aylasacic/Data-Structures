// Header files
#include "SinglyLinkedList.h"
#include "FitnessClass.h"

#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>

using namespace std;

#define MAX_ARRAY 30 // Array for destacking
#define width 14

// Stack used for stroing members of the Fitness Class
Stack::Stack(int cap){
    capacity = cap; // Capacity of the stack
    StackList = new SinglyLinkedList(); // Singly linked list used as a method of storing the Member IDs
    number_IDs = 0; // Number of IDs in the stack
}

// Destructor
Stack::~Stack(){
    delete StackList;
}

// Push ID onto the stack
void Stack::push(const int& ID){
    if(!full()){
        StackList->addToFront(ID);
        number_IDs++;
    }
}

// Pop ID from the top of the stack
void Stack::pop(){
    if(!empty()){
        StackList->removeFromFront();
        number_IDs--;
    }
}

// Return the element at the top of the stack
const int& Stack::topElement(){
    return StackList->getFront();
}

// Is the stack empty?
bool Stack::empty(){return StackList->isEmpty();}

// Is the stack full? It is full if the number of ID is the same as the capacity of the stack
bool Stack::full(){return number_IDs == capacity;}

// Return number of IDs on the stack
int Stack::getNrIDs(){return number_IDs;}

// Set capacity of the stack
void Stack::setCapacity(int cap){capacity = cap;}

// Set the number of IDs
void Stack::setNrIDs(int nr_ids){number_IDs = nr_ids;}


// FITNESS CLASS
// Empty constructor for head and tail of Doubly Linked List of Fitness Classes
FitnessClass::FitnessClass(){}

// FitnessClass constructor
FitnessClass::FitnessClass(int class_id, std::string class_name, std::string class_date, std::string class_time, int max_cap, int room_nr)
:Class_ID(class_id),Class_name(class_name), Class_date(class_date), Class_time(class_time), Max_capacity(max_cap), Room_number(room_nr)
{List_Members = new Stack(Max_capacity);}

// Destructor
FitnessClass::~FitnessClass(){}

// Getters and Setters
int FitnessClass::getID(){return Class_ID;}

std::string FitnessClass::getName(){return Class_name;}

std::string FitnessClass::getDate(){return Class_date;}

std::string FitnessClass::getTime(){return Class_time;}

int FitnessClass::getMaxCap(){return Max_capacity;}

int FitnessClass::getRoomNr(){return Room_number;}

Stack* FitnessClass::getStack(){return List_Members;}

void FitnessClass::addMember(int ID){List_Members->push(ID);}

void FitnessClass::deleteMember(){List_Members->pop();}

void FitnessClass::setID(int new_id){
    Class_ID = new_id;
}
void FitnessClass::setName(std::string new_name){
    Class_name = new_name;
}
void FitnessClass::setDate(std::string new_date){
    Class_date = new_date;
}
void FitnessClass::setTime(std::string new_time){
    Class_time = new_time;
}
void FitnessClass::setCap(int new_cap){
    Max_capacity = new_cap;
    List_Members->setCapacity(new_cap);
}
void FitnessClass::setRoomNr(int new_nr){
    Room_number = new_nr;
}

// Searching for a member in the Stack
bool FitnessClass::searchMember(int member_id){
    int array[MAX_ARRAY]={0}; int temp, j; int i = 0; int flag = false;
    int left = 0;
    int right = sizeof(array)/sizeof(array[0])-1;
    
    // Popping IDs from the stack into an array until it is empty
    int start = List_Members->getNrIDs(); // Number of IDs present in stack before emptying
    while(List_Members->empty()!=true){
        array[i]=List_Members->topElement();
        if(array[i]==member_id){
            flag = true; // If the member is found, flag is set to true
        }
        List_Members->pop();
        i++;
    }

    // reversing the array so that the members can be returned in proper order
    while (left < right){
        // Switching between left and right ID in the array
        temp = array[left];
        array[left] = array[right];
        array[right] = temp;
        left++; right--;
    }

    // Pushing the IDs back into the stack in proper order
    for(int j = MAX_ARRAY-start; j<MAX_ARRAY; j++){
        List_Members->push(array[j]);
    }
    return flag; // True if member is found, false if it is not
}

// Method from removing the member from the Stack
void FitnessClass::removeMember(int member_id){
    int array[MAX_ARRAY] = {0}; int temp, j; int i = 0;
    int left = 0;
    int right = MAX_ARRAY-1;
    int start = List_Members->getNrIDs();
    
    // Popping from the stack
    while(List_Members->empty() != true){
        // If the member is found, just pop, do not place into array
        if(List_Members->topElement() == member_id){
            List_Members->pop();
        }
        // If the member is not found, place ID into array
        else{
            array[i] = List_Members->topElement();
            List_Members->pop();
            i++;
        }
    }

    // Reverse the array so that the members are pushed back properly
    while (left < right){
        temp = array[left];
        array[left] = array[right];
        array[right] = temp;
        left++; right--;
    }

    // Push IDs back into the Stack
    for(int j = MAX_ARRAY - start + 1; j < MAX_ARRAY; j++){
        List_Members->push(array[j]);
    }
}

// Method for printing out the Fitness Classes (used in viewing vacant and booked classes in main)
void FitnessClass::print(){
    cout << "\e[1mClass ID" << " " << setw(width) << "Class Name" << " " << setw(width) << "Class Date" << " " << setw(width) << "Class Time" << " " << setw(width) << "Class Room" << "\e[0m" << endl;
        cout << right << setw(8) << Class_ID <<
                setw(width+1) << Class_name <<
                setw(width+1) << Class_date <<
                setw(width+1) << Class_time <<
                setw(width+1) << Room_number << endl;
}

// Output Method for FitnessClass
void FitnessClass::output(){
    ofstream fitnessout("FitnessClasses.txt", ios::app);
    std::string members = "["; // Members of the fitness class / stack, starts with "["
    int id;
    
    // If the class is empty, add empty space to the members
    if(List_Members->empty()){
        members += " ";
    }
    
    // Add IDs to the members by popping them from the stack
    while(List_Members->empty() != true){
        id = List_Members->topElement();
        // If the number of IDs is one, a comma should not be added at the end
        if(List_Members->getNrIDs() == 1){
            members += to_string(id);
            List_Members->pop();
            break;
        }
        List_Members->pop();
        members += to_string(id) + ","; // Add comma after each ID
    }
    members += "]"; // Add closing bracked to the end of members
    fitnessout << Class_ID << "," << Class_name << "," << Class_date << "," << Class_time << "," << Max_capacity << "," << Room_number << "," << members << endl;
    
    fitnessout.close();
}
