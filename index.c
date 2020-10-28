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
	if (!myfile) {
		cout << "No index detected. Currently making index.\n";9
	}
	fopen("anime_index.txt");
	else {
		string entry;
		cout << "Please put in an anime entry into the list:\n";
		cin >> entry;
		cout >> "Adding Entry...\n";
		myfile << entry;
		cout >> "Entry Added.\n";
	}
}

int main() {
	intro();
  int choice_num;
  cin >> choice_num;
	switch(choice_num) {
		case 1:
			add_list();
		case 2:
			search_list();
		case 3:
			cout << "Closing.";
			EXIT_SUCCESS;
		default:
			cout << "Invalid input.\n";
	}
}
