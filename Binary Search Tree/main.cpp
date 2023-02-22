
//=================================================================================
// Name         : DS Assignment#3 
// Author       : Ajla Šačić
// Version      : 1.0
// Date Created : 01-04-2022
// Date Modified: 17-04-2022
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<string>
#include<fstream>

// Header files
//==========================================================
#include "contact.h"
#include "myvector.h"
#include "contactbst.h"
//==========================================================

void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"del <key>          :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markfv <key>       :Mark as favourite"<<endl
		<<"umarkfv <key>      :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printfv            :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}

int main(void)
{
	ContactBST myContactBST; // declaration of BST
	listCommands(); 
	string input;
	string choice;
	string key;
	bool flag = false;
	
	do
	{
		cout << ">";
		
		// if flag is false, then the user wants to edit another record
		if(flag == true){
			// edit is printed so that they know thay are editing a new records
			cout << "edit ";
			// input is parsed into different variables used as parameters
			getline(cin, input);
			stringstream sstr(input);
			choice = "edit";
			getline(sstr, key);
		}
		else{
			// otherwise, just parse the input into the variables and use them below
			getline(cin, input);
			stringstream sstr(input);
			getline(sstr, choice, ' ');
			getline(sstr, key);
		}

		if(choice == ""){
			getline(cin, input);
			stringstream sstr(input);
			getline(sstr, choice, ' ');
			getline(sstr, key);
		}

		try{
			flag = false;
			if(choice == "import"){
				cout << myContactBST.importCSV(myContactBST.getRoot(), key) << endl;
			}
			else if(choice == "export"){
				cout << myContactBST.exportCSV(myContactBST.getRoot(), key) << endl;
			}
			else if(choice == "add"){
				// variables used for storing contact details
				string fname, lname, email, phone, city, country, isStrFav, key; int isFav;
				cout << "Please enter the details of the contact: " << endl;
				cout << "First Name: "; cin >> fname;
				cout << "Last Name: "; cin >> lname;
				cout << "Email: "; cin >> email;
				cout << "Phone#: "; cin >> phone;
				cout << "City: "; cin >> city;
				cout << "Country: "; cin >> country;
				cout << "Do you want to add the contact in your favourites (y/n): "; cin >> isStrFav;
				// if they want to add the record as a favourite, they enter "y" or "Y"
				if(isStrFav == "n" || isStrFav == "N"){isFav = 0;}
				else if(isStrFav == "y" || isStrFav == "Y"){isFav = 1;}
				else{
					cout << "No such option! Contact has not been added to your favourites!" << endl;
					cout << "You can mark it as your favourite with the markfv option!" << endl;
					isFav = 0;
				}
				// new contact object is created
				Contact *contact = new Contact(fname, lname, email, phone, city, country, isFav);

				// key is created according to the name and surname
	            key = fname + " " + lname;

	            // contact is added into the BST
				myContactBST.insert_helper(key, contact); 

				// input is cleared to the program does not fail
				cin.clear(); cin.ignore();
			}
			else if(choice == "edit"){
				string cont;
				string key2 = key;
				myContactBST.update(myContactBST.getRoot(), key2);
				// If user wants to edit another contact, flag is switched to true and aove explained method is utilized
				cout << "Do you want to edit another record (y/n)?: "; cin >> cont;
				if(cont == "y" || cont == "Y"){
					flag = true;
				}
				else if(cont == "n" || cont == "N"){
					flag = false;
				}
				else{
					cout << "No such option" << endl;
					flag = false;
				}

				// input is cleared to the program does not fail
				cin.clear(); cin.ignore();
			}
			else if(choice == "del"){
				int count1 = myContactBST.count(myContactBST.getRoot());
				Node *deleted = myContactBST.del(myContactBST.getRoot(), key);
				if(myContactBST.count(myContactBST.getRoot()) < count1){
					cout << "The contact record has successfully been deleted!" << endl;
				}
			}
			else if(choice == "searchFor"){
				Node* searched = myContactBST.search(myContactBST.getRoot(), key);
			}
			else if(choice == "markfv"){
				myContactBST.markFav(myContactBST.getRoot(), key);
				cin.clear(); cin.ignore();
			}
			else if(choice == "unmarkfv"){
				myContactBST.unmarkFav(myContactBST.getRoot(), key);
				cin.clear(); cin.ignore();
			}
			else if(choice == "printASC"){
				myContactBST.printASC(myContactBST.getRoot());
			}
			else if(choice == "printDES"){
				myContactBST.printDES(myContactBST.getRoot());
			}
			else if(choice == "printfv"){
				myContactBST.printFav(myContactBST.getRoot());
			}
			else if(choice == "help"){
				listCommands();
			}
			else if(choice == "exit"){
				exit(0);
			}
			else{cout << "Invalid command!" << endl;}
		}
		catch(exception &e)
		{
			cout << "Exception: " << e.what() << endl;
		}
	}while(choice != "exit");


	return 0;
}



