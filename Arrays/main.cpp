//============================================================================
// Name         : Assignment 1: A Simple Fitness Center Management System.cpp
// Author       : Ajla Šačić
// Date Created : 10/02/2022
// Date Modified: 24/02/2022
//============================================================================

#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include "Admin.h"
#include "Member.h"
#include "FitnessClass.h"

using namespace std;

// Template for login function so that both admin and member can login without the need to create two separate functions
template <typename C>
bool login(C *ClassArray []);
// Quit function
void quit(Admin *ClassArray1[], Member *ClassArray2[], FitnessClass *ClassArray3[]);

int main(){
    // Category: admin/member, Username and Password are distinct
    string category, username, password;
    int input; int id; int flag = 0;
    // Array for Admin objects
    Admin* admin_array[50]={NULL};
    // Array for Member objects
    Member* member_array[100]={NULL};
    // Array for FitnessClass objects
    FitnessClass* fitness_array[50]={NULL};
    // Default admin used for loggin in
    admin_array[0]=new Admin(1, "admin","admin","admin1","admin1");
    
    // Opening all three files for writing to delete data from previous session.
    ofstream adminout("AdminsTable.txt"); adminout.close();
    ofstream memberout("MembersTable.txt"); memberout.close();
    ofstream fitnessout("FitnessClassesTable.txt"); fitnessout.close();
    
    while(true){
        cout << "Welcome to the fitness management system!" << endl <<
        "Please enter the category of your account before logging in [admin/memeber]." << endl;
        cin >> category;
        if(category == "admin"){
            if(login(admin_array)){
                cout << "You have logged in successfully!" << endl;
                while(true){
                    flag = 0;
                    adminOptions();
                    cout << "Enter the number of the required action: [1-8]" << endl; cin >> input;
                    switch(input){
                        case 1:
                            addAdmin(admin_array); break;
                        case 2:
                            addMember(member_array); break;
                        case 3:
                            addFitnessClass(fitness_array); break;
                        case 4:
                            deleteFitnessClass(fitness_array); break;
                        case 5:
                            updateClassDetails(fitness_array); break;
                        case 6:
                            viewClassesWithVacancies(fitness_array); break;
                        case 7:
                            flag = 1;
                            break;
                        case 8:
                            flag = 2;
                            break;
                        default:
                            cout << "Please enter a valid option!" << endl;
                            break;
                    }
                    // If flag is 1 or 2, the first main loop stops working
                    if(flag == 1 || flag ==2){
                        break;
                    }
                }
            }
            // If admin credentials are not correct, the program informs the user that thy have not logged in.
            else{
                cout << "Wrong credentials! Please make sure you are an admin!" << endl;
            }
        }
        else if(category == "member") {
            if(login(member_array)){
                cout << "You have logged in successfully!" << endl;
                while(true){
                    memberOptions();
                    cout << "Enter the number of the required action: [1-8]" << endl; cin >> input;
                    // Returning the ID of current member logged. Used in booking and canceling a class.
                    id = returnID(member_array, username, password);
                    switch(input){
                        case 1:
                            bookAClass(fitness_array, id);
                            break;
                        case 2:
                            viewClassesWithVacancies(fitness_array);
                            break;
                        case 3:
                            CancelABooking(fitness_array, id);
                            break;
                        case 4:
                            flag = 1;
                            break;
                        case 5:
                            flag = 2;
                            break;
                        default:
                            cout << "Please enter a valid option!" << endl;
                            break;
                    }
                    // flag == 1 for quitting completely and flag == 2 for logging out.
                    if(flag == 1 || flag ==2){
                        break;
                    }
                }
            }
            // If member credentials are not correct, the program informs the user that thy have not logged in.
            else{
                cout << "Wrong credentials! Please make sure you are a member!" << endl;
            }
        }
        else{
            cout << "No known " << category << " category! Please enter a valid category!" << endl;
        }
        // If flag == 1, the program quits all together, but before quitting, the data is saved into its respective files.
        if(flag == 1){
            quit(admin_array, member_array, fitness_array);
        }
    }
}

// Login Function for both Admin and Member
template <typename C>
bool login(C *ClassArray []){
    int i=0; int flag = 0;
    string username, password;
    cout << "Plase enter your username:" << endl;
    cin >> username;
    cout << "Plase enter your password:" << endl;
    cin >> password;
    
    while(ClassArray[i]!=NULL){
        if(ClassArray[i]->getUsername()==username && ClassArray[i]->getPassword()==password){
            return true;
        }
        i++;
    }
    return false;
}

// Quit function saves the data into files and quits the program;
void quit(Admin *ClassArray1[], Member *ClassArray2[], FitnessClass *ClassArray3[]){
    int i = 0; int j = 0; int k = 0; // counters for while functions
    while(ClassArray1[i]!=NULL){
        ClassArray1[i]->output();
        i++;
    }
    while(ClassArray2[j]!=NULL){
        ClassArray2[j]->output();
        j++;
    }
    while(ClassArray3[k]!=NULL){
        ClassArray3[k]->output();
        k++;
    }
    
    exit(0);
}
