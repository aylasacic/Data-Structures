#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include "Member.h"

using namespace std;

// Constructor function for the Member Class
Member::Member(int member_id, string first_name, string last_name, string username, string password){
        this->Member_ID=member_id;
        this->First_name=first_name;
        this->Last_name=last_name;
        this->Username=username;
        this->Password=password;
    }
// Destructor function for the Member Class
Member::~Member(){
};

// Getter functions for the Member ID, Username and Password used for login
int Member::getMemberID() {return Member_ID;}
    
string Member::getUsername() {return Username;}
    
string Member::getPassword() {return Password;}
    
// Method for outputting the Member details into a file
void Member::output(){
        ofstream memberout("MembersTable.txt", ios::app);
        memberout << Member_ID << "," << First_name << "," << Last_name << "," << Username << "," << Password << endl;
    }

void memberOptions(){
    // All the options available to a member
    cout << "1) Book a Class" << endl;
    cout << "2) Display the Classes with vacencies" << endl;
    cout << "3) Cancel a booking" << endl;
    cout << "4) Quit the program" << endl;
    cout << "5) Logout" << endl;
}

// Adding a new member into the system
void addMember(Member *ClassArray []){
    int id, rand_nr; int i=0; int j=0; int flag = 0;
    string f_name, l_name, u_name, pass;

    srand(time(NULL));
    id=rand()%9000+1000; // Generating a random ID
    
    cout << "Enter the first name: "; cin >> f_name; // Getting user input for first name
    
    cout << "Enter the new last name: "; cin >> l_name; // Getting user input for last name
    
    u_name = f_name + to_string(id); // Creating the username
    
    rand_nr=rand()%9000+1000;
    pass=l_name+to_string(rand_nr); // Creating the password
    // If the ID already exists, or if the password already exists, generate a new ID or password, or both.
    do{
        while(ClassArray[i]!=NULL){
            if(ClassArray[i]->getMemberID()==id){
                flag = 1;
                id=rand()%9000+1000;
                break;
            }
            if(ClassArray[i]->getPassword()==pass){
                flag = 1;
                rand_nr=rand()%9000+1000;
                pass=l_name+to_string(rand_nr);
                break;
            }
            i++;
        }
    }while(flag!=0);

    // Finding the first empty spon in the array of pointers to Admin objects
    while(ClassArray[j]!=NULL){
        j++;
    }
    // Creating a new admin object with the information from above.
    Member *member = new Member(id, f_name, l_name, u_name, pass);
    ClassArray[j]= member;
    
    cout << endl;
    cout << "You have successfully added a new member!" << endl << endl;

}

// Function for returning the ID of the current Member logged in. Used for Canceling and Booking a class.
int returnID(Member *ClassArray [], string username, string password){
    int i = 0;
    while(ClassArray[i]!=NULL){
        if(ClassArray[i]->getUsername()==username && ClassArray[i]->getPassword()==password){
            return ClassArray[i]->getMemberID();
        }
        i++;
    }
    return 0;
}
