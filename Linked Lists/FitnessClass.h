#ifndef FITNESSCLASS_H
#define FITNESSCLASS_H
#include "SinglyLinkedList.h"

// Stack declaration
class Stack {
private:
    int capacity;
    SinglyLinkedList *StackList;
    int top;
    int number_IDs;

public:
    Stack(int cap = 10); // Capacity is set to default 10
    
    ~Stack();

    void push(const int& e);

    void pop();

    const int& topElement();

    bool empty();

    bool full();

    int getNrIDs();
    
    void setCapacity(int cap);
    
    void setNrIDs(int nr_ids);
};


// Declaration of the FitnessClass Class
class FitnessClass{
private:
    int Class_ID;
    std::string Class_name;
    std::string Class_date;
    std::string Class_time;
    int Max_capacity;
    int Room_number;
    Stack *List_Members;
    
public:
    // Constructor
    FitnessClass();
    
    FitnessClass(int class_id, std::string class_name, std::string class_date, std::string class_time, int max_cap, int room_nr);
    // Destructor
    ~FitnessClass();
    
    // Getters and Setters
    int getID();

    std::string getName();

    std::string getDate();

    std::string getTime();

    int getMaxCap();

    int getRoomNr();
    
    Stack *getStack();
    
    void addMember(int ID);

    void deleteMember();

    void setID(int new_id);
    
    void setName(std::string new_name);
    
    void setDate(std::string new_date);
    
    void setTime(std::string new_time);
    
    void setCap(int new_cap);
    
    void setRoomNr(int new_nr);
    
    // Traversing the List_Members /  Stack methods

    bool searchMember(int member_id);

    void removeMember(int member_id);

    void print();
    
    void output();
};

#endif
