#include<iostream>
#include<fstream>
#include <string>
#include "User.h" // Declaration and methods of User superclass that Member class inherits from
#include "Member.h" // Declaration of Member class

// Empty Member object used for head and tail of Doubly Linked List of Admins
Member::Member(){}

// Constructor of Member class
Member::Member(int ID, std::string first_name, std::string last_name, std::string username, std::string password)
: User(ID, first_name, last_name, username, password){}

// Destructor
Member::~Member(){}

// Method for outputting each Member object into the Admins.txt file after the program quits
void Member::output(){
    // opening Members.txt for appending data
    std::ofstream memberout("Members.txt", std::ios::app);
    
    memberout << getID() << "," << getName() << "," << getSurname() << "," << getUsername() << "," << getPassword() << std::endl;
    
    memberout.close();
}
