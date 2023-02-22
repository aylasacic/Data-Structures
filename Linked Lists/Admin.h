#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include "User.h"

// Intialization of the Admin Class
class Admin: public User{
public:
    // Empty constructor declaration
    Admin();
    
    // Admin constructor
    Admin(int ID, std::string first_name, std::string last_name, std::string username, std::string password);
    
    // Admin destructor
    ~Admin();
    
    // output method explained in Admin.cpp
    void output();
};

#endif
