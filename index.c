#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/* Just a function that prints out some intro statements */
void intro(){
	cout << "Welcome to my anime index. \n";
	cout << "What do you want to do today? \n";
	cout << "1. Add an anime.\n2. Display list.\n3. Exit.\n";
}

/* Function used to organize list of anime.
	 PROB THE ONE THAT WILL CREATE THE MOST PROBLEMS ATM.
	 Using vectors to organize > write back to the file.
	 Current write_back uses sep files to check for issues. */
void organize_list() {
	fstream myfile;
	//ifstream fileCheck("anime_index.txt");
	string name;
	vector<string> name_vector;
	// Same file check > exit if file does not exist.
	/*
	if (!fileCheck) {
		myfile.open("anime_index.txt");
		cout << "No index detected. A file will be made for you.\n";
		cout << "Because this is a blank file, I will be returning you to the menu.\n";
		myfile.close();
		return;
	}
	*/
	myfile.open("anime_index.txt");
	// Pushing into vector and then using sort to organize.
	while (getline(myfile, name)) {
		name_vector.push_back(name);
	}
	sort(name_vector.begin(), name_vector.end());
	// Testfile created + written into it via from vector
	for (size_t i = 0; i < name_vector.size(); i++) {
		myfile << name_vector[i] << endl;
	}
	// Closing both files.
	myfile.close();
	return;
}

/* Function that deals with adding to the list.
	 Also deals with ensuring that the list itself
	 does not have a dupe. */
void add_list() {
	ifstream fileCheck("anime_index.txt");
	fstream myfile;
	// Checking to make sure file exists.
	if (!fileCheck) {
		ofstream fileOpen("anime_index.txt");
		cout << "No index detected. Currently making index.\n";
		fileCheck.close();
		fileOpen.close();
	}
	else {
		myfile.open("anime_index.txt");
		string entry;
		string textHolder;
		cout << "Please put in an anime entry into the list:\n";
		cin >> entry;
		// Check for existing line or not.
		while (getline(myfile, textHolder)) {
			if (textHolder.find(entry) != std::string::npos) {
				cout << "This entry already exists. Returning to menu.";
				myfile.close();
				return;
			}
		}
		// Adding entry if success.
		cout << "Adding Entry...\n";
		myfile << entry << endl;
		cout << "Entry Added.\n";
	}
	organize_list();
	// Closing file
	myfile.close();
	return;
}

/* Function that displays the list of anime names
	 added to the current created list. */
void display_list() {
	ifstream fileCheck("anime_index.txt");
	fstream myfile;
	string name;
	// File checking here.
	if (!fileCheck) {
		ofstream fileOpen("anime_index.txt");
		cout << "No index detected. A file will be made for you.\n";
		cout << "Because this is a blank file, I will be returning you to the menu.\n";
		fileCheck.close();
		fileOpen.close();
		return;
	}
	// This prints the list out.
	else {
		myfile.open("anime_index.txt");
		cout << "This is your list of anime as of the moment.\n";
		while (getline(myfile, name)) {
			cout << name << endl;
		}
		// Closing file.
		myfile.close();
	}
	return;
}

int main() {
	// Switch statements for inputs.
	bool token = true;
	while (token) {
		intro();
		int choice_num;
	  cin >> choice_num;
		switch(choice_num) {
			case 1:
				// Maybe a more flexible way to add and organize at the same time?
				add_list();
				break;
			case 2:
				display_list();
				break;
			case 3:
				token = false;
				cout << "Exiting.\n";
				break;
			default:
				cout << "Invalid input.\n";
			}
		cout << "\n";
	}
}
