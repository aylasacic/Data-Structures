#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include "Admin.h"

using namespace std;

// Constructor function for Admin Class
Admin::Admin(int admin_id, string first_name, string last_name, string username, string password){
		this->Admin_ID=admin_id;
		this->First_name=first_name;
		this->Last_name=last_name;
		this->Username=username;
		this->Password=password;
	}
// Destructor function for Admin Class
Admin::~Admin(){
};
// Getter functions for Admin ID, Username and Password used for admin login
int Admin::getAdminID(){return Admin_ID;}
    
string Admin:: getUsername(){return Username;}
    
string Admin:: getPassword(){return Password;}

// Outputting the admin information into a file.
void Admin:: output(){
        ofstream adminout("AdminsTable.txt", ios::app);
        adminout << Admin_ID << "," << First_name << "," << Last_name << "," << Username << "," << Password << endl;
    }

// Function for Adding an admin
void addAdmin(Admin *ClassArray []){
    int id, rand_nr; int i=0; int j=0; int flag = 0;
    string f_name, l_name, u_name, pass;

    srand(time(NULL));
    id=rand()%9000+1000; // Random 4-digit ID
    
    cout << "Enter the first name: "; cin >> f_name; // Getting user input for first name
    
    cout << "Enter the new last name: "; cin >> l_name; // Getting user input for last name
    
    u_name = f_name + to_string(id); // Creating the username
    
    rand_nr=rand()%9000+1000;
    pass=l_name+to_string(rand_nr); // Creting the password
    
    // If the ID already exists, or if the password already exists, generate a new ID or password, or both.
    do{
        while(ClassArray[i]!=NULL){
            flag = 0;
            if(ClassArray[i]->getAdminID()==id){
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
    Admin *admin = new Admin(id, f_name, l_name, u_name, pass);
    ClassArray[j]= admin;
    
    cout << endl;
    cout << "You have successfully added a new admin!" << endl << endl;
}

void adminOptions(){
    // All options available to the admin.
    cout << "1) Register a new Admin" << endl;
    cout << "2) Register a new member" << endl;
    cout << "3) Add a fitness class" << endl;
    cout << "4) Delete a fitness class" << endl;
    cout << "5) Update the details of a fitness class" << endl;
    cout << "6) Display the Classes with vacencies" << endl;
    cout << "7) Quit the program" << endl;
    cout << "8) Logout" << endl;
}


