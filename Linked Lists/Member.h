#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include "User.h"

// Intialization of the Member Class
class Member: public User{
public:
    // Empty constructor declaration
    Member();
    
    // Member constructor
    Member(int ID, std::string first_name, std::string last_name, std::string username, std::string password);
    
    // Member destructor
    ~Member();
    
    // output method explained in Member.cpp
    void output();
};

#endif
