#include<iostream>
#include<fstream>

#include "Admin.h" // Declaration of Admin class
#include "User.h" // Declaration and methods of User superclass that Admin class inherits from

// Empty Admin object used for head and tail of Doubly Linked List of Admins
Admin::Admin(){}

// Constructor of Admin class
Admin::Admin(int ID, std::string first_name, std::string last_name, std::string username, std::string password)
:User(ID, first_name, last_name, username, password)
{}

// Destructor
Admin::~Admin(){}

// Method for outputting each Admin object into the Admins.txt file after the program quits
void Admin::output(){
    // opening Admins.txt for appending data
    std::ofstream adminout("Admins.txt", std::ios::app);
    
    adminout << getID() << "," << getName() << "," << getSurname() << "," << getUsername() << "," << getPassword() << std::endl;
    
    adminout.close();
}


