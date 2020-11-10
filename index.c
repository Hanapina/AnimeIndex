#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

/* Just a function that prints out some intro statements */
void intro(){
	cout << "Welcome to my anime index. \n";
	cout << "What do you want to do today? \n";
	cout << "1. Add an anime.\n2. Display list.\n3. Delete Entry.\n4. Exit\n";
}

/* Function used to organize list of anime.
	 PROB THE ONE THAT WILL CREATE THE MOST PROBLEMS ATM.
	 Using vectors to organize > write back to the file.
	 Current write_back uses sep files to check for issues. */
void organize_list() {
	string name;
	vector<string> name_vector;

	// Reading first and then making vector.
	ifstream myfile("anime_index.txt");
	while (getline(myfile, name)) {
		name_vector.push_back(name);
	}
	sort(name_vector.begin(), name_vector.end());

	/*
	for (int j = 0; j < name_vector.size(); j++) {
		cout << name_vector.at(j) << '\n';
	}
	myfile.close();
	*/

	// Writing into textfile via from vector and then closing file
	ofstream writefile("anime_index.txt");
	for (size_t i = 0; i < name_vector.size(); i++) {
		writefile << name_vector[i];
		writefile << '\n';
	}
	writefile.close();
}

/* Function that deals with adding to the list.
	 Also deals with ensuring that the list itself
	 does not have a dupe. */
void add_list() {
	ifstream fileCheck("anime_index.txt");
	fstream myfile;
	ifstream checkfile;

	// Checking to make sure file exists.
	if (!fileCheck) {
		ofstream fileOpen("anime_index.txt");
		cout << "No index detected. Currently making index.\n";
		fileCheck.close();
		fileOpen.close();
	}

	// Asking for input
	myfile.open("anime_index.txt", std::fstream::app);
	string entry;
	string textHolder;
	cout << "Please put in an anime entry into the list:\n";
	cin.ignore();
	getline(cin, entry);

	// Check for existing line or not.
	checkfile.open("anime_index.txt", std::fstream::app);
	while (!checkfile.eof()) {
		getline(checkfile,textHolder);
		if((textHolder == entry)) {
			cout << "Entry already exists. Returning.\n";
			return;
		}
	}

	// Adding entry if success.
	cout << "\nAdding Entry...\n";
	myfile << entry;
	myfile << '\n';
	cout << "Entry Added.\n";

	// Closes Files and then organizes.
	myfile.close();
	checkfile.close();
	organize_list();
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

	// This prints the list out. File closes after.
	else {
		myfile.open("anime_index.txt");
		cout << "\nThis is your list of anime as of the moment.\n";
		while (getline(myfile, name)) {
			cout << name << endl;
		}
		myfile.close();
	}
}

/* Delete function that mainly uses a vector to hold data.
 	 Takes in user input + deletes says input from vector.
	 File is overwritten with new vector. */
void delete_entry() {
	string name;
	string userChoice;
	vector<string> name_vector;
	bool token = false;

	// Reading first and then making vector: prep for deletion
	ifstream myfile("anime_index.txt");
	while (getline(myfile, name)) {
		name_vector.push_back(name);
	}
	sort(name_vector.begin(), name_vector.end());
	myfile.close();

	// While loops that handles inputs + vector + writing of file. Uses Bool to hold
	while (!token) {
		// Input
		display_list();
		cout << "\nWhat entry do you want to delete from your list?\n";
		cin >> userChoice;
		cin.ignore();

		// If statement that handles checking if entry exists.
		// Exists = Remove from Vector -> Write to file, else > Warns user.
		// MAYBE WE CAN DO SOME CASE SENSE CHANGES LATER?
		auto position = find(name_vector.begin(), name_vector.end(), userChoice);
		if (position != name_vector.end()) {
			cout << "Deleting Entry.\n";
			token = true;
			name_vector.erase(position);
			ofstream writefile("anime_index.txt");
			for (int i = 0; i < name_vector.size(); i++) {
				writefile << name_vector[i];
				writefile << "\n";
			}
			cout << "Entry deleted.\n";
		}
		else {
			cout << "Your input does not exist in your index. Redisplaying list.\n";
			cout << "\n";
		}
	}
}

int main() {
	// Switch statements for inputs.
	bool token = true;
	while (token) {
		intro();
		string choice_num;
		int actual_num;
		bool inputCheck = false;
	  getline(cin, choice_num);
		std::stringstream convert(choice_num);

		// Small check to ensure that the inputs are digits vs anything else.
		while (!inputCheck) {
			cout << "This is your current number: " << actual_num;
			cout << "\n"; 
			if (convert >> actual_num && !(convert >> choice_num)) {
				inputCheck = true;
			}
			cout << "Input was not a number. Please enter only 1, 2, 3, or 4.\n";
			cout << "\n";
			cin.clear();
			intro();
			getline(cin, choice_num);
			std::stringstream convert(choice_num);
		}

		switch(actual_num) {
			case 1:
				// Maybe a more flexible way to add and organize at the same time?
				add_list();
				break;
			case 2:
				display_list();
				break;
			case 3:
				delete_entry();
				break;
			case 4:
				token = false;
				cout << "Exiting.\n";
				break;
			default:
				cout << "Invalid input.\n";
				break;
			}
		cout << "\n";
	}
}
