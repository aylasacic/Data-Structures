#ifndef USER_H
#define USER_H
#include <string>

// User class declaration and methods
class User{
private:
    int ID;
    std::string First_name;
    std::string Last_name;
    std::string Username;
    std::string Password;

public:
    // Empty User Constructor
    User(){};
    
    // Constructor for User
    User(int ID, std::string first_name, std::string last_name, std::string username, std::string password)
    :ID(ID), First_name(first_name), Last_name(last_name), Username(username), Password(password)
    {}
    
    // Destructor
    ~User(){};

    // Getter functions
    virtual int getID(){return ID;}
    
    virtual std::string getName(){return First_name;}
    
    virtual std::string getSurname(){return Last_name;}

    virtual std::string getUsername(){return Username;}

    virtual std::string getPassword(){return Password;}
};

#endif
