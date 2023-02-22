#include "contact.h"

Contact::Contact(){}

Contact::Contact(std::string fname, std::string lname, std::string email, std::string primaryPhone, std::string city, std::string country, bool isFav): 
				fname(fname), lname(lname), email(email),primaryPhone(primaryPhone), city(city), country(country), isFav(isFav){}

Contact::~Contact(){}


// Setter and getter methods
std::string Contact::getFName(){return fname;}
std::string Contact::getLName(){return lname;}
std::string Contact::getEmail(){return email;}
std::string Contact::getPhone(){return primaryPhone;}
std::string Contact::getCity(){return city;}
std::string Contact::getCountry(){return country;}
bool Contact::getIsFav(){return isFav;}

void Contact::setFName(std::string new_fname){fname = new_fname;}
void Contact::setLName(std::string new_lname){lname = new_lname;}
void Contact::setEmail(std::string new_email){email = new_email;}
void Contact::setPhone(std::string new_phone){primaryPhone = new_phone;}
void Contact::setCity(std::string new_city){city = new_city;}
void Contact::setCountry(std::string new_country){country = new_country;}
void Contact::setIsFav(bool new_fav){isFav = new_fav;}

// method for printing the details of contact object, used in ContactBST methods
void Contact::printDetails(){
	std::cout << fname << " " << lname << ", " << email << ", " 
		 << primaryPhone << ", " << city << ", " << country << std::endl;
}