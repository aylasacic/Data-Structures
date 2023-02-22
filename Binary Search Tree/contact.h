#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
using namespace std;

class Contact
{
private:
    std::string fname;
    std::string lname;
    std::string email;
    std::string primaryPhone;
    std::string city;
    std::string country;
    bool isFav;

public:
    // Contructors and destructor for contact class
    Contact();
    Contact(std::string fname, std::string lname, std::string email, std::string primaryPhone, std::string city, std::string country, bool isFav);
    ~Contact();
    
    // setter and getter declarations
    std::string getFName();
    std::string getLName();
    std::string getEmail();
    std::string getPhone();
    std::string getCity();
    std::string getCountry();
    bool getIsFav();
    
    void setFName(std::string new_fname);
    void setLName(std::string new_lname);
    void setEmail(std::string new_email);
    void setPhone(std::string new_phone);
    void setCity(std::string new_city);
    void setCountry(std::string new_country);
    void setIsFav(bool new_fav);

    void printDetails();
};

#endif
