#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;
namespace fs = boost::filesystem

/* Just a function that prints out some intro statements */
void intro(){
	cout << "Welcome to The Weeb Index.\n";
	cout << "What do you want to do today? \n";
	cout << "1. Add an entry.\n2. Display current file list.\n3. Display files in current directory.";
	cout << "\n4. Delete Entry.\n5. Change fileName.\n6. Exit\n";
}

/* Function used to organize list of anime.
	 PROB THE ONE THAT WILL CREATE THE MOST PROBLEMS ATM.
	 Using vectors to organize > write back to the file.
	 Current write_back uses sep files to check for issues. */
void organize_list(string fileName) {
	string name;
	vector<string> name_vector;

	// Reading first and then making vector + sorting it afterwards.
	ifstream myfile(fileName);
	while (getline(myfile, name)) {
		name_vector.push_back(name);
	}
	sort(name_vector.begin(), name_vector.end());

	// Writing into textfile via from vector and then closing file
	ofstream writefile(fileName);
	for (size_t i = 0; i < name_vector.size(); i++) {
		writefile << name_vector[i];
		writefile << '\n';
	}
	writefile.close();
}

/* Function that deals with adding to the list.
	 Also deals with ensuring that the list itself
	 does not have a dupe. */
void add_list(string fileName) {
	ifstream fileCheck(fileName);
	fstream myfile;
	ifstream checkfile;

	// Checking to make sure file exists.
	if (!fileCheck) {
		ofstream fileOpen(fileName);
		cout << "No index detected. Currently making index.\n";
		fileCheck.close();
		fileOpen.close();
	}

	// Asking for input
	myfile.open(fileName, std::fstream::app);
	string entry;
	string textHolder;
	cout << "Please put in an anime entry into the list:\n";
	getline(cin, entry);

	// Check for existing line or not.
	checkfile.open(fileName, std::fstream::app);
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
	organize_list(fileName);
}

/* Function that displays the list of anime names
	 added to the current created list. */
void display_list(string fileName) {
	ifstream fileCheck(fileName);
	fstream myfile;
	string name;

	// File checking here.
	if (!fileCheck) {
		ofstream fileOpen(fileName);
		cout << "No index detected. A file will be made for you.\n";
		cout << "Because this is a blank file, I will be returning you to the menu.\n";
		fileCheck.close();
		fileOpen.close();
		return;
	}

	// This prints the list out. File closes after.
	else {
		myfile.open(fileName);
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
void delete_entry(string fileName) {
	string name;
	string userChoice;
	vector<string> name_vector;
	bool token = false;

	// Reading first and then making vector: prep for deletion
	ifstream myfile(fileName);
	while (getline(myfile, name)) {
		name_vector.push_back(name);
	}
	sort(name_vector.begin(), name_vector.end());
	myfile.close();

	// While loops that handles inputs + vector + writing of file. Uses Bool to hold
	while (!token) {
		// Input
		display_list(fileName);
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
			ofstream writefile(fileName);
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

/* This function takes in a fileName as its argument and
	 essentially enforces a while loop that checks user input
	 to see if they want to change to w/e file they want to. */
string change_entry(string fileName) {
	string userInput;
	string userBool;
	bool token = true;

	// Getting Input
	while (token) {
		cout << "\nThe current file that you are working with is: " << fileName;
		cout << '\n';
	  cout << "Please enter the name of the entry you would like to change to.\n";
		getline(cin, userInput);
		cin.clear();

		// Checking whether or not user wants this file name.
		cout << "Input: " << userInput;
		cout << "\nIs this correct? Type 'yes' to lockin change.\n";
		getline(cin, userBool);
		cin.clear();
		if (userBool == "yes") {
			token = false;
		}
		else {
			cout << "Did not type yes, returning you to the beginning to file change.\n";
		}
	}
	return userInput + ".txt";
}

/* Function taken from stack overflow using the boost library to find certain
 	 file extensions.
	 Link: https://stackoverflow.com/questions/11140483/how-to-get-list-of-files-with-a-specific-extension-in-a-given-folder
*/
void display_directory_files(fs::path const & root, string const & ext)
{
    vector<fs::path> paths;
    if (fs::exists(root) && fs::is_directory(root))
    {
        for (auto const & entry : fs::recursive_directory_iterator(root))
        {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext)
                paths.emplace_back(entry.path().filename());
        }
    }
		cout << "These are all your text files in your current folder:\n";
  	for (auto i = 0; i < paths.size(); i++) {
			cout << paths[i] << endl;
		}
}

int main() {
	// Switch statements for inputs.
	bool token = true;
	auto cwdPath = fs::current_path();
	string fileName = "anime_index.txt";
	while (token) {
		string choice_num;
		int actual_num;
		bool inputCheck = false;

		// Small check to ensure that the inputs are digits vs anything else.
		while (!inputCheck) {
			intro();
			cout << "Your current file that you are working with is: " << fileName;
			cout << "\n";
			getline(cin, choice_num);
			std::stringstream convert(choice_num);
			if (convert >> actual_num && !(convert >> choice_num)) {
				inputCheck = true;
			}
			else {
				cout << "Input was not a number. Please enter only 1, 2, 3, or 4.\n";
				cout << "\n";
				cin.clear();
			}
		}

		// Switch statement that defines our integer inputs.
		// NEXT TO DO. Add a actual index system w/ user input name as well.
		switch(actual_num) {
			case 1:
				// Maybe a more flexible way to add and organize at the same time?
				add_list(fileName);
				break;
			case 2:
				display_list(fileName);
				break;
			case 3:
				display_directory_files(cwdPath, ".txt");
			case 4:
				delete_entry(fileName);
				break;
			case 5:
				fileName = change_entry(fileName);
				break;
			case 6:
				token = false;
				cout << "Exiting.\n";
				break;
			default:
				cout << "\nInvalid input. You entered a number that was not listed.\n";
				break;
			}
		cout << "\n";
	}
}
