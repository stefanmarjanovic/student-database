/********************************************************
*    main.cpp - CSCI251/851 Ass1 - Atm2017        		*
*    Contains main + UI for student DB program    		*
*    <Stefan Marjanovic -  sm903 - 19/03/17>		    *
********************************************************/
#include <iostream>
#include <cctype>
#include <cstdio>
#include "ass1.h"
#include <string>

using namespace std;

char Menu();

int main() 
{
	// Option for redirecting input from input.txt 
	// Use this when you demo your program to your 
	// tutor as explained on page 4 of the Ass1 specs.
	char RedirectInput[20];
	cout << "Redirect input? (y/n): ";
	cin.getline(RedirectInput,20);
	if(RedirectInput[0]=='y'){ // then get input from input.txt...
		FILE *fp = freopen ("input.txt","r",stdin);    
		if(fp==NULL){cerr<<"\"input.txt\" not found!\n"; exit(1);}
	}
	
	// Main Menu loop
	bool Quit = false;
	do {
		char Cmd = Menu();
		switch(Cmd) {
			case 'r':
				ReadFile();
				break;
			case 'd':
				DisplayRecords();
				break;
			case 'a':
				AddRecord();
				break;
			case 's':
				SearchArray();
				break;
			case 'q':
				Quit = true;
				break;
			default:
			cerr << "Invalid command!\n";
		}
    } while(!Quit);

	cout << "Thank you for using the student records database" << endl;
	if(RedirectInput[0]=='y') fclose (stdin);    // close redirected input from input.txt
	return 0;
}

// Shows main menu options
char Menu() 
{
	char Cmd;
	cout << "\n*********************************"<< endl;
	cout << "*    Student Records Database   *"<< endl;
	cout << "*     (r)ead data file          *"<< endl;
	cout << "*     (d)isplay records         *"<< endl;
	cout << "*     (a)dd record to DB        *"<< endl;
	cout << "*     (s)earch records          *"<< endl;
	cout << "*     (q)uit                    *"<< endl;
	cout << "*********************************"<< endl;
	cout << "Command: ";
	cin  >> Cmd;
	cin.ignore();  // eat up '\n'
	Cmd = tolower(Cmd);
	return Cmd;
}

