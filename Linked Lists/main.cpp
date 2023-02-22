#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<iomanip>
#include<limits>

// Header files
#include "DoublyLinkedList.h"
#include "User.h"
#include "Admin.h"
#include "Member.h"
#include "FitnessClass.h"

#define MAX_ARRAY 30

using namespace std;

//===============================================================================
void adminOptions(){
     
    cout << "\e[1mThe list of available operations for Admins: \e[0m" << endl
    << "\e[1m1)\e[0m Register a new Admin" << endl
    << "\e[1m2)\e[0m Register a new member" << endl
    << "\e[1m3)\e[0m View the list of members" << endl
    << "\e[1m4)\e[0m Add a fitness class" << endl
    << "\e[1m5)\e[0m Delete a fitness class" << endl
    << "\e[1m6)\e[0m Update the details of a fitness class" << endl
    << "\e[1m7)\e[0m Update the capacity of a fitness class" << endl
    << "\e[1m8)\e[0m Split a fitness class into two classes" << endl
    << "\e[1m9)\e[0m View the classes with vacancies" << endl
    << "\e[1m10)\e[0m Logout" << endl
    << "\e[1m11)\e[0m Quit the program" << endl;
}
//===============================================================================

//===============================================================================
void memberOptions(){
    
    cout << "\e[1mThe list of available operations for Members: \e[0m" << endl
    << "\e[1m1)\e[0m Book a Class" << endl
    << "\e[1m2)\e[0m View booking list" << endl
    << "\e[1m3)\e[0m View the classes with vacancies" << endl
    << "\e[1m4)\e[0m Cancel a booking" << endl
    << "\e[1m5)\e[0m Logout" << endl
    << "\e[1m6)\e[0m Quit the program" << endl;
}
//===============================================================================

// Function declarations
//==============================================================================================
void viewMembers();
template <typename T, typename C>
void loadUsers(T& DLL, C Class, string path);
void loadClasses();
void registerAdmin(string name, string surname);
void registerMember(string name, string surname);
void addFitnessClass();
template <typename T, typename U> bool login(T& DLL, string username, string password, U u);
void updateClassDetails(int class_id);
void changeCapacity(int class_id, int max_cap = 10);
void splitClass(int class_id, int cap = 10);
void viewClassesWithVacancies();
void viewBookingList();
void deleteFitnessClass(int class_id);
void bookAClass(int class_id);
void cancelABooking(int class_id);
int validID();
string validDate();
bool checkDate(int day, int month, int year);
string validTime();
int validInput();
void quit();
//==============================================================================================

// Doubly Linked List declarations
//===========================================
DoublyLinkedList<Admin> adminList;
DoublyLinkedList<Member> memberList;
DoublyLinkedList<FitnessClass> fitnessList;
//===========================================

int main()
{
    srand(time(NULL));
    string category, username, password, name, surname, action; int class_id, capacity; bool flag = true;
    Admin admin; Member member; // User for sending class into login function
    
    // Loading Admins, Members and Classes
    //============================================
    loadUsers(adminList, admin, "Admins.txt");
    loadUsers(memberList, member, "Members.txt");
    loadClasses();
    //============================================
    system("clear");
    
    while(true){
        cout << "\e[1mWelcome to the fitness management system!\e[0m" << endl;
        cout << "\e[1mPlease enter the category of your account before logging in: [admin/member]\e[0m" << endl;
        cin >> category;
        transform(category.begin(), category.end(), category.begin(), ::tolower); // Converts the category inputted into lower letters
        if(category == "admin"){
            cout << "\e[1mPlease enter your username: \e[0m" << endl; cin >> username;
            cout << "\e[1mPlease enter your password: \e[0m" << endl; cin >> password;
            if(login(adminList, username, password, admin)){
                do{
                    adminOptions();
                    cout << "\e[1mEnter the number of the required action [1-11]: \e[0m"; cin >> action;
                    system("clear");
                    if(action == "1"){
                        cout << "\e[1mEnter the name of the new admin: \e[0m"; cin >> name;
                        cout << "\e[1mEnter the surname of the new admin: \e[0m"; cin >> surname;
                        registerAdmin(name, surname);
                    }
                    else if(action == "2"){
                        cout << "\e[1mEnter the name of the new member: \e[0m"; cin >> name;
                        cout << "\e[1mEnter the surname of the new member: \e[0m"; cin >> surname;
                        registerMember(name, surname);
                    }
                    else if(action == "3"){
                        viewMembers();
                    }
                    else if(action == "4"){
                        addFitnessClass();
                    }
                    else if(action == "5"){
                        cout << "\e[1mEnter the id of the class you would like to delete: \e[0m"; cin >> class_id;
                        deleteFitnessClass(class_id);
                    }
                    else if(action == "6"){
                        cout << "\e[1mEnter the id of the class whose details you would like to change: \e[0m"; cin >> class_id;
                        updateClassDetails(class_id);
                    }
                    else if(action == "7"){
                        cout << "\e[1mEnter the id of the class whose capacity you would like to change (Default capacity is 10): \e[0m"; cin >> class_id;
                        cout << "\e[1mEnter the new capacity: \e[0m"; cin >> capacity;
                        changeCapacity(class_id, capacity);
                    }
                    else if(action == "8"){
                        cout << "\e[1mEnter the id of the class you would like to split in two: \e[0m"; cin >> class_id;
                        cout << "\e[1mEnter the capacity of the new classes: \e[0m"; cin >> capacity;
                        splitClass(class_id, capacity);
                    }
                    else if(action == "9"){viewClassesWithVacancies();}
                    else if(action == "10"){flag = false;}
                    else if(action == "11"){quit(); break;}
                    else{system("clear"); cout << "\033[31m\033[1mNo such option! Please enter a valid option [1-11]!\e[0m" << endl;}
                    
                }while(action != "10");
            }
            else{
                system("clear");
                cout << "\033[31m\033[1mInvalid credentials! Make sure you enter your username and password correctly!\e[0m" << endl;
            }
            
        }
        else if(category == "member"){
            cout << "\e[1mPlease enter your username: \e[0m" << endl; cin >> username;
            cout << "\e[1mPlease enter your password: \e[0m" << endl; cin >> password;
            if(login(memberList, username, password, member)){
                // Gets the digits from the username (4 digits) to send into the setCurrentMember function
                size_t index = username.find_last_not_of("0123456789");
                int member_id = stoi(username.substr(index + 1)); // Converts the digits into integer
                memberList.setCurrentMember(member_id);
                // Current member is used when booking and canceling a class
                flag = true;
                do{
                    memberOptions();
                    cout << "\e[1mEnter the number of the required action[1-6]: \e[0m"; cin >> action;
                    system("clear");
                    if(action == "1"){
                        cout << "\e[1mEnter the id of the class you would like to book: \e[0m"; cin >> class_id;
                        bookAClass(class_id);
                    }
                    else if(action == "2"){
                        viewBookingList();
                    }
                    else if(action == "3"){
                        viewClassesWithVacancies();
                    }
                    else if(action == "4"){
                        cout << "\e[1mEnter the id of the class you would like to cancel: \e[0m"; cin >> class_id;
                        cancelABooking(class_id);
                    }
                    else if(action == "5"){flag = false;}
                    else if(action == "6"){quit();}
                    else{cout << "\033[31m\033[1mNo such option! Please enter a valid option [1-6]!\e[0m" << endl;}
                }while(action != "10");
            }
            else{
                cout << "\033[31m\033[1mInvalid credentials! Make sure you enter your username and password correctly!\e[0m" << endl;
            }
        }
        else{
            system("clear");
            cout << "\033[31m\033[1mPlease enter one of the designated categories! Make sure you are either an admin or member!\e[0m" << endl;
        }
    }
    return 0;
}

// Function for registering admins
void registerAdmin(string name, string surname){
    Node<Admin> *current;
    int id, rand_nr; string username, password; int flag = 0;
    
    id = rand() % 9000 + 1000; // Random 4-digit ID
    do{
        // If the ID already exists, make a new one. Repeat untill a unique ID is made
        current = adminList.getHead()->getNext();
        while(current->getNext() != NULL){
            flag = 0;
            if(current->getData().getID() == id){
                id = rand()%9000+1000;
                flag = 1;
                break;
            }
            else{flag = 0;}
            current = current -> getNext();
        }
    }while(flag == 1);

    transform(name.begin(), name.end(), name.begin(), ::tolower); // Converts the name that was given by the admin into lowercase
    username = name + to_string(id); // Creating the username by concatenating name and ID

    rand_nr = rand()%9000+1000;
    transform(surname.begin(), surname.end(), surname.begin(), ::tolower); // Converts the surname that was given by the admin into lowercase
    password = surname + to_string(rand_nr); // Creating the password by concatenating surname and random number generated above
    
    // Creating a new admin object with the information from above.
    Admin admin = Admin(id, name, surname, username, password);

    adminList.addBack(admin); // Adds created admin to the back of the admin list
    system("clear");
    cout << "\033[1m\033[32mYou have successfully added a new admin, with username " << username << " and password " << password << "!\e[0m" << endl;
}

// Function for registering admins

void registerMember(string name, string surname){
    Node<Member> *current;
    int id, rand_nr; string username, password; int flag = 0;
    
    id = rand() % 9000 + 1000; // Random 4-digit ID
    do{
        // If the ID already exists, make a new one. Repeat untill a unique ID is made
        current = memberList.getHead()->getNext();
        while(current->getNext() != NULL){
            flag = 0;
            if(current->getData().getID() == id){
                id = rand()%9000+1000;
                flag = 1;
                break;
            }
            else{flag = 0;}
            current = current -> getNext();
        }
    }while(flag == 1);

    transform(name.begin(), name.end(), name.begin(), ::tolower); // Converts the name that was given by the admin into lowercase
    username = name + to_string(id); // Creating the password by concatenating surname and ID

    rand_nr = rand()%9000+1000;
    transform(surname.begin(), surname.end(), surname.begin(), ::tolower); // Converts the surname that was given by the admin into lowercase
    password = surname + to_string(rand_nr); // Creating the password by concatenating surname and random number generated above
    
    // Creating a new member object with the information from above.
    Member member = Member(id, name, surname, username, password);

    memberList.addBack(member); // Adds created admin to the back of the admin list
    system("clear");
    cout << "\033[1m\033[32mYou have successfully added a new member, with username " << username << " and password " << password << "!\e[0m" << endl;
}

// Login function for members and admins
template <typename T, typename U> bool login(T& DLL, string username, string password, U u){
    Node<U> *current = DLL.getHead(); // Gets head of the Doubly Linked List that was sent in
    while(current!=NULL){
        // If username and password match with ones stored in the list, login is successful.
        if(current->getData().getUsername() == username && current->getData().getPassword() == password){
            system("clear");
            cout << "\033[1m\033[32mYou have successfully logged in!\e[0m" << endl;
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Function for viewing registered members in the system
void viewMembers(){
    Node<Member> *current = memberList.getHead()->getNext();
    cout << "\e[1mMember ID" << setw(7) << " " << "Username" << setw(7) << " " << "Password" << "\e[0m" << endl;
    while(current->getNext()!=NULL){
        cout << right << setw(9) << current -> getData().getID() <<
                setw(15) << current -> getData().getUsername() <<
                setw(15) << current -> getData().getPassword() << endl;
        current = current->getNext();
    }
}

// Function for loading users, i.e. members and admins
template <typename T, typename C>
void loadUsers(T& DLL, C Class, string path){
    // Opening the file for loading data
    ifstream filein(path);
    int ID; string name, surname, username, password;
    if(filein.is_open()){
        string line;
        string tmp_id;
        // Gets every line until meeting a comma and passes it into one of the variables
        while(getline(filein, line)){
            stringstream ss(line);
            getline(ss, tmp_id, ',');
            ID = stoi(tmp_id);
            getline(ss, name, ',');
            getline(ss, surname, ',');
            getline(ss, username, ',');
            getline(ss, password, ',');
            C user = C(ID, name, surname, username, password); // Creates an Admin or Member object
            DLL.addBack(user); // Adds user to the designated Doubly Linked List
        }
    }
}

// Function for loading classes
void loadClasses(){
    // Opening the file for loading data
    ifstream filein("FitnessClasses.txt");
    int ID, max_cap, room_nr, member, nr_ids; string name, date, time, break_, room;
    if(filein.is_open()){
        string line;
        string tmp_id, tmp_max_cap, tmp_room_nr, tmp_member;
        // Gets every line until meeting a comma and passes it into one of the variables
        while(getline(filein, line)){
            stringstream ss(line);
            getline(ss, tmp_id, ',');
            ID = stoi(tmp_id);
            getline(ss, name, ',');
            getline(ss, date, ',');
            getline(ss, time, ',');
            getline(ss, tmp_max_cap, ',');
            max_cap = stoi(tmp_max_cap);
            getline(ss, tmp_room_nr, ',');
            room_nr = stoi(tmp_room_nr);
            
            FitnessClass fitnessclass = FitnessClass(ID, name, date, time, max_cap, room_nr); // Creates FitnessClass object
            
            fitnessList.addBack(fitnessclass); // Adds class to the Doubly Linked List

            // Stores empy string before it meets "[" symbol
            getline(ss, break_, '[');
            
            // While there is a comma delimiter, gets IDs stored
            while(getline(ss,tmp_member, ',')){
                if(tmp_member.find(']')){
                    tmp_member.erase(remove(tmp_member.begin(), tmp_member.end(), ']'), tmp_member.end()); // Removes "]" from the last ID in the list
                }
                // If the class is not empty, push the ID the stack in FitnessClass
                if(tmp_member != " "){
                    member = stoi(tmp_member);
                    fitnessclass.addMember(member);
                }
            }
        }
    }
}

// Function for adding a fitness class
void addFitnessClass()
{
    int id, room_nr; string name, date, time; int max_cap = 10;
    Node<FitnessClass> *current = fitnessList.getHead()->getNext();
    
    id = validID(); // ID validation, function is at the bottom
    
    cout << "\e[1mEnter the new class name: \e[0m";
    cin >> name;
    
    date = validDate(); // Date validation, function is at the bottom
    
    time = validTime(); // Time validation, function is at the bottom
    
    cout << "\e[1mEnter the new class capacity (Must be at least 10. If it is less, it will automatically be set to 10!): \e[0m"; max_cap = validInput(); // Integer validation, function is at the bottom
    max_cap = (max_cap < 10) ? max_cap = 10 : max_cap; // If the capacity is less than ten, it sets it to default 10
    
    cout << "\e[1mEnter the new classroom: \e[0m";
    room_nr = validInput(); // Integer validation, function is at the bottom

    // Creating a new FitnessClass object with the information from above.
    FitnessClass fitnessclass = FitnessClass(id, name, date, time, max_cap, room_nr); // Creates FitnessClass object

    fitnessList.addBack(fitnessclass); // Adds class to the back of the Doubly Linked List
    system("clear");
    cout << "\033[1m\033[32mYou have successfully added a new class!\e[0m" << endl;
}

// Function for splitting the class in two
void splitClass(int class_id, int cap){
    bool found = false;
    Node<FitnessClass> *current = fitnessList.getHead()->getNext();
    while(current->getNext() != NULL){
        if(current->getData().getID() == class_id){
            // If capacity is less than 5 or bigger than 15, sets capacity to default 10
            if(cap < 5 || cap > 15){
                cout << "\033[31m\033[1mCapacity must be between 5 and 15! Set to default 10!\e[0m" << endl;
                cap = 10;
            }
            found = true;
            string name, date, time, choice; int id, room_nr, k, j, temp;
            int array[MAX_ARRAY] = {0}; bool flag = false;
            int left = 0;
            int right = MAX_ARRAY-1;
            int nr_ids = current->getData().getStack()->getNrIDs();
            
            id = validID();
            
            // Pops each element in the Stack of IDs into an array
            int i = 0;
            while(current->getData().getStack()->empty() != true){
                array[i] = current->getData().getStack()->topElement();
                current->getData().getStack()->pop();
                i++;
            }

            // Reverses the array. Same function as in searchMember and removeMember method in FitnessClass
            while (left < right){
                temp = array[left];
                array[left] = array[right];
                array[right] = temp;
                left++; right--;
            }
            
            do{
                // If the user wants to change date and time, they are offered with the ability to do it
                cout << "\e[1mDo you want to change the time and date of the new class? [y/n]: \e[0m";
                cin >> choice;

                if(choice == "y" || choice == "Y"){
                    cout << "\e[1mEnter the new class date: \e[0m";
                    date = validDate(); // Date validation

                    cout << "\e[1mEnter the new class time: \e[0m";
                    time = validTime(); // Time validation
                    flag = true;
                }
                // If they do not wish to change the date and time, current class date and time are set
                else if(choice == "n" || choice == "N"){
                    date = current->getData().getDate();
                    time = current->getData().getTime();
                    flag = true;
                }
                else{cout << "\033[31m\033[1mInvalid optione! Please enter [y/n]!\e[0m" << endl;}
            }while(flag == false);

            // Capacity of class and stack are changes
            current -> getData().setCap(cap);
            name = current -> getData().getName();
            room_nr = current->getData().getRoomNr();
            
            FitnessClass class2 = FitnessClass(id, name, date, time, cap, room_nr); // FitnessClass object create for the other class with different ID
            fitnessList.addBack(class2); // Class added to the back of the list

            // IDs pushed into the stacks. If there is more members than allowed in the first class, they are put into the second one
            for(int j = MAX_ARRAY - nr_ids; j < MAX_ARRAY; j++){
                if(current->getData().getStack()->getNrIDs() == cap){
                    class2.addMember(array[j]);
                }
                else{current->getData().addMember(array[j]);}
            }
        }
        current = current -> getNext();
    }
    system("clear");
    if(found == false){cout << "\033[31m\033[1mNo class with ID " << class_id << "!\e[0m" << endl;}
    else{cout << "\033[1m\033[32mSuccesfully split the class!\e[0m" << endl;}
}

// Function for deleting a fitness class
void deleteFitnessClass(int class_id){
    bool flag = false;
    Node<FitnessClass> *current = fitnessList.getHead()->getNext();

    // If the ID is found, class is deleted usign removeElement method of the Doubly Linked List
    while(current->getNext() != NULL){
        if(current->getData().getID() == class_id){
            fitnessList.removeElement(class_id);
            flag = true;
        }
        current = current -> getNext();
    }
    if(flag == false){cout << "\033[31m\033[1mNo class with id " << class_id << "!\e[0m" << endl;}
    else{cout << "\033[1m\033[32mSuccessfully deleted the class!\e[0m" << endl;}
}

// Function for updating class details (date, time, room number)
void updateClassDetails(int class_id){
    int id, max_cap, room_nr; string name, choice, date, time; bool flag = false;
    Node<FitnessClass> *current = fitnessList.getHead()->getNext();

    system("clear");
    cout << "\e[1mWhich section do you wish to change? \e[0m" << endl
    << "\e[1m1)\e[0m Date when the class takes place" << endl
    << "\e[1m2)\e[0m Time at which the class takes place" << endl
    << "\e[1m3)\e[0m Room number in which the class takes place" << endl;

    while(current->getNext() != NULL){
        if(current->getData().getID() == class_id){

            do{
                // Admin chooses which to change
                flag = true;
                cout << "\e[1mWhat would you like to change? Enter one of the options [1-5]: \e[0m";
                cin >> choice;
                if(choice == "1"){
                    cout << "\e[1mEnter the new date: \e[0m"; date = validDate(); // Validation of date input
                    current->getData().setDate(date);
                }
                else if(choice == "2"){
                    cout << "\e[1mEnter the new time: \e[0m"; time = validTime(); // Validation of time input
                    current->getData().setTime(time); // Setting time
                }
                else if(choice == "3"){
                    cout << "\e[1mEnter the new room number: \e[0m"; room_nr = validInput(); // Validation of integer input
                    current->getData().setRoomNr(room_nr);
                }
                else{cout << "\033[31m\033[1mNo such option! Please make sure you enter one of the available options!\e[0m" << endl; flag = false;}
                
            }while(flag ==  false);
        }
        current = current->getNext();
    }
    system("clear");
    if(flag == false){cout << "\033[31m\033[1mNo class with id " << class_id << "!\e[0m" << endl;}
    else{cout << "\033[1m\033[32mSuccessfully updated class detail!\e[0m" << endl;}
}

// Function for changing the capacity of the class
void changeCapacity(int class_id, int max_cap){
    // If capacity is not in bounds, it is set to default 10
    if(max_cap < 5 || max_cap > 15){
        cout << "\033[31m\033[1mPlease put a valid capacity, between 5 and 15!\e[0m" << endl;
        max_cap = 10;
    }
    
    Node<FitnessClass> *current = fitnessList.getHead()->getNext();
    int array[MAX_ARRAY]={0}; int temp, j; int i = 0;
    int left = 0; int right = sizeof(array)/sizeof(array[0])-1; int flag = false;
    
    while(current->getNext() != NULL){
        if(current->getData().getID() == class_id){
            flag = true;
            int start = current->getData().getStack()->getNrIDs();
            // Everything is popped from the stack until it is empty (member IDs)
            while(current->getData().getStack()->empty() != true){
                   array[i]=current->getData().getStack()->topElement();
                   current->getData().getStack()->pop();
                   i++;
            }
            
            // Array is reversed
            while (left < right){
                temp = array[left];
                array[left] = array[right];
                array[right] = temp;
                left++; right--;
            }
            
            // Capacity of class and stack is changed
            current->getData().setCap(max_cap);

            // IDs are placed back into the stack. If the maximum capacity is reached, some IDs are removed
            for(int j = MAX_ARRAY-start; j<MAX_ARRAY; j++){
                if(current->getData().getStack()->getNrIDs()==max_cap){
                    break;
               }
                current->getData().getStack()->push(array[j]);
            }
        }
        current = current->getNext();
    }
    system("clear");
    if(flag == false){cout << "\033[31m\033[1mNo class with id " << class_id << "!\e[0m" << endl;}
    else{cout << "\033[1m\033[32mSuccessfully changed the class capacity!\e[0m" << endl;}
}

// Function for viewing the classes with vacancies
void viewClassesWithVacancies(){
    Node<FitnessClass> *current = fitnessList.getHead()->getNext();
    bool flag = false; // If a class is found, flag turns to true.

    cout << "\e[1mClasses with vacancies are: \e[0m" << endl;
    while(current->getNext() != NULL){
        // If a class is not full, it is displayed
        if(current->getData().getStack()->full() != true){
            flag = true;
            current->getData().print();
        }
        current = current->getNext();
    }
    if(flag == false){cout << "\033[31m\033[1mNo vacant classes!\e[0m" << endl;}
}

//Function for booking a class
void bookAClass(int class_id){
    Node<FitnessClass> *current = fitnessList.getHead()->getNext();
    Node<Member> *currMem = memberList.getCurrentMember(); // Gets current member's ID that is logged into the system
    bool flag = false; // Flag turns to true is the member is added

    // If the class ID is found
    while(current->getNext() != NULL){
        if(current->getData().getID() == class_id){
            // If the class is not full
            if(current->getData().getStack()->full() == true){
                cout << "\033[31m\033[1mClass is full!\e[0m" << endl;
                return;
            }
            else if(current->getData().searchMember(currMem->getData().getID())){
                cout << "\033[31m\033[1mYou are already in this class!\e[0m" << endl;
                return;
            }
            else{
                // Member is added
                flag = true;
                current->getData().addMember(currMem->getData().getID());
                break;
            }
        }
        current = current -> getNext();
    }
    system("clear");
    if(flag == false){cout << "\033[31m\033[1mNo class with ID " << class_id << "!\e[0m" << endl;}
    else{cout << "\033[1m\033[32mSuccessfully booked the class!\e[0m" << endl;}
}

// Function for viewing the vacant classes
void viewBookingList(){
    Node<FitnessClass> *current = fitnessList.getHead()->getNext();
    Node<Member> *currMem = memberList.getCurrentMember(); // Gets current member's ID that is logged into the system
    bool flag = false;

    cout << "\e[1mYou have booked the following classes: \e[0m" << endl;
    while(current->getNext() != NULL){
        // Gets the ID and searches the member in the stack
        int id = currMem->getData().getID();
        // If the member is there, displays the class as having their booking
        if(current->getData().searchMember(id) == true){
            flag = true;
            current->getData().print();
        }
        current = current -> getNext();
    }
    if(flag == false){cout << "\033[31m\033[1mNo classes booked!\e[0m" << endl;}
}

// Function for canceling a booking
void cancelABooking(int class_id){
    bool flag = false;
    Node<FitnessClass> *current = fitnessList.getHead()->getNext();
    Node<Member> *currMem = memberList.getCurrentMember(); // Gets current member's ID that is logged into the system

    while(current->getNext() != NULL){
        if(current->getData().getID() == class_id){
            flag = true;
            // Gets the ID and searches the member in the stack
            int id = currMem->getData().getID();
            // If the member is there, deletes their ID from the class
            if(current->getData().searchMember(id) == true){
                current->getData().removeMember(id);
                cout << "\033[1m\033[32mSuccessfully canceled the booking!" << endl;
                break;
            }
            else{
                cout << "\033[31m\033[1mYou have not booked this class!\e[0m" << endl;
            }
        }
        current = current->getNext();
    }
    system("clear");
    if(flag==false){ cout << "\033[31m\033[1mNo class with ID" << class_id << "!\e[0m" << endl;}
}

// Function for validating ID input
int validID(){
    Node<FitnessClass> *current;
    int i = 0; bool flag = true; int id;
    
    do{
        flag = true;
        current = fitnessList.getHead()->getNext();
        cout << "\e[1mEnter an ID for the new class: \e[0m"; cin >> id;
        // If input is good, i.e. an integer, proceed
        if(cin.good()){
            while(current->getNext() != NULL){
                // If ID already exists, display message
                if(current->getData().getID() == id){
                    cout << "\033[31m\033[1mClass ID already exists!\e[0m" << endl;
                    flag = false;
                    break;
                }
                current = current->getNext();
            }
        }
        else{
            // If input is bad, clear it, ignore it and ask for another input
            flag = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\033[31m\033[1mInvalid input! Make sure the ID is a number!\e[0m" << endl;
        }
    }while(flag == false);
    
    return id;
}

// Function for validating date input
string validDate(){
    bool flag = false; string date;
    
    do{
        cout << "\e[1mEnter a date for the new class: \e[0m"; cin >> date;
        // If date is in correct format and length, proceed
        if(date[2] == '-' && date[5] == '-' && date.length() == 10){
            int day, month, year;
            day = stoi(date.substr(0,2));
            month = stoi(date.substr(3,5));
            year = stoi(date.substr(6,11));
            // If date is accurate, i.e. not a non existent day or month or year that is too far away, proceed
            if(checkDate(day, month, year)){
                flag = true;
            }
            else{cout << "\033[31m\033[1mInvalid input! Make sure that the date is valid!\e[0m" << endl;}
        }
        else{cout << "\033[31m\033[1mInvalid input! Make sure that the date is valid!\e[0m" << endl;}
    }while(flag == false);
    
    return date;
}

bool checkDate(int day, int month, int year){

    if(day < 1 || day > 31){return false;} // Valid day
    else if(month < 1 || month > 12) {return false;} // Valid month
    else if (year < 2022 || year > 2023) {return false;} // Valid year (Bigger than 2023 seems bad)

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31){return false;} // If month is 30-days, day cannot be put as 31
    else if ((month == 2) && (year % 4 == 0) && day > 29){return false;} // Gap year
    else if ((month == 2) && (year % 4 != 0) && day > 28){return false;} // Non-gap year (Does not work for all as 1900 would pass as a gap year, though it is not)
    
    return true;
}

// Time input validation
string validTime(){
    bool flag = false; string time;
    
    do{
        cout << "\e[1mEnter a time for the new class: \e[0m"; cin >> time;
        // If it is the correct format and length
        if(time[2] == ':' && time.length() == 5){
            string hours, minutes; int hours_, minutes_;
            hours = time.substr(0,2); hours_ = stoi(hours);
            minutes = time.substr(3,5); minutes_ = stoi(minutes);
            // If time input is valid, i.e. minutes and hours are within limits, proceed.
            if((hours_ < 0 || hours_ > 23) || (minutes_ < 0 || minutes_ > 59)){
                cout << "\033[31m\033[1mInvalid input! Make sure that the time is valid!\e[0m" << endl;
            }
            else{flag = true;}
        }
        else{cout << "\033[31m\033[1mInvalid input! Make sure that the time is valid!\e[0m" << endl;}
    }while(flag == false);
    
    return time;
}
    
// Valid integer input function
int validInput(){
    int input; bool flag = true;
    do{
        // If the input is good, i.e. an integer, proceed
        flag = true;
        cin >> input;
        if(!cin){
            // If it is not good, clear the input and ask for it again
            flag = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\033[31m\033[1mMake sure that your input cosists of only numbers!\e[0m" << endl;
            cout << "\e[1mEnter new value: \e[0m";
        }
    }while(flag == false);
    
    return input;
}
// Quit function
void quit(){

    // Sorts each list and outputs the data from it
    adminList.bubbleSort();
    adminList.saveData("Admins.txt");
    memberList.bubbleSort();
    memberList.saveData("Members.txt");
    fitnessList.bubbleSort();
    fitnessList.saveData("FitnessClasses.txt");

    // Exits the program
    exit(0);
}


