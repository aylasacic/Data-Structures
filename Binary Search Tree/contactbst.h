#ifndef ContactBST_H
#define ContactBST_H

#include<iostream>
#include "contact.h"
#include "myvector.h"

using namespace std;

class Node
{
	private:
		string key;
		MyVector<Contact>* contactVector;
		Node* left;
		Node* right;
	public:
        Node();
		Node(string key, MyVector<Contact>* contactVector);
		~Node();
		string getKey() { return this->key;}
		MyVector<Contact>* getData() { return this->contactVector;}
		friend class ContactBST;
};

//=============================================================================
class ContactBST
{
	private:
		Node* root;
	public:
		ContactBST();									    // Constructor
		~ContactBST();									    // Cestructor
		Node* getRoot();						            // Returns the root of the Tree
		Node* add(Node* root, string key, Contact* data);	// Add key into tree/subtree with root ptr
		Node* update(Node* ptr, string key);                // Edit the node with key
		Node* del(Node* ptr,string key);		            // Delete a node with key from the tree/subtree with root
		Node* search(Node* ptr,string key);	                // Find and returns the node with key
		bool markFav(Node* ptr, string key);                // Mark a contact as favorite
		bool unmarkFav(Node* ptr, string key);              // Unmark a contact as favorite
		void printASC(Node* ptr);			                // Print the data at nodes in an ascending order
		void printDES(Node* ptr);			                // Print the data at nodes in a descending order
		void printFav(Node* ptr);                           // Print the favorite data at nodes in an ascending order
		int importCSV(Node* ptr, string path);              // Load all the contacts from the CSV file to the BST
		int exportCSV(Node* ptr, string path);              // Export all the contacts from the BST to a CSV file in an ascending order
        Node* findMin(Node* ptr);
        Node* findMax(Node* ptr);
        Node* findKey(Node* ptr, string key);
        int getSize();
        int count(Node* ptr);
        int height(Node *ptr);				    			//Find the height of a tree/subtree with root ptr
        Node* clean(Node* ptr,string key);					// Method same as del, but without user input, exaplined in cpp file

	public:	//helper methods
		void insert_helper(string key, Contact* data);				//Helper method for insert method
		void remove_helper(string key);								//Helper method for remove method
	};

#endif
