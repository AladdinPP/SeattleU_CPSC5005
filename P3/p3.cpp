// AUTHOR:      Hongru He
// FILENAME:    p3.cpp
// TODO: add functional documentation (and inline comments, as necessary)
// DATE:        11/13/2023
// PURPOSE:     Allows users to input commands, make changes to the patient
//              queue, and display the information based on the triage system.
// INPUT:       Command lines and the file name
// PROCESS:     Uses PatientPriorityQueue and Patient classes to deal with
//              input commands and operate specific functions
// OUTPUT:      Add/remove/display the patient priority queue

#include "PatientPriorityQueue.h"
#include "Patient.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.
// IN:  the input line, the patient priority queue (by reference)
// MODIFY:  deal with the input line, get the possible command string
// OUT: if the input line includes valid command

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.
// IN:  the input line without command string, the patient priority queue
// MODIFY:  deal with the input line, get the possible priority code and
//          patient name, create new patient, add it into the priority queue,
// OUT: display the operation information, including error message

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.
// IN:  the patient priority queue
// MODIFY:  none
// OUT: display the first patient in the queue

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.
// IN:  the patient priority queue
// MODIFY:  remove the first patient in the queue
// OUT: display the first patient in the queue

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.
// IN:  the patient priority queue
// MODIFY:  none
// OUT: all patient information in the queue

void execCommandsFromFileCmd(string, PatientPriorityQueue &); 
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.
// IN:  the input line without command string, the patient priority queue
// MODIFY:  based on the file content, add patient to/remove patient from the
//          patient queue
// OUT: based on the file content, display specific operation information

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.
// IN:  string (by reference)
// MODIFY:  get the first substring delimited by space
// OUT: the split substring


int main() {
	// declare variables
	string line;

	// welcome message
	welcome();

	// process commands
	PatientPriorityQueue priQueue;
	do {
		cout << "\ntriage> ";
		getline(cin, line);
	} while (processLine(line, priQueue));

	// goodbye message
	goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
	// get command
	string cmd = delimitBySpace(line);
	if (cmd.length() == 0) {
		cout << "Error: no command given.";
		return false;
	}
	
	// process user input
	if (cmd == "help")
		help();
	else if (cmd == "add")
		addPatientCmd(line, priQueue);
	else if (cmd == "peek")
		peekNextCmd(priQueue);
	else if (cmd == "next")
		removePatientCmd(priQueue);
	else if (cmd == "list")
		showPatientListCmd(priQueue);
	else if (cmd == "load")
		execCommandsFromFileCmd(line, priQueue);
	else if (cmd == "quit")
		return false;
	else
		cout << "Error: unrecognized command: " << cmd << endl;

	return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) { 
	string priority, name; 

	// get priority and name
	priority = delimitBySpace(line);
	if (priority.length() == 0) {
		cout << "Error: no priority code given.\n";
		return;
	}
	name = line;
	if (name.length() == 0) {
		cout << "Error: no patient name given.\n";
		return;
	}

	// TODO: add logic to remove leading/trailing spaces
    // remove possible leading spaces
    while (name[0] == ' ')
        name.erase(0, 1);

    // remove possible trailing spaces
    while (name[name.size() - 1] == ' ')
        name.pop_back();

	// TODO: validate priority is between 1 and 4
    if (priority != "immediate" && priority != "emergency" && priority !=
    "urgent" && priority != "minimal") {
        cout << "Error: wrong priority code given.\n";
        return;
    }

	// TODO: add patient
    Patient newPatient = Patient(name, priority);
    priQueue.add(newPatient);
    cout << "Added patient \"" << name << "\" to the priority system" << endl;
}

void peekNextCmd(PatientPriorityQueue &priQueue) {
	// TODO: shows next patient to be seen
    string patient = priQueue.peek().getName();
    cout << "Highest priority patient to be called next: " << patient << endl;
}

void removePatientCmd(PatientPriorityQueue &priQueue) {
	// TODO: removes and shows next patient to be seen
    // check if there is any patients on the queue
    if (priQueue.size() == 0)
        cout << "There are no patients in the waiting area." << endl;
    else {
        string patient = priQueue.peek().getName();
        priQueue.remove();
        cout << "This patient will now be seen: " << patient << endl;
    }
}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
	cout << "# patients waiting: " << priQueue.size() << endl;
	cout << "  Arrival #   Priority Code   Patient Name\n"
		  << "+-----------+---------------+--------------+\n";
	// TODO: shows patient detail in heap order
    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
	ifstream infile;
	string line;

	// open and read from file
	infile.open(filename);
	if (infile) {
		while (getline(infile, line)) {
			cout << "\ntriage> " << line;
			// process file input 
			processLine(line, priQueue);
		} 
	} else {
		cout << "Error: could not open file.\n";
	}
	// close file
	infile.close();
}

string delimitBySpace(string &s) {
	const char SPACE = ' ';
    size_t pos = 0;
	string result = ""; 

	pos = s.find(SPACE);
	if (pos == string::npos)
        return s;

    result = s.substr(0, pos);
    s.erase(0, pos + 1);
	return result;
}

void welcome() {
	// TODO
    cout << "Welcome to the hospital triage system.\n";
}

void goodbye() {
	// TODO
    cout << "\nThank you for using the hospital triage system!\n";
}	

void help() {
	cout << "add <priority-code> <patient-name>\n"
<< "            Adds the patient to the triage system.\n"
<< "            <priority-code> must be one of the 4 accepted priority codes:\n"
<< "                1. immediate 2. emergency 3. urgent 4. minimal\n"
<< "            <patient-name>: patient's full legal name (may contain spaces)\n"
<< "next        Announces the patient to be seen next. Takes into account the\n"
<< "            type of emergency and the patient's arrival order.\n"
<< "peek        Displays the patient that is next in line, but keeps in queue\n"
<< "list        Displays the list of all patients that are still waiting\n"
<< "            in the order that they have arrived.\n"
<< "load <file> Reads the file and executes the command on each line\n"
<< "help        Displays this menu\n"
<< "quit        Exits the program\n";
}
