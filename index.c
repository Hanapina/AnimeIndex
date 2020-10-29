#include <stdio.h>
#include <string,h>
#include <iostream>
#include <fstream>
using namespace std;

void intro{
	cout << "Welcome to my anime index. \n";
	cout << "What do you want to do today? \n";
	cout << "1. Add an anime\n2. Search through list\n3. Exit\n";
}

void add_list() {
	fstream myfile;
	fopen("anime_index.txt");
	if (!myfile) {
		cout << "No index detected. Currently making index.\n";9
	}
	else {
		string entry;
		cout << "Please put in an anime entry into the list:\n";
		cin >> entry;
		while (getline("anime_index.txt", entry)) {
			if (entry.find(entry) != std::string::npos) {
				cout >> "This entry already exists. Returning to menu."
				fclose("anime_index.txt");
				return;
			}
		}
		cout >> "Adding Entry...\n";
		myfile << entry;
		cout >> "Entry Added.\n";
	}
}

void search_list() {
	fstream myfile;
	string name;
	fopen("anime_index.txt");
	if (!myfile) {
		cout << "No index detected. An index can be created through option 1
		of this program.\n";
		return;
	}
	else {
		cout << "This is your list of anime as of the moment.\n";
		while (getline(myfile, name)) {
			cout << name << endl;
		}
	}
}

int main() {
	intro();
  int choice_num;
  cin >> choice_num;
	switch(choice_num) {
		case 1:
			add_list();
			//organize_list();
		case 2:
			search_list();
		case 3:
			cout << "Closing.";
			EXIT_SUCCESS;
		default:
			cout << "Invalid input.\n";
	}
}
