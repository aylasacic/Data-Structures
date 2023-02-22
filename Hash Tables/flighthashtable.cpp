//=====================================================================================
// HEADER FILES

#include "flighthashtable.h"
#include "flightticket.h"

//=====================================================================================
// LIBRARIES

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<chrono>
#include<ctime>
#include<cmath>

//=====================================================================================
// METHOD DECLERATIONS

// Constructor for Hash Table with no parameters
FlightHASHTABLE::FlightHASHTABLE(){
    // Capacity set to 20k, but can be lowered because increasing does not change size by a lot
    buckets = new MyList<HashNode>[20000]; 
    // How many filled spaces in the array of MyList
    this->size = 0;
    this->capacity = 20000;
    // Number of collisons -> counts number of collisions before a node comes to an empty spot
    this->collisons = 0;
}

// Constructor for Hash Table with parameters
FlightHASHTABLE::FlightHASHTABLE(int capacity){
    buckets = new MyList<HashNode>[capacity];
    this->size = 0;
    this->capacity = capacity;
    this->collisons = 0;
}

// Destructor for Hash Table
FlightHASHTABLE::~FlightHASHTABLE(){}

// Return size of the hash table
int FlightHASHTABLE::getSize(){
    return size;
}

// Hash Code function for hashing a key <companyName,flightNumber>
long FlightHASHTABLE::hashCode(string key){

    // Hash Function #1

    // unsigned int h = 0;
    //   for (int i = 0; i < key.length(); i++){
    //       h = (h << 5)|(h >> 27);
    //     h += (unsigned int)key[i];}
    // return h % capacity;

    // Hash Function #2

    // unsigned int h = 0;
    // for(int i = 0; i < key.length(); i++)
    // {
    //     h = h + (unsigned int)key[i];
    // }
    // return h % capacity;

    // Hash Function #3

    unsigned int h = 0;
    for(int i = 0; i < key.length();  i++){
        h = 8191 * h + (unsigned int)key[i]; // 8191 is a famous Mersenne prime found in 15th century
    }

    h = h % capacity; // Divide by capacity to get a hash within the bounds of the capacity of the table

    return h;
}

int FlightHASHTABLE::importCSV(string path){

    ifstream filein(path);

    // variables used for storing the data imported
    string companyName, country_of_origin, country_of_destination, stopOver, price, 
    time_of_departure, time_of_arrival, date, flightNumberStr; int flightNumber;
    int count = 0; // counter for number of records imported
    // if file is opened, i.e. it exists, proceed
    if(filein.is_open()){
        string line;
        getline(filein, line);
        // while there is lines to get
        while(getline(filein, line)){
            // store line in line variable
            stringstream ss(line);
            // using, as a delimiter, store data from each cell
            // as there is an empty space after each delimiter, store it in space variable
            // to ensure data does not have an empty space beforehand
            getline(ss, companyName, ',');
            getline(ss, flightNumberStr, ','); flightNumber = stoi(flightNumberStr);
            getline(ss, country_of_origin, ',');
            getline(ss, country_of_destination, ',');
            getline(ss, stopOver, ',');
            getline(ss, price, ',');
            getline(ss, time_of_departure, ',');
            getline(ss, time_of_arrival, ',');
            getline(ss, date, ',');

            transform(companyName.begin(), companyName.end(), companyName.begin(), ::tolower);
            transform(country_of_origin.begin(), country_of_origin.end(), country_of_origin.begin(), ::tolower);
            transform(country_of_destination.begin(), country_of_destination.end(), country_of_destination.begin(), ::tolower);
            transform(date.begin(), date.end(), date.begin(), ::tolower);

            // create a new contact object with data from csv file
            Flight_Ticket *ticket = new Flight_Ticket(companyName, flightNumber, country_of_origin, 
                country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);

            // increase the count of records
            count++;

            // insert the new record using the add method
            add(ticket);   
        } 
    }
    else{
        // if file is not opened, return -1
        return (-1);
    }
    return count;
}

int FlightHASHTABLE::exportCSV(string path){
ofstream fileout(path, ios::app);
    int count = 0;
    // If csv file is not corrupt
    if(fileout.good()){
        // Fill in the header
        fileout << "companyName" << ", " << "flightNumber" << ", " << "country-of-origin"
                    << ", " << "country-of-destination" << ", " << "stopover"
                    << ", " << "price"<< ", " << "time-of-departure"
                    << ", " << "time-of-arrival" << ", " << "date" << endl;
        // Export each node to the file from the hash table, using "," delimiter
        for(int i = 0; i < capacity; i++){
            if(!(buckets[i].empty())){
                // Create node pointer to go over the list
                Node<HashNode> *current = buckets[i].getHead()->getNext();
                while(current->getNext() != NULL){
                    fileout << current -> getData().getValue().getCompanyName() 
                            << ", " << current -> getData().getValue().getFlightNumber()
                            << ", " << current -> getData().getValue().getCoO()
                            << ", " << current -> getData().getValue().getCoD()
                            << ", " << current -> getData().getValue().getStopOver()
                            << ", " << current -> getData().getValue().getPrice()
                            << ", " << current -> getData().getValue().getToD()
                            << ", " << current -> getData().getValue().getToA()
                            << ", " << current -> getData().getValue().getDate() << endl;
                    count++;
                    current = current -> getNext();
                }
            }   
        }
        return count;
    }
    // If file failed to open, return -1
    return (-1);
}   

// Return number of collisions
int FlightHASHTABLE::count_collisions(){return collisons;}

int FlightHASHTABLE::add(Flight_Ticket* data)
{
    // Create a key from the company name and flight number extracted from the data
    std::string key = data -> getCompanyName() + to_string(data -> getFlightNumber());

    // Create a new node to store the key and value
    HashNode *new_node = new HashNode(key, *data);
    unsigned int idx = hashCode(key); // Send the key into the hash function to retrieve an index for the 
                                      // placement of the node in the table
    
    Node<HashNode> *current = buckets[idx].getHead(); // Retreive head of the linked list 

    // Go over the linked list. If there is an identical record, display warning!
    while(current -> getNext() != NULL){
        if(current -> getData().getValue() == *data){
            cout << "Record already exists!" << endl;
            return -1;
        }
        current = current -> getNext();
    }

    // If the bucket is empty, just increase the size of the table, but no collisions
    if(!(buckets[idx].empty())){
        // Counting collisions:
        // Method 1: The lenght of the non-empty linked list before adding the node
        collisons += buckets[idx].getElements();
        // Method 2: If it is not empty, just add one collisions to the total, otherwise no collisions
        // collisons += 1;
    }
    else{
        size++;
    }

    // Add the record to the back of the linked list
    buckets[idx].addBack(*new_node);
    // cout << "Flight Ticket has been successfully added!" << endl; // Prints many lines if data is imported
    return 1;
}

// Remove record method
void FlightHASHTABLE::removeRecord(string companyName, int flightNumber){
    // Create a key from the company name and flight number extracted from the data
    std::string key = companyName + to_string(flightNumber);
    unsigned int idx = hashCode(key); // Retreive the index through the hash function

    Node<HashNode> *current = buckets[idx].getHead()->getNext(); // Get first element of the linked list at index

    Node<HashNode> *array = new Node<HashNode>[buckets[idx].getElements()]; // Create and array to hold the Nodes

    string choice; int i = 0; // i is a counter

    // Iterate over the linked list and if the data, companyName and flightNumber matches, add it to the array;
    while(current -> getNext() != NULL){
        if(current -> getData().getValue().getCompanyName() == companyName &&
            current -> getData().getValue().getFlightNumber() == flightNumber){ 
            array[i] = current -> getData();
            i++;
        } 
        current = current -> getNext();  
    }

    // If i is 0, no records were found
    if(i == 0){
        cout << "Not Found!" << endl;
        return; // Exit the function
    }

    // Otherwise, dispaly the number of records and the records themselves
    cout << i << " records found: " << endl;

    for(int j = 0; j < i; j++){
        cout << j+1 << ". "; array[j].getData().getValue().displayRecord();
    }

    // User inputs the record to be deleted
    cout << "Please select the record you want to delete: "; cin >> choice;

    // The record at the index is stored in variavle deleted_node
    Node<HashNode> deleted_node = array[stoi(choice)-1];

    // The data is sent into removeElement method od linked list
    // The node will be deleted when the data is identical to the one stored in the deleted_node
    buckets[idx].removeElement(deleted_node.getData()); 

    // Dynammic array is deleted
    delete [] array; 
}

// Find method
void FlightHASHTABLE::find(string companyName, int flightNumber){
    // Two variables for measuring the time from chrono library are intialised
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now(); // Time starts

    std::string key = companyName + to_string(flightNumber);
    unsigned int idx = hashCode(key);

    Node<HashNode> *current = buckets[idx].getHead();

    int i = 1; int count = 0; // count counts the number of elements mathing the criteria

    // Iterate over the linked list and if the data, companyName and flightNumber matches, add it to the array;
    while(current -> getNext() != NULL){
        if(current -> getData().getValue().getCompanyName() == companyName &&
            current -> getData().getValue().getFlightNumber() == flightNumber){
            count++;
        }
        current = current -> getNext();
    }

    // If i is 0, no records were found
    if(count == 0){
        cout << "Not Found!" << endl;
        return;
    }

    // Otherwise, current is sent back to the start of the list, and the number of found records displayed
    current = buckets[idx].getHead();

    cout << count << " records found: " << endl;

    current = buckets[idx].getHead(); // Back to the beginning of the list

    while(current -> getNext() != NULL){
        if(current -> getData().getValue().getCompanyName() == companyName &&
            current -> getData().getValue().getFlightNumber() == flightNumber){
            cout << i << ". " << endl;
                cout << "   Company Name: " << current -> getData().getValue().getCompanyName() << endl;
                cout << "   Flight Number: " << current -> getData().getValue().getFlightNumber() << endl;
                cout << "   Country of Origin: " << current -> getData().getValue().getCoO() << endl;
                cout << "   Country of Destination: " << current -> getData().getValue().getCoD() << endl;
                cout << "   How many stops?: " << current -> getData().getValue().getStopOver() << endl;
                cout << "   Price: " << current -> getData().getValue().getPrice() << endl;
                cout << "   Time of Departure: " << current -> getData().getValue().getToD() << endl;
                cout << "   Time of Arrival: " << current -> getData().getValue().getToA() << endl;
                cout << "   Date: "<< current -> getData().getValue().getDate() << endl;
                cout << endl;
            i++;
        }
        current = current -> getNext();
    }

    end = std::chrono::system_clock::now(); // Time ends
    std::chrono::duration<double> elapsed_seconds = end - start; // Difference is measured

    cout << "Time taken: " << elapsed_seconds.count() << " seconds" << endl; // Time is displayed
}

void FlightHASHTABLE::allinday(string date){
    int count = 0; int k = 1; string fileDate;

    // Iterate over the hash table and check each bucket for matching date
    for(int i = 0; i < capacity; i++){
        Node<HashNode> *current = buckets[i].getHead()->getNext();
        if(buckets[i].empty() != true){
            while(current -> getNext() != NULL){
                fileDate = current -> getData().getValue().getDate();
                fileDate.resize(6); // Resize the date before checking to ensure it matches the format
                if(fileDate == date || current -> getData().getValue().getDate() == date){
                    count++;
                }
                current = current -> getNext();
            }
        }
    }

    // If count is 0, no dates are found
    if(count == 0){
        cout << "Not Found!" << endl;
        return; // Exit function
    }

    // Otherwise display the number of records found and their details
    cout << count << " records found: " << endl;

    for(int j = 0; j < capacity; j++){
        Node<HashNode> *current = buckets[j].getHead()->getNext();
        if(buckets[j].empty() != true){
            while(current -> getNext() != NULL){
                fileDate = current -> getData().getValue().getDate();
                fileDate.resize(6); // Resize it again for the same purpose as above
                if(fileDate == date || current -> getData().getValue().getDate() == date){
                    cout << k << ". "; current -> getData().getValue().displayRecord();
                    k++;
                }
                current = current -> getNext();
            }
        }
    }  
}

// Print same companyName and flightNumber records in ascending order
void FlightHASHTABLE::printASC(string companyName, int flightNumber){
    std::string key = companyName + to_string(flightNumber);
    unsigned int idx = hashCode(key);

    Node<HashNode> *current = buckets[idx].getHead();
    int count = 0;

    buckets[idx].bubbleSort(); // Sort the list using Bubble Sort based on the country of destination

    // Get number of records with matching data
    while(current -> getNext() != NULL){
        if(current -> getData().getValue().getCompanyName() == companyName &&
            current -> getData().getValue().getFlightNumber() == flightNumber){
            count++;
        }
        current = current -> getNext();
    }

    // If count is 0, no records are found
    if(count == 0){
        cout << "Not Found!" << endl;
        return; // Exit function
    }

    // Otherwise display the number of records found and their details
    cout << count << " records found: " << endl;

    current = buckets[idx].getHead();
    int i = 1;

    while(current -> getNext() != NULL){
        if(current -> getData().getValue().getCompanyName() == companyName &&
            current -> getData().getValue().getFlightNumber() == flightNumber){
            cout << i << ". "; current -> getData().getValue().displayRecord();
            i++;
        }
        current = current -> getNext();
    }


}
