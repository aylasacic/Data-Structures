#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>

#include "flightticket.h"
#include "mylist.h"

using namespace std;

class HashNode
{
	private:
		string key; // key = companyName+flightNumber
		Flight_Ticket value;
	public:
		HashNode(){};
		HashNode(std::string key, Flight_Ticket value)
		{
			this->key = key; // Key of hash table, it does not have to be unique for each record
			this->value = value; // Holds Flight_ticket data
		}
		Flight_Ticket &getValue(){
			return value;
		}
		~HashNode(){}

		friend class FlightHASHTABLE;
};


//=============================================================================
class FlightHASHTABLE
{
	private:
		MyList<HashNode> *buckets;		// List of buckets to hold HashNode
		int size;					    // Current size of HashTable
		int capacity;				    // Total capacity of HashTable
		int collisons;					// Total number of collisions in the table
		// add more attributes needed
	public:
		FlightHASHTABLE();						// Constructors
		FlightHASHTABLE(int capacity);
		~FlightHASHTABLE();						// Destructor
		int getSize();
		long hashCode(std::string key); 				
		int importCSV(std::string path); 		// Import data 
		int exportCSV(std::string path); 		// Export data
		int count_collisions();					// Number of collisions in the table
		int add(Flight_Ticket* data);			// Add new flight record
		void removeRecord (string companyName, int flightNumber);	// Delete a record 
		void find(string companyName, int flightNumber);			// Find and display flights with same key 
		void allinday(std::string date);  							// Find and display flights flying on the same day (entered by used)
		void printASC(std::string companyName, int flightNumber);  	// Display all flight-tickets having the same key entered by the user 

			
};

#endif
