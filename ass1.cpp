/****************************************************************
 * ass1.cpp -  CSCI251/851 Ass1 - Atm2017
 * Function definitions for student database
 * <Stefan Marjanovic -  sm903 - 19/03/17>
 ****************************************************************/
 
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>

using namespace std;

// ============== Constants ==========================================

//Put your consts like: filename, array sizes, etc. here.
const int cMaxRecs = 100;

// ============= User Defined types ==================================

//Put the enum status declaration here
enum Status{FT, PT};

struct StudentRecord
{
// declare struct members here
	char studentNumber[9]; // must be 8 characters.
	char lastName[20]; //max 20 characters 
	char firstName[20]; //max 20 characters 
	Status stat; //FT or PT.
	char subjectCode[4][8]; // 4 subjects of 8 characters each.
	int results[4]; 
};


// ============= Global Variables ====================================

StudentRecord gRecs[cMaxRecs];  // Student Record DB with 100 record limit. 
int gNumRecs = 0;               // Number of records in the student DB


// ============= Private Function Prototypes =========================

void PrintRecord(int i);
int SearchRecords(char CallNo[]);
void WriteFile();
char GetGrade(int Mark);

// ============= Public Function Definitions =========================

// Reads data file into array
void ReadFile()
{
	cout << "Readfile() called." <<endl; // for testing, remove this line
	
	ifstream fin; //declare filestream object
	char status[2];
	int subCounter;
	fin.open("students.txt");
	if(!fin.good()){
		cout << "Sorry could not read file" << endl;
		exit(1);
	}	
	int i = 0;
	fin >> gRecs[i].studentNumber;	
	while (!fin.eof() && i < cMaxRecs){
		fin >> gRecs[i].lastName;
		fin >> gRecs[i].firstName;
		fin >> status;
		if (strcmp(status, "PT")){
			gRecs[i].stat = FT;
			subCounter = 4;
		} else {
			gRecs[i].stat = PT;
			subCounter = 2;
		}
		for(int j = 0; j < subCounter; j++){
			fin >> gRecs[i].subjectCode[j];	
			fin >> gRecs[i].results[j];
		}		
		i++;
		gNumRecs++;
		fin >> gRecs[i].studentNumber;	
	}
	fin.close();
	cout << "There are " << gNumRecs << " records." << endl;
}

// Adds new record to the database
void AddRecord()
{
	cout << "AddRecord() called." <<endl; // for testing, remove this line
/*
	i = gNumRecs
	get data from user and put it into gRec[i]
	inc gNumRecs

*/	
	cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "\t Add Record" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	int i = gNumRecs;
	char status[2]; 
	int loop;
	
	while (true){ //detects if the user input is valid.
		cout << "student ID: ";
		cin >> gRecs[i].studentNumber;
		if (strlen(gRecs[i].studentNumber) == 8) break;
		cerr << "Student ID must be 8 characters, try again!" << endl;
	}	
// last name declaration	
	cout << "Family name: ";
	cin >> gRecs[i].lastName;
	gRecs[i].lastName[0] = toupper(gRecs[i].lastName[0]); //first letter to upper case.	
// first name declaration	
	cout << "First name: ";
	cin >> gRecs[i].firstName;
	gRecs[i].firstName[0] = toupper(gRecs[i].firstName[0]); //first letter to upper case.
// status declaration	
	cout << "Status (FT/PT): ";
	cin >> status;
	if (strcmp(status, "PT")) {
		gRecs[i].stat = FT;
		loop = 4;
	} else {
		gRecs[i].stat = PT;
		loop = 2;
	}
// subject code declaration
	cout << "Enter subjects and the Results: \n";
	for(int j = 0; j < loop; j++){
		while(true){
			cin >> gRecs[i].subjectCode[j];
			cin >> gRecs[i].results[j]; 
			// change subjectCode to upper case loop
			for (int n=0; n < strlen(gRecs[i].subjectCode[j]); n++) {	
				gRecs[i].subjectCode[j][n] = toupper(gRecs[i].subjectCode[j][n]);
				}

			if( strlen(gRecs[i].subjectCode[j]) != 7) {
				cerr << "Subjects must be 7 characters, try again!\n" << endl;		
				j--;
			}
			if (gRecs[i].results[j] > 100 || gRecs[i].results[j] < 0){
				cerr << "Results must be (0 - 100), try again!\n" << endl;
				j--;
			}
			break;
		}
	}
	gNumRecs++;	
	cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "\t" << gNumRecs << " Records are in the database" << endl;	
	cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	WriteFile();	
}


// Finds and displays specified record on screen
void SearchArray()
{

	cout << "SearchArray() called." <<endl; // for testing, remove this line
/*
	print "Enter student number: "
	read student number
	i = SearchRecords(studentNumber);
	if record not found
		print "Record not found"
	else
		PrintRecord(i)
*/
	char studentNum[9];
	studentNum[8] = 0; //null terminates the input
	cout << "Enter student number: ";
	cin >> studentNum; 
	
	char i =  SearchRecords(studentNum); 
	if (i == -1){
		cout << "Record not found" << endl;
	}
	else {
		PrintRecord(i);
	}
}

// Display all books on screen one at a time
void DisplayRecords()
{
	cout << "DisplayRecords() called." <<endl; // for testing, remove this line
/*
	for i=0 to gNumRecs
		PrintRecord(i)
        ask: "Display next record (y/n): "
        get response
        if response == 'n' break;
    }
*/
	for (int i=0; i < gNumRecs; i++)
	{
		PrintRecord(i);
		cout << "Display next record? (y/n): ";
			
		char userInput;
		cin >> userInput;
		if (userInput == 'n')
		{
			break; 
		}
	}

}


// ============= Private Function Definitions =========================

// Prints record i on screen
void PrintRecord(int i)
{ 
/*	print members of gRecs[i]	
*/
	int n; // status counter
	
	cout << "Student number: " << gRecs[i].studentNumber << "\0"<<"\n";
	cout << "First name: " << gRecs[i].firstName << "\n";
	cout << "Last name: " << gRecs[i].lastName<< "\n";

	if(gRecs[i].stat == 1){
		n=2;
		cout << "Status: " << "PT " << endl;
	}else{
		n=4;
		cout << "Status: " << "FT " << endl;
	}
	cout << "Subjects: \t";
	for(int j=0;j<n;j++){
		cout << gRecs[i].subjectCode[j]<<" ";
	}
	cout << endl;
	cout << "Results: \t";
	for(int j=0;j<n;j++){
		cout << GetGrade(gRecs[i].results[j]) <<" "<< gRecs[i].results[j] << "\t";
	}
	cout << endl; 
}

char GetGrade(int Mark){
	if(Mark<50)return 'F';
	if(Mark<65)return 'P';
	if(Mark<75)return 'C';
	if(Mark<85)return 'D';
	return 'H';
}

// Returns index of matching record or -1 if not found
int SearchRecords(char StudentNo[])
{
/*
	for i=0 to gNumRecs
		if gRecs[i] StudentNo and StudentNo are same
			return i
	return -1 // not found
*/
	for (int i =0; i < gNumRecs; i++){
		if(strncmp(gRecs[i].studentNumber, StudentNo, 8) == 0) 
		{
			return i;
		}
	}
	return -1; //not found
}

// Writes array to text data file
void WriteFile()
{
/*
	open data file
	if open no good
		print "Problem opening data file!\n";
		exit(1);
	for i=0 to gNumRecs
		write each gRecs[i] record to file
	close data file
	print gNumRecs " records saved"
*/
	ofstream fout;
	fout.open("output.txt"); // creates outfile
	if(!fout.good()){
			cout << "Problem opening data file\n";
			exit(1);
	}
	for (int i=0; i < gNumRecs; i++){
		fout << gRecs[i].studentNumber << endl;
		fout << gRecs[i].lastName << endl;
		fout << gRecs[i].firstName << endl;
		
		if (gRecs[i].stat == FT){ //if full time student 
			fout << "FT"<< endl;
			for (int j = 0; j < 4; j++){
				fout << gRecs[i].subjectCode[j] << "\t" << gRecs[i].results[j] <<endl;
			}
		}
		if (gRecs[i].stat == PT){ //if part time student
			fout << "PT" << endl;
			for (int j = 0; j < 2; j++){
				fout << gRecs[i].subjectCode[j] << "\t" << gRecs[i].results[j] <<endl;
			}
		}		
	}
	fout.close();
	cout <<  gNumRecs << " records saved.";
}

