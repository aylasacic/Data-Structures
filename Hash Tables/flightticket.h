#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
using namespace std;

class Flight_Ticket
{
	private:
		std::string companyName;
		int flightNumber;
		std::string country_of_origin;
		std::string country_of_destination;
		std::string stopOver;
		std::string price;
		std::string time_of_departure;
		std::string time_of_arrival;
		std::string date;

	public:
        Flight_Ticket();
		Flight_Ticket(std::string companyName, int flightNumber, std::string country_of_origin, std::string country_of_destination, 
			std::string stopOver, std::string price, std::string time_of_departure, std::string time_of_arrival, std::string date);
		~Flight_Ticket();
		std::string getCompanyName();
		int getFlightNumber();
		std::string getCoO();
		std::string getCoD();
		std::string getStopOver();
		std::string getPrice();
		std::string getToD();
		std::string getToA();
		std::string getDate();

        void setCompanyName(std::string newCompanyName);
        void setFlightNumber(int newFlightNumber);
        void setCoO(std::string newCoO);
        void setCoD(std::string newCoD);
        void setStopOver(std::string newStopOver);
        void setPrice(std::string newPrice);
        void setToD(std::string newToD);
        void setToA(std::string newToA);
        void setDate(std::string newDate);

        bool operator==(const Flight_Ticket& other) const;
        void displayRecord();
};

#endif
