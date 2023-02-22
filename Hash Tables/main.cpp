
//=====================================================================================
// Name         : DS Assignment#4 
// Author       : Ajla Šačić
// Version      : 1.0
// Date Created : 16-04-2022
// Date Modified: 07-05-2022
// Description  : Main.cpp for Contact Travel Management System using HASH TABLE in C++
//=====================================================================================

#include<iostream>
#include<cstdlib>
#include<sstream>

//=====================================================================================

#include "flightticket.h"
#include "flighthashtable.h"
#include "mylist.h"

//=====================================================================================
void listCommands(){
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print Number of Collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//=====================================================================================

int main(void)
{
	string input;
	string command;
	string key;
	string num;
	listCommands();

	FlightHASHTABLE myFlightHASHTABLE;

	while(true){

		cout<<">";

		// Parse user input into variables to use later

		getline(cin, input);
		stringstream sstr(input);
		getline(sstr, command, ' ');
		getline(sstr, key, ',');
		getline(sstr, num); // Used for flightNr when entered with the key

		transform(key.begin(), key.end(), key.begin(), ::tolower);

		try{
			if(command == "import"){
				cout << myFlightHASHTABLE.importCSV(key) << endl;

			}
			else if(command == "export"){
				cout << myFlightHASHTABLE.exportCSV(key) << endl;
			}
			else if(command == "count_collisions"){
				cout << "Total number of collisions: " << myFlightHASHTABLE.count_collisions() << endl;
			}
			else if(command == "add"){
				// variables used for storing contact details
				string companyName, flightNrStr, CoD, CoA, stopOver, price, ToD, ToA, date; int flightNr;
				cout << "Please enter the details of the flight-ticket: " << endl;
				cout << "Company Name: "; getline(cin, companyName);
				cout << "Flight Number: "; cin >> flightNrStr; flightNr = stoi(flightNrStr); cin.ignore();
				cout << "Country of Departure: "; getline(cin, CoD);
				cout << "Country of Arrival: "; getline(cin, CoA);
				cout << "How many stops?: "; cin >> stopOver; cin.ignore();
				cout << "Price: "; cin >> price; cin.ignore();
				cout << "Time of Departure: "; cin >> ToD; cin.ignore();
				cout << "Time of Arrival: "; cin >> ToA; cin.ignore();
				cout << "Date: "; cin >> date; 

				// new contact object is created
				Flight_Ticket *ticket = new Flight_Ticket(companyName, flightNr, CoD, CoA, stopOver, price, ToD, ToA, date);

	            // ticked is added into the hach table
				cout << myFlightHASHTABLE.add(ticket) << endl; 

				cin.clear(); cin.ignore();
			}
			else if(command == "delete"){
				myFlightHASHTABLE.removeRecord(key, stoi(num));
				cin.clear(); cin.ignore();
			}
			else if(command == "find"){
				myFlightHASHTABLE.find(key, stoi(num));
			}
			else if(command == "allinday"){
				myFlightHASHTABLE.allinday(key);
			}
			else if(command == "printASC"){
				myFlightHASHTABLE.printASC(key, stoi(num));
			}
			else if(command == "exit"){
				exit(0);
			}
			else if(command == "help"){
				listCommands();
			}
			else{
				cout << "Invalid option!" << endl;
			}
		}
		catch(exception &e){
			cout << "Exception: " << e.what() << endl;
		}
	}
	return 0;
}
