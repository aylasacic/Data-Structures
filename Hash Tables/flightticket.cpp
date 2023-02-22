 // HEADER FILE INCLUDED
#include "flightticket.h"


Flight_Ticket::Flight_Ticket(){} // Empty constructor

// Constructor
Flight_Ticket::Flight_Ticket(std::string companyName, int flightNumber, std::string country_of_origin, std::string country_of_destination, 
			std::string stopOver, std::string price, std::string time_of_departure, std::string time_of_arrival, std::string date)
{
	this->companyName = companyName;
	this->flightNumber = flightNumber;
	this->country_of_origin = country_of_origin;
	this->country_of_destination = country_of_destination;
	this->stopOver = stopOver;
	this->price = price;
	this->time_of_departure = time_of_departure;
	this->time_of_arrival = time_of_arrival;
	this->date = date;
}

// Destructor
Flight_Ticket::~Flight_Ticket(){}

//=====================================================================================
// SETTERS AND GETTERS

std::string Flight_Ticket::getCompanyName(){return this->companyName;}
int Flight_Ticket::getFlightNumber(){return this->flightNumber;}
std::string Flight_Ticket::getCoO(){return this->country_of_origin;}
std::string Flight_Ticket::getCoD(){return this->country_of_destination;}
std::string Flight_Ticket::getStopOver(){return this->stopOver;}
std::string Flight_Ticket::getPrice(){return this->price;}
std::string Flight_Ticket::getToD(){return this->time_of_departure;}
std::string Flight_Ticket::getToA(){return this->time_of_arrival;}
std::string Flight_Ticket::getDate(){return this->date;}

void Flight_Ticket::setCompanyName(std::string new_CompanyName){this->companyName = new_CompanyName;}
void Flight_Ticket::setFlightNumber(int newFlightNumber){this->flightNumber = newFlightNumber;}
void Flight_Ticket::setCoO(std::string newCoO){this->country_of_origin = newCoO;}
void Flight_Ticket::setCoD(std::string newCoD){this->country_of_destination = newCoD;}
void Flight_Ticket::setStopOver(std::string newStopOver){this->stopOver = newStopOver;}
void Flight_Ticket::setPrice(std::string newPrice){this->price = newPrice;}
void Flight_Ticket::setToD(std::string newToD){this->time_of_departure = newToD;}
void Flight_Ticket::setToA(std::string newToA){this->time_of_arrival = newToA;}
void Flight_Ticket::setDate(std::string newDate){this->date = newDate;}

//=====================================================================================

// Method to overload == operator for comparing data from two flight tickets
bool Flight_Ticket::operator==(const Flight_Ticket& other) const{
	if(this->country_of_origin == other.country_of_origin &&
		this->country_of_destination == other.country_of_destination &&
		this->stopOver == other.stopOver &&
		this->price == other.price &&
		this->time_of_arrival == other.time_of_arrival &&
		this->time_of_departure == other.time_of_departure &&
		this->date == other.date){
		return true;
	}
	return false;
}

// Method to display a flight ticket
void Flight_Ticket::displayRecord(){
	cout << companyName << "," << flightNumber << ","
		 << country_of_origin << "," << country_of_destination 
		 << "," << stopOver << "," << price << "," << time_of_departure 
		 << "," << time_of_arrival << "," << date << endl;
}
