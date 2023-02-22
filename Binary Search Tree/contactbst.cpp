#include<iostream>
#include<sstream>
#include<cstdlib>
#include<fstream>
#include<string>

#include "contactbst.h"
#include "contact.h"
#include "myvector.h"


using namespace std;

Node::Node(){}

Node::Node(string key, MyVector<Contact>* contactVector)
{
    this->key = key;
    this->contactVector = contactVector;
    this->left = nullptr;
    this->right = nullptr;
}
Node::~Node()
{}

// Constructor for ContactBST class
ContactBST::ContactBST()
{
    this->root=nullptr;
}

// Destructor for ContactBST class
ContactBST::~ContactBST()
{
   //Keep removing the root of the tree untill it becomes empty
    while(root)
        root = clean(root, root->key);
}

//Helper method for insert method
void ContactBST::insert_helper(string key, Contact* data)
{
   root = add(root, key, data);
}

//Helper method for remove
void ContactBST::remove_helper(string key)
{
   root = del(root, key);
}

Node* ContactBST::getRoot(){
   return this->root;
}

// Recursive function to find the height of the BST
int ContactBST::height(Node *ptr){
   if(ptr == NULL){return -1;} // If the tree is empty or leaf node is found, return -1
   else{return 1 + max(height(ptr->left), height(ptr->right));} // Add 1 and call height function again
}

// Method to add a new records
Node* ContactBST::add(Node* ptr, string key, Contact* data){   
   if(ptr == nullptr){
        // if the key does not exist, create a new vector
        MyVector<Contact> *myVec = new MyVector<Contact>();
        // add the new record to the vector
        myVec->push_back(*data);
        // create the new node
        ptr = new Node(key, myVec);
        return ptr;
   }
   else if (ptr -> key == key){
        // if the key exists, push the new record into the vector
        ptr -> getData() -> push_back(*data);
        return ptr;
   }
   if(ptr -> key < key){
        ptr->right = add(ptr->right, key, data);
   }
   else{
        ptr->left = add(ptr->left, key, data);
   }
   return ptr;
}

// Method for updating an existing contact
Node* ContactBST::update(Node* ptr, string key){
    if(ptr == NULL){
        // if key is not found, NULL is returned
        cout << "Key not found!" << endl;
        return NULL;
    }
    else if(ptr -> key == key){
        //if key is found, vector data is displayed and user asked to select a record to edit
        string record;
        cout << ptr -> getData() -> getSize() << " records found:" << endl;
        ptr -> getData() -> printData(); 
        cout << "Please select the record you want to edit: "; cin >> record;
        // Checking whether the record is within range
        if(stoi(record)-1 >= 0 && stoi(record) <= ptr -> getData() -> getSize()){
            string category, fname, lname, email, phone, city, country; int isFav;
            cout << "Which field do you want to edit? 1) First Name 2) Last Name 3) Email 4) Phone 5) City 6) Country: "; cin >> category;
            if(category == "1"){
                // changing the first name and storing other information in variables
                cout << "Please enter the new first name: "; cin >> fname;
                ptr -> getData() -> at(stoi(record)-1).setFName(fname);
                lname = ptr -> getData() -> at(stoi(record)-1).getLName();
                email = ptr -> getData() -> at(stoi(record)-1).getEmail();
                phone = ptr -> getData() -> at(stoi(record)-1).getPhone();
                city = ptr -> getData() -> at(stoi(record)-1).getCity();
                country = ptr -> getData() -> at(stoi(record)-1).getCountry();
                isFav = ptr -> getData() -> at(stoi(record)-1).getIsFav();

                // if vector only has one element, delete the element with the key
                if(ptr -> getData() -> getSize() == 1){
                    del(root, key);
                    // form new key with new first name
                    string new_key = fname + " " + lname;
                    // create a new contact object for the key
                    Contact *contact1 = new Contact(fname, lname, email, phone, city, country, isFav);
                    // insert new key back into the BST
                    insert_helper(new_key, contact1);
                }
                // if it is not the only element in the vector, erase the record
                else if(fname != key.substr(0, key.find(" "))){
                    ptr ->getData()->erase(stoi(record)-1);
                    // create a new key with the first name
                    string new_key = fname + " " + lname;
                    // create a new contact object for the key
                    Contact *contact1 = new Contact(fname, lname, email, phone, city, country, isFav);
                    // insert new key back into the BST
                    insert_helper(new_key, contact1);
                } 
            }
            else if(category == "2"){
                // Same procedure for last name as for first name
                cout << "Please enter the new last name: "; cin >> lname;
                ptr -> getData() -> at(stoi(record)).setLName(lname);
                fname = ptr -> getData() -> at(stoi(record)-1).getFName();
                email = ptr -> getData() -> at(stoi(record)-1).getEmail();
                phone = ptr -> getData() -> at(stoi(record)-1).getPhone();
                city = ptr -> getData() -> at(stoi(record)-1).getCity();
                country = ptr -> getData() -> at(stoi(record)-1).getCountry();
                isFav = ptr -> getData() -> at(stoi(record)-1).getIsFav();
                Contact *contact2 = new Contact(fname, lname, email, phone, city, country, isFav);

                if(ptr -> getData() -> getSize() == 1){
                    del(root, key);
                    string new_key = fname + " " + lname;
                    insert_helper(key, contact2);
                } 
                else if(lname != key.substr(key.find(" ")+1)){
                    ptr ->getData()->erase(stoi(record)-1);
                    string new_key = fname + " " + lname;
                    insert_helper(new_key, contact2);
                }
            }
            // other categories do noot effect key, so only setters are used to change the data
            else if(category == "3"){
                cout << "Please enter the new email: "; cin >> email;
                ptr -> getData() -> at(stoi(record)-1).setEmail(email);
            }
            else if(category == "4"){
                cout << "Please enter the new phone: "; cin >> phone;
                ptr -> getData() -> at(stoi(record)-1).setPhone(phone);
            }
            else if(category == "5"){
                cout << "Please enter the new city: "; cin >> city;
                ptr -> getData() -> at(stoi(record)-1).setCity(city);
            }
            else if(category == "6"){
                cout << "Please enter the new country: "; cin >> country;
                ptr -> getData() -> at(stoi(record)-1).setCountry(country);
            }
            else{
                cout << "Invalid option!" << endl;
            }
        }
        else{
            // input is cleared and exception thrown
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            throw out_of_range("Index out of range!");
        }
        cin.clear(); cin.ignore();
        return ptr;
    }
    else if(key < ptr -> key){
        return update(ptr -> left, key);
    }
    else{
        return update(ptr -> right, key);
    }
}

// Method to find the minimum element of the BST
Node* ContactBST::findMin(Node *ptr){
    // if tree is empty, return NULL
    if(height(ptr) == -1){
        return NULL;
    }
    // When the minimum child is found, return it
    if(ptr->left == nullptr){
        return ptr;
    }
    else{
        return findMin(ptr->left);
    }
}

// Method to find the maxiumum element of the BST
Node* ContactBST::findMax(Node *ptr){
    // if tree is empty, return NULL
    if(height(ptr) == -1){
        return NULL;
    }
    // When the maximum child is found, return it
    if(ptr->right == nullptr){
        return ptr;
    }
    else{
        return findMax(ptr->right);
    }
}

// Method for finding a node in the tree
Node* ContactBST::search(Node *ptr, string key){
    if(ptr == NULL){
        cout << "Key not found!" << endl;
        return NULL;
    }
    else if(ptr->key == key){
        // if key is found, all vector elements are printed to the screen
        cout << ptr -> getData() -> getSize() << " record(s) found: " << endl << endl;
        for(int i = 0; i < ptr -> getData() -> getSize(); i++){
            cout << "Name: " << ptr -> getData() -> at(i). getFName() << " " 
                 <<  ptr -> getData() -> at(i). getLName() << " " << endl
                 <<  "Email: " << ptr -> getData() -> at(i). getEmail() << endl
                 <<  "Phone: " << ptr -> getData() -> at(i). getPhone() << endl
                 <<  "City: " << ptr -> getData() -> at(i). getCity() << endl
                 <<  "Country: " << ptr -> getData() -> at(i). getCountry() << endl << endl;
        }      
        return ptr;
    }
    else if(key < ptr -> key){
        return search(ptr -> left, key);
    }
    else{
        return search(ptr -> right, key);
    }
}

// Method for printing data in BST in ascending order
void ContactBST::printASC(Node* ptr){
    if(ptr != NULL){
        printASC(ptr->left);
        // All vector elements are printed
        for(int i = 0; i < ptr -> getData() -> getSize(); i++){
            ptr -> getData() -> at(i).printDetails();
        }
        printASC(ptr->right);
   }

}

// Method for printing data in BST in descending order
void ContactBST::printDES(Node* ptr){
    if(ptr != NULL){
        printDES(ptr->right);
        for(int i = 0; i < ptr -> getData() -> getSize(); i++){
            ptr -> getData() -> at(i).printDetails();
        }        
        printDES(ptr->left);
   }
}

// Method for printing only favourite contacts in the BST, in ascending order
void ContactBST::printFav(Node* ptr){
    if(ptr != NULL){
        printFav(ptr->left);
        // All vector elements are printed
        for(int i = 0; i < ptr -> getData() -> getSize(); i++){
            if(ptr -> getData() -> at(i).getIsFav() == true){
                ptr -> getData() -> at(i).printDetails();
            }
        }
        printFav(ptr->right);
   }
}

// Method for marking a contact as a favourite
bool ContactBST::markFav(Node* ptr, string key){
    if(ptr == NULL){
        // If key is not found, false is returned
        cout << "Key not found!" << endl;
        return false;
    }
    else if(ptr->key == key){
        string choice;
        cout << ptr -> getData() -> getSize() << " records found:" << endl;
        ptr -> getData() -> printData();

        cout << "Please select the record you want to mark as favourite: "; cin >> choice;
        if(stoi(choice)-1 >= 0 && stoi(choice) <= ptr -> getData() -> getSize() ){
            // If index is within range, proceed
            if(ptr -> getData() -> at(stoi(choice)-1).getIsFav() != true){
                // If contact is not already a favourite, proceed and make it a favourite
                ptr -> getData() -> at(stoi(choice)-1).setIsFav(true);
                // Print out a confimartion message
                cout << ptr -> getData() -> at(stoi(choice)-1).getFName() << " "
                     << ptr -> getData() -> at(stoi(choice)-1).getLName()
                     << "(" << ptr -> getData() -> at(stoi(choice)-1).getEmail() 
                     << ") has sucessfully been marked as favourite!" << endl; 
            }
            else{
                cout << "This record is already in your favourites!" << endl;
            }
        }
        else{
            cout << ("Index out of range! Make sure you enter an existing record!");
            return false;
        }
        return true;
    }
    else if(key < ptr -> key){
        return markFav(ptr -> left, key);
    }
    else{
        return markFav(ptr -> right, key);
    }
}

// Method for unmarking a contact as a favourite
bool ContactBST::unmarkFav(Node* ptr, string key){
    if(ptr == NULL){
        // If key is not found, false is returned
        cout << "Key not found!" << endl;
        return false;
    }
    else if(ptr->key == key){
        string choice;
        cout << ptr -> getData() -> getSize() << " records found:" << endl;
        ptr -> getData() -> printData();

        cout << "Please select the record you want to unmark as favourite: "; cin >> choice;
        if(stoi(choice)-1 >= 0 && stoi(choice) <= ptr -> getData() -> getSize() ){
            // If index is within range, proceed
            if(ptr -> getData() -> at(stoi(choice)-1).getIsFav() == true){
                // If contact is not already a favourite, proceed and make it a favourite
                ptr -> getData() -> at(stoi(choice)-1).setIsFav(false);
                cout << ptr -> getData() -> at(stoi(choice)-1).getFName() << " "
                     << ptr -> getData() -> at(stoi(choice)-1).getLName()
                     << "(" << ptr -> getData() -> at(stoi(choice)-1).getEmail() 
                     << ") has sucessfully been unmarked as favourite!" << endl; 
            }
            else{
                cout << "This record is not in your favourites!" << endl;
            }
        }
        else{
            throw out_of_range("Index out of range! Make sure you enter an existing record!");
        }
        return true;
    }
    else if(key < ptr -> key){
        return unmarkFav(ptr -> left, key);
    }
    else{
        return unmarkFav(ptr -> right, key);
    }
}

// Method for deleting notes from the BST (used by destructor), since the del method asks for user 
// input which would not be required for the destructor
Node* ContactBST::clean(Node *ptr, string key){
    string choice;
    // if key is not found, message is printed and process breaks 
    if(ptr == nullptr){cout << "Key not found!" << endl; return ptr;}
    else if(key > ptr -> key){ptr -> right = del(ptr -> right, key);}
    else if(key < ptr -> key){ptr -> left = del(ptr -> left, key);}
    else{ // If key is found
        if(ptr -> left == NULL && ptr -> right == NULL){
            // if it is a leaf node, delete it and return ptr
            delete ptr; ptr = NULL;
            return ptr;
        }
        else if(ptr -> left == NULL && ptr -> right != NULL){
            // if it has a right child, store it in tmp, switch the ptr and delete the tmp
            Node *tmp = ptr;
            ptr = ptr -> right;
            free(tmp);   
            return ptr;
        }

        else if(ptr -> left != NULL && ptr -> right == NULL){
            // if it has a left child, store it in tmp, switch the ptr and delete the tmp
            Node *tmp = ptr;
            ptr = ptr -> left;
            free(tmp); 
            return ptr;
        }
        else{
            // if node has both children find minimum value of right subtree
            Node* tmp = findMin(ptr -> right);
            // switch the key and vector data between the two
            ptr -> key = tmp -> key;
            ptr -> contactVector = tmp -> contactVector;
            // delete the temporary node, i.e. the minimum node of right subtree
            // as it is now at the root
            ptr -> right = del(ptr -> right, tmp -> key);
        }
    }
    return ptr;
}

// Same process as with the clean function, but takes into consideration that vector 
// might store more than one element
Node* ContactBST::del(Node *ptr, string key){
    string choice;
    if(ptr == nullptr){cout << "Key not found!" << endl; return ptr;}
    else if(key > ptr -> key){ptr -> right = del(ptr -> right, key);}
    else if(key < ptr -> key){ptr -> left = del(ptr -> left, key);}
    else{ // If key is found
        if(ptr -> left == NULL && ptr -> right == NULL){
            // if vector is not holding only one element, choose which recod to delete
            if(ptr -> getData() -> getSize() > 1){
                cout << ptr -> getData() -> getSize() << " records found:" << endl;
                ptr -> getData() -> printData();
                cout << "Please select the record you want to delete: "; cin >> choice;
                // erase the choosen record
                ptr -> getData() -> erase(stoi(choice)-1);
            }
            else{
                // if vector holds only one element, delete the node
                delete ptr; ptr = NULL;
            }
            return ptr;
        }
        else if(ptr -> left == NULL && ptr -> right != NULL){
            // if vector is not holding only, one element, choose which recod to delete
            if(ptr -> getData() -> getSize() > 1){
                cout << ptr -> getData() -> getSize() << " records found:" << endl;
                ptr -> getData() -> printData();
                cout << "Please select the record you want to delete: "; cin >> choice;
                ptr -> getData() -> erase(stoi(choice)-1);
            }
            else{
                // if vector holds only one element, delete the node
                Node *tmp = ptr;
                ptr = ptr -> right;
                free(tmp);  
            }   
            return ptr;
        }
        else if(ptr -> left != NULL && ptr -> right == NULL){
            // if vector is not holding only, one element, choose which recod to delete
            if(ptr -> getData() -> getSize() > 1){
                cout << ptr -> getData() -> getSize() << " records found:" << endl;
                ptr -> getData() -> printData();
                cout << "Please select the record you want to delete: "; cin >> choice;
                // erase the choosen record
                ptr -> getData() -> erase(stoi(choice)-1);
            }
            else{
                // if vector holds only one element, delete the node
                Node *tmp = ptr;
                ptr = ptr -> left;
                free(tmp); 
            }
            return ptr;
        }
        else{
            if(ptr -> getData() -> getSize() > 1){
                cout << ptr -> getData() -> getSize() << " records found:" << endl;
                ptr -> getData() -> printData();
                cout << "Please select the record you want to delete: "; cin >> choice;
                // erase the choosen record
                ptr -> getData() -> erase(stoi(choice)-1);
            }
            else{   
                Node* tmp = findMin(ptr -> right);
                ptr -> key = tmp -> key;
                ptr -> contactVector = tmp -> getData();
                ptr -> right = del(ptr -> right, tmp -> key);
            }
            return ptr;
        }
    }
    return ptr;
}

// method for importing data from a csv file
int ContactBST::importCSV(Node* ptr, string path){
    ifstream filein(path);

    // variables used for storing the data imported
    string fname, lname, email, phone, city, country, StrFav, space, key; bool isFav;
    int count = 0; // counter for number of records imported
    // if file is opened, i.e. it exists, proceed
    if(filein.is_open()){
        string line;
        // while there is lines to get
        while(getline(filein, line)){
            // store line in line variable
            stringstream ss(line);
            // using, as a delimiter, store data from each cell
            // as there is an empty space after each delimiter, store it in space variable
            // to ensure data does not have an empty space beforehand
            getline(ss, fname, ','); getline(ss, space, ' ');
            getline(ss, lname, ','); getline(ss, space, ' ');
            getline(ss, email, ','); getline(ss, space, ' ');
            getline(ss, phone, ','); getline(ss, space, ' ');
            getline(ss, city, ','); getline(ss, space, ' ');
            getline(ss, country, ','); getline(ss, space, ' ');
            getline(ss, StrFav, ','); isFav = stoi(StrFav);

            // create a new contact object with data from csv file
            Contact *contact = new Contact(fname, lname, email, phone, city, country, isFav);

            // create a new key for each contact
            key = fname + " " + lname;

            // increase the count of records
            count++;

            // insert the new record using the insert_helper method
            insert_helper(key, contact);
        } 
    }
    else{
        // if file is not opened, return -1
        return (-1);
    }
    return count;
}

// Method for counting the number of records in the tree
// Includes records from each vector rather than just the number of nodes
int ContactBST::count(Node* ptr){
    int j = 0;
    if(ptr == NULL){
        return 0;
    }
    else{
        for(int i = 0; i < ptr -> getData() -> getSize(); i++){
            j += 1; // count records in the vector
        }
        return j + count(ptr->left) + count(ptr->right);
    }
}

// method for exporting data to a csv file
int ContactBST::exportCSV(Node* ptr, string path){
    ofstream fileout(path, ios::app);

    // if csv file is not corrupt
    if(fileout.good()){
        // recursively export each node to the file in ascending order, using "," delimiter
        if(ptr != NULL){
        exportCSV(ptr -> left, path);
            for(int i = 0; i < ptr -> getData() -> getSize(); i++){
                fileout << ptr -> getData() -> at(i).getFName() << ", "
                     << ptr -> getData() -> at(i).getLName()
                     << ", " << ptr -> getData() -> at(i).getEmail()
                     << ", " << ptr -> getData() -> at(i).getPhone()
                     << ", " << ptr -> getData() -> at(i).getCity()
                     << ", " << ptr -> getData() -> at(i).getCountry()
                     << ", " << ptr -> getData() -> at(i).getIsFav() << endl;
                }
        exportCSV(ptr -> right, path);
        }
        // return the number of records exporeted using the count method
        return count(root);
    }
    // if file failed to open, return -1
    return (-1);
}


