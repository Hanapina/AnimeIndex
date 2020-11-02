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

/* Function that deals with adding to the list.
	 Also deals with ensuring that the list itself
	 does not have a dupe. */
void add_list() {
	fstream myfile;
	myfile.open("anime_index.txt");
	// Checking to make sure file exists.
	if (!myfile) {
		cout << "No index detected. Currently making index.\n";
	}
	else {
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
	// Closing file
	myfile.close();
	return;
}

/* Function that displays the list of anime names
	 added to the current created list. */
void display_list() {
	fstream myfile;
	string name;
	myfile.open("anime_index.txt");
	// File checking here.
	if (!myfile) {
		cout << "No index detected. A file will be made for you.\n";
		cout << "Because this is a blank file, I will be returning you to the menu.\n";
		myfile.close();
		return;
	}
	// This prints the list out.
	else {
		cout << "This is your list of anime as of the moment.\n";
		while (getline(myfile, name)) {
			cout << name << endl;
		}
	}
	// Closing file.
	myfile.close();
	return;
}

/* Function used to organize list of anime.
	 PROB THE ONE THAT WILL CREATE THE MOST PROBLEMS ATM.
	 Using vectors to organize > write back to the file.
	 Current write_back uses sep files to check for issues. */
void organize_list() {
		fstream myfile;
		fstream testfile;
		string name;
		vector<string> name_vector;
		// Same file check > exit if file does not exist.
		myfile.open("anime_index.txt");
		if (!myfile) {
			cout << "No index detected. A file will be made for you.\n";
			cout << "Because this is a blank file, I will be returning you to the menu.\n";
			myfile.close();
			return;
		}
		// Pushing into vector and then using sort to organize.
		while (getline(myfile, name)) {
			name_vector.pushback(name);
		}
		sort(name_vector.begin(), name_vector.end());
		// Testfile created + written into it via from vector
		testfile.open("test_file.txt");
		for (size_t i = 0; i < name_vector.size(); i++) {
			testfile << name_vector[i] << endl;
		}
		// Closing both files.
		myfile.close();
		testfile.close();
		return;
}

int main() {
	intro();
	// Switch statements for inputs.
  int choice_num;
  cin >> choice_num;
	switch(choice_num) {
		case 1:
			// Maybe a more flexible way to add and organize at the same time?
			add_list();
			organize_list();
		case 2:
			display_list();
		case 3:
			cout << "Closing.";
			EXIT_SUCCESS;
		default:
			cout << "Invalid input.\n";
	}
}
