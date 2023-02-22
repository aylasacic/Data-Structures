#include<iostream>
#include<fstream>
#include<string>
#include "FitnessClass.h"

using namespace std;

// Constructor function for FitnessClass Class
FitnessClass::FitnessClass(int class_id, string class_name, string class_date, string class_time, int max_cap, int room_nr){
        this->Class_ID=class_id;
        this->Class_name=class_name;
        this->Class_date=class_date;
        this->Class_time=class_time;
        this->Max_capacity=max_cap;
        this->Room_number=room_nr;
        this->List_Members=new int[max_cap];
    }
// Desructor function for FitnessClass Class deallocates memory used for dynamic array of Members
FitnessClass::~FitnessClass(){
    delete [] List_Members;
    }

// Getter functions for FitnessClass
int FitnessClass::getFitnessClassID(){return Class_ID;}
    
string FitnessClass::getFitnessClassName(){return Class_name;}
    
string FitnessClass::getFitnessClassTime(){return Class_time;}
    
string FitnessClass::getFitnessClassDate(){return Class_date;}
    
int FitnessClass::getFitnessClassRoomNr(){return Room_number;}
    
int FitnessClass::getMaxCap(){return Max_capacity;}
    
// Setter functionf for FitnessCLass
void FitnessClass::setClassID(int id){this->Class_ID=id;}
    
void FitnessClass::setClassName(string class_name){this->Class_name=class_name;}
    
void FitnessClass::setClassDate(string class_date){this->Class_date=class_date;}
    
void FitnessClass::setClassTime(string class_time){this->Class_time=class_time;}
    
// Setting maximum capacity changes the length of the Members array
void FitnessClass::setMaxCap(int max_cap){
    int *new_array = new int[max_cap];
    
// Copying the elements of List_Members into new array
    for(int i = 0; i < max_cap; i++){
        if(List_Members[i]==0){
            break;
        }
        else{
            new_array[i]=List_Members[i];
        }
    }
// Deleting List_Members and setting the new length to maximum capcacity
    this->Max_capacity=max_cap;
    delete[] List_Members;
    this->List_Members=new int[max_cap];

// Copying elements from new_array back into List_Members
    for(int i = 0; i < max_cap; i++){
        if(new_array[i]==0){
            break;
        }
        else{
            List_Members[i]=new_array[i];
        }
    }
// Deleting the new_array
    delete [] new_array;
}
    
void FitnessClass::setRoomNr(int room_nr){this->Room_number=room_nr;}
    
// Method for adding members to a fitness class
void FitnessClass::addMember(int id){
    for(int i = 0; i < Max_capacity; i++){
        if(List_Members[i]==0){
            List_Members[i]=id;
            break;
        }
    }
    cout << "You have successfully enrolled yourself into the class" << endl;
}
    
// Method for checking if there are available spots in a fitness class
bool FitnessClass::check_vacancy(){
    for(int i = 0; i < Max_capacity; i++){
        if(List_Members[i]==0){
            return true;
        }
    }return false;
}
    
// Method for returning whether a memeber is already in the fitness class
bool FitnessClass::memberInClass(int id){
    for(int i = 0; i < Max_capacity; i++){
        if(id==List_Members[i]){
            return true;
        }
    }return false;
}

// Method for removing a member from a fitness class
void FitnessClass::removeMember(int id){
    int idx = 0;
    for(int i = 0; i < Max_capacity; i++){
        if(id==List_Members[i]){
            List_Members[i]=0;
            break;
        }
        idx++;
    }

// Sorting the list after the member is removed
    for(int j = idx; idx < Max_capacity; idx++){
        if(List_Members[j+1]==0){
            break;
        }
        List_Members[j]=List_Members[j+1];
    }
}

// Displaying fitness classes. Used with the check_vacancy method.
void FitnessClass::print(){
    cout << "==============================" << endl;
    cout << left << setfill(' ') << setw(20) << "ID:" << right << setfill(' ') << setw(10) << Class_ID << endl;
    cout << left << setfill(' ') << setw(20) << "Name" << right << setfill(' ') << setw(10) << Class_name <<  endl;
    cout << left << setfill(' ') << setw(20) << "Date:" << right << setfill(' ') << setw(10) << Class_date << endl;
    cout << left << setfill(' ') << setw(20) << "Time:" << right << setfill(' ') << setw(10) << Class_time << endl;
    cout << left << setfill(' ') << setw(20) << "Room Number:" << right << setfill(' ') << setw(10) << Room_number << endl;
    cout << "==============================" << endl;
}

// Outputting the FitnessClass information into a text file
void FitnessClass::output(){
    ofstream fitnessout("FitnessClassesTable.txt", ios::app);
    fitnessout << Class_ID << "," << Class_name << "," << Class_date << "," << Class_time << "," << Max_capacity << "," << Room_number << endl;
}

// Function that returns whether an ID already exists when making a new fitness class.
int idExists(FitnessClass *ClassArray[]){
    int i=0; int flag=0; int id; bool good = false;
    do{
        cout << "Enter the ID for the class: " << endl;
        cin >> id;
        // If the input is good, the program proceeds, i.e. it is not a letter
        if(cin.good()){
            if(to_string(id).length()==4){
                while(ClassArray[i]!=NULL){
                    if(ClassArray[i]->getFitnessClassID()==id){
                        cout << "Class ID already exists!" << endl;
                        i=0;
                        flag=1;
                        break;
                    }
                    else{
                        flag=0;
                    }
                    i++;
                }
                if(flag==0){
                    good=true;
                    break;
                }
            }
            else{
                // Resetting the buffer's state to good
                cin.clear();
                // Emptying it
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Please make sure that the ID is a 4-digit number!" << endl;
                continue;
            }
        }
        else{
            // Resetting the buffer's state to good
            cin.clear();
            // Emptying it
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Please make sure that the ID is a 4-digit number!" << endl;
            continue;
        }
    }while(!good);
    
    return id;
}

// Function for adding a new fitness Class
void addFitnessClass(FitnessClass *ClassArray []){
    int id, max_cap, room_nr; string name; char date[15]; char time[10];
    string date_, time_;
    int i=0;
    
    id = idExists(ClassArray);
    cout << "Enter the name of the new class: "; cin >> name;
    
    while(true){
        cout << "Enter the the date of the class: "; cin >> date;
        // If date format is correct, proceed
        if(validInput(date, "date")){
            // Converting the char array into a string, so that it can be used in the constructor
            date_ = date;
            while(true){
                cout << "Enter the time of the class: "; cin >> time;
                // If time format is correct, proceed
                if(validInput(time, "time")){
                    // Converting the char array into a string, so that it can be used in the constructor
                    time_ = time;
                    cout << "Enter the maximum capacity of the class: "; cin >> max_cap;
                    cout << "Enter the room number the class will be held in: "; cin >> room_nr;
                    break;
                }
                else{
                    cout << "Invalid time format! Plase make sure you enter it in the hh:mm format!" << endl;
                    continue;
                }
            }
                break;
        }
        else{
            cout << "Invalid date format! Plase make sure you enter it in the dd-mm-yyyy format!" << endl;
            continue;
        }
    }
    
    while(ClassArray[i]!=NULL){
        i++;
    }
    
    // create a new fitness class and add it to the fitness_class array
    FitnessClass *fitness_class = new FitnessClass(id, name, date_, time_, max_cap, room_nr);
    ClassArray[i] = fitness_class;
}

// Function for updating information of a fitness class
void updateClassDetails(FitnessClass *ClassArray []){
    int id, choice, max_cap, room_nr; char date[15]; char time[10]; string name, date_, time_;
    int i = 0; int flag = 0; int done = 0;
    cout << "Enter the ID of the class you would like to update: "; cin >> id;
    
    // If ID is present, edits can be made.
    while(ClassArray[i]!=NULL){
        if(ClassArray[i]->getFitnessClassID()==id){
            flag=1;
            break;
        }
        i++;
    }
    
    if(flag==0){
        cout << "Class does not exist!" << endl;
        return;
    }
    
    system("clear");
    
    // Use of setters for changing the class information
    do{

        cout << "Which section do you wish to change? " << endl;
        cout << "1) ID of the class" << endl;
        cout << "2) Name of the class" << endl;
        cout << "3) Date when the class takes place" << endl;
        cout << "4) Time at which the class takes place" << endl;
        cout << "5) Maximum capacity of the class" << endl;
        cout << "6) Room number in which the class takes place" << endl;
        
        cin >> choice;
        switch(choice){
            case 1:
                id = idExists(ClassArray);
                ClassArray[i]->setClassID(id);
                done = 1;
                break;
            case 2:
                cout << "Enter the new name: "; cin >> name;
                ClassArray[i]->setClassName(name);
                done = 1;
                break;
            case 3:
                while(true){
                    cout << "Enter the new date: "; cin >> date;
                    // If date format is valid, proceed
                    if(validInput(date, "date")){
                        // Converting the char array into a string, so that it can be used in the constructor
                        date_ = date;
                        ClassArray[i]->setClassDate(date_);
                        done = 1;
                        break;
                    }else{
                        cout << "Invalid date format! Plase make sure you enter it in the dd/mm/yyyy format!" << endl;
                        continue;
                    }
                }
                break;
            case 4:
                while(true){
                    cout << "Enter the new time: "; cin >> time;
                    // If time format is valid, proceed
                    if(validInput(time, "time")){
                        time_ = time;
                        ClassArray[i]->setClassTime(time);
                        done = 1;
                        break;
                    }else{
                        cout << "Invalid time format! Plase make sure you enter it in the hh:mm format!" << endl;
                    }
                }
                break;
            case 5:
                cout << "Enter the new maximum capacity: "; cin >> max_cap;
                ClassArray[i]->setMaxCap(max_cap);
                done = 1;
                break;
            case 6:
                cout << "Enter the new room number: "; cin >> room_nr;
                ClassArray[i]->setRoomNr(room_nr);
                done = 1;
                break;
            default:
                cout << "Please enter a valid option!" << endl;
                flag = 0;
                break;
        }
    }while(done!=1);
    
    cout << "You have successfully updated the fitness class!" << endl;
}

// Function for deleting a Fitness Class
void deleteFitnessClass(FitnessClass *ClassArray []){
    int id; int i = 0; int flag = 0;
    cout << "Enter the ID of the class you would like to delete: "; cin >> id;
    
    while(ClassArray[i]!=NULL){
        if(ClassArray[i]->getFitnessClassID()==id){
            flag = 1;
            break;
        }
        i++;
    }
    
    // If the ID exists, the fitness_arraay is sorted from the index of the class that is to be deleted
    if(flag == 0){
        cout << "ID does not exist!" << endl;
        return;
    }
    else{
        while(ClassArray[i]!=NULL){
            ClassArray[i]=ClassArray[i+1];
            i++;
        }
    }
    cout << "You have successfully deleted the fitness class!" << endl;

}

// Function for viewing classes with vacancies
void viewClassesWithVacancies(FitnessClass *ClassArray[]){
    int i = 0; int flag = 0;
    system("clear");
    cout << "Classes with vacancies are: " << endl;
    
    // If a class is found, the print function is called to display its information
    while(ClassArray[i]!=NULL){
        if(ClassArray[i]->check_vacancy()){
            flag = 1;
            ClassArray[i]->print();
        }
        i++;
    }
    
    if(flag == 0){
    cout << "There are no vacant classes!" << endl;
    }
}

// Function for canceling a booking by a member
void CancelABooking(FitnessClass *ClassArray[], int current_ID){
    int id; int flag = 0; int i = 0;
    cout << "Enter the ID of the class you would like to cancel your booking for: "; cin >> id;
    
    while(ClassArray[i]!=NULL){
        if(ClassArray[i]->getFitnessClassID()==id){
            if(ClassArray[i]->memberInClass(current_ID)){
                ClassArray[i]->removeMember(current_ID);
                flag = 1;
                break;
            }
            else{
                flag = 2;
            }
        }i++;
    }
    
    // Depending on the flag, if a class is found and if the member is in it, they are removed.
    if(flag==0){
        cout << "Class ID does not exist!" << endl;
    }
    else if(flag == 1){
        cout << "You have successfully booked the class!" << endl;
    }
    else{
        cout << "You are not enrolled in this class!" << endl;
    }
}

// Function for booking a class by a member
void bookAClass(FitnessClass *ClassArray[], int current_ID){
    int id; int i = 0; int flag = 0;
    cout << "Enter the ID of the class you would like to book: "; cin >> id;
    
    while(ClassArray[i]!=NULL){
        if(ClassArray[i]->getFitnessClassID()==id){
            if(ClassArray[i]->check_vacancy()){
                ClassArray[i]->addMember(current_ID);
                flag = 1;
                break;
            }
            else{
                flag = 2;
            }
        }
        i++;
    }
    
    // Depending on the flag, if a class is found and if the member is not already in it, they are added.
    if(flag==0){
        cout << "Class ID does not exist!" << endl;
    }
    else if(flag == 1){
        cout << "You have successfully booked the class!" << endl;
    }
    else{
        cout << "Class is fully booked!" << endl;
    }
}

bool validInput(char value[], string type){
    if(type=="date"){
        if(value[2]=='-' && value[5]=='-'){
           return true;
        }
    }
    else{
        if(value[2]==':'){
            return true;
        }
    }
    return false;
}
