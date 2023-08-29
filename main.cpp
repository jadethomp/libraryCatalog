// Program Completed: March 2023
// Jade Thompson

#include <iostream>
#include <string>
#include <fstream>
#include "Tokenizer.h"
#include "LinkedList.h"
using namespace std;

void nextLine(Tokenizer& tkn, ifstream& fin) {
	string tmp;
	getline(fin, tmp);
	tkn.setString(tmp);
}

bool defaultValues(LinkedList& lib) {
	string currTitle, currAuthor, currGenre, placeholder;
	int currLength;
	Tokenizer tkn;

	ifstream fin;
	bool status = true;
	fin.open("libraryRecord.txt");
	if (!fin.is_open()) {
		cout << "Failed to open the file" << endl << endl;
		return false;
	}
	cout << "File is open." << endl;

	//file process loop
	while (!fin.eof()) {
		try{
			cout << "top of file loop" << endl;
			nextLine(tkn, fin);
			tkn.readLine(currTitle);
			nextLine(tkn, fin);
			tkn.readLine(currAuthor);
			nextLine(tkn, fin);
			tkn.readLine(currGenre);
			nextLine(tkn, fin);
			tkn.readInteger(currLength);
			lib.insert(currTitle, currAuthor, currGenre, currLength, 1);
			lib.size += 1;
			cout << "bottom of file loop" << endl;
		}
		catch (...){
			cout << "terminating read" << endl;
		}
	}

	if (fin.eof()) {
		fin.close();
		cout << "Default file processed." << endl << endl;
		return true;
	}
	if (!status) return false;
	return false;
}

bool processText(istream& is, LinkedList& library, bool interactive = true) {
	string line;
    string clearchoice, saveExitChoice;
	string command;
	string arg1, arg2, arg3;
	int arg2alt, arg3alt;
	Tokenizer tkn;

	while (true) { //read loop
		if (!interactive) { // (if in file loading mode)
			if (is.eof()) { // (if file is done)
				cout << "File completed!" << endl << endl;
				return true;
			}
		}
		else { cout << ">> "; }
		getline(is, line);
		tkn.setString(line);
		tkn.readWord(command);

		if (command == "exit") {
            cout << "Would you like to save? (Y/n)";
            cin >> saveExitChoice;
            if (saveExitChoice[0] == 'Y'){
                ofstream fout;
                fout.open("libraryRecord.txt"); //may need to make it clear, but someone said this is fine
                if (!fout.is_open()) {
                    cout << "Failed to open file" << endl << endl;
                    continue;
                }
                Node* tmp = library.getHead();
                for (int i = library.size; i > 0; i--) {
                    fout << tmp->name << endl << tmp->authorlastname << endl << tmp->genre << endl << tmp->length << endl;
                    tmp = tmp->next;
                }
                fout.close();
                cout << "Save successful." << endl << endl;
            }
			library.~LinkedList(); //cleans up memory
			cout << "Exiting ...." << endl;
			return false;
		}

        if (command == "load") {
			// load expects a filename .. so read one more word
			if (!tkn.readWord(arg1)) {
				cout << "Missing file name" << endl << endl;
				continue; // skip back to the top of the read loop (same with other continues in this function)
			}
			// attempts to load file
			ifstream fin;
			bool status = true;
			fin.open(arg1);
			if (fin.is_open()) {
				status = processText(fin, library, false);
			}
			else {
				cout << "Failed to open the file" << endl << endl;
			}
			fin.close();
			if (!status) return false;
		}

		if (command == "add") {
			if (!tkn.readLine(arg1)) {
				cout << "Missing book name" << endl << endl;
				continue;
			}
			arg1 = arg1.erase(0, 1);
			if (library.insert(arg1)) {
				cout << "Book added." << endl << endl;
				library.size += 1;
			}
		}

		if (command == "set") {
			Node* tmp = library.getHead();
			int counter = 1;
			int userChoice;
			if (tmp == nullptr) {
				cout << "There are no books to edit!" << endl << endl;
				continue;
			}
			if (!tkn.readWord(arg2)) {
				cout << "Missing attribute to set" << endl << endl;
				continue;
			}
			if (!tkn.readLine(arg3)) {
				cout << "Missing attribute value to set" << endl << endl;
				continue;
			}

			cout << "Which book would you like to edit?" << endl << ">> ";
			getline(is, arg1);
			cout << endl;
			arg3 = arg3.erase(0, 1);
			if (library.setStat(arg1, arg2, arg3)) {
				cout << "Attribute set." << endl << endl;
				continue;
			}
			cout << "Something went wrong. Try again." << endl << endl;
			continue;
		}

		if (command == "remove") {
			// removes a book by title
			if (!tkn.readLine(arg1)) {
				cout << "Must give book title to remove" << endl << endl;
				continue;
			}
			if (library.remove(arg1)) {
				cout << "Book removed." << endl << endl;
				library.size -= 1;
				continue;
			}
			cout << "Something went wrong..." << endl << endl;
			continue;
		}

		if (command == "display") {
			// displays all books and attributes (if they are set)
            if (library.getHead() == nullptr){
                cout << "There are no books to display!" << endl << endl;
                continue;
            }
			library.display();
			continue;
		}

		if (command == "clear") {
			// empties library
            cout << "Are you sure you want to clear the library? This cannot be undone. Input Y or N.\n>>";
            cin >> clearchoice;
            if (clearchoice == "Y") {
                if (library.clear()) {
                    cout << "Library cleared." << endl << endl;
                    continue;
                }
                cout << "Something went wrong." << endl << endl;
                continue;
            }
            else if (clearchoice == "N"){
                cout << "Clearing cancelled." << endl << endl;
                continue;
            }
		}

		if (command == "search") {
			if (!tkn.readWord(arg1)) {
				cout << "Must give attribute to search for and value of attribute." << endl << endl;
				continue;
			}
			if (!tkn.readWord(arg2)) {
				cout << "Must give attribute to search for and value of attribute." << endl << endl;
				continue;
			}
			if (library.searchByStat(arg1, arg2)) {
				continue;
			}
            else{
                cout << "Invalid stat name" << endl << endl;
                continue;
            }

			continue; //may not be necessary?
		}

        if (command == "COMMANDS"){
            cout << "Supported commands:\n\n"
                    "COMMANDS - lists all supported commands\n"
					"ABOUT - gives more information about this program (and me!)\n\n"
					"save - backs up the current catalog to the file that is loaded in by default\n"
					"exit - exits the program (without saving!)\n"
					"load <filename> - attempts to load a .txt file into the program\n"
					"add <bookTitle> - adds a book to the catalog by title\n" 
					"set <attribute> <value> <bookTitle> - sets an attribute of a particular book (author, genre, or length)\n"
					"remove <bookTitle> - removes a book from the catalog\n"
					"display - displays the full catalog\n"
					"search <attribute> <value> - displays a list of books that match the attribute value\n"
					"clear - clears the full catalog"<< endl;
        }

        if (command == "ABOUT") {
			cout << "This program serves as a CLI book catalog, equipped with the ability to store basic info about each book,"
                    "as well as to edit the list. For now, the catalog simply uses a .txt file to store the catalog between runs, and loads"
                    "from this file each time the program is run. Books are stored within the program using a linked list. The program"
                    "reads user input using a simple tokenizer. Thanks for checking it out!" << endl << endl;
        }

		if (command == "save") {
			ofstream fout;
			fout.open("libraryRecord.txt"); //may need to make it clear, but someone said this is fine
			if (!fout.is_open()) {
				cout << "Failed to open file" << endl << endl;
				continue;
			}
			Node* tmp = library.getHead();
			for (int i = library.size; i > 0; i--) {
				fout << tmp->name << endl << tmp->authorlastname << endl << tmp->genre << endl << tmp->length << endl;
				tmp = tmp->next;
			}
			fout.close();
			cout << "Save successful." << endl << endl;
			continue;
		}
	}
}

int main() {
	LinkedList library;
	defaultValues(library);
    cout << "Welcome to my personal library! This program supports several commands for editing my personal catalog of books.\n"
            "To view the commands that this program supports, input COMMANDS. To learn more about this program, input HELP." << endl;
	processText(cin, library);

	return 0;
}