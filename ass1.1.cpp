/****************************************************************
 * ass1.cpp -  CSCI251/851 Ass1 - Atm2017                       *
 * Function definitions for student database                    *
 * <Kyle Williams- 5439309 kw878, 17/03/2017>                   *
 ***************************************************************/
 
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;

// ============== Constants ==========================================

//Put your consts like: filename, array sizes, etc. here.
const int cMaxRecs = 100;
const char filePath[] = "students.txt";
//open file > filepath (bin) + fileName (students.txt) 

// ============= User Defined types ==================================

//Put the enum status declaration here
enum StructureElement {STUDENT_NUMBER, FAMILY_NAME, FIRST_NAME, STATUS, SUBJECT};

struct StudentRecord
{
// declare struct menbers here
   char studentNumber[9];
   char familyName[20];
   char firstName[20];
   char status[2];
   string subject;
   string results;
   char grade[3];
   
   //numOfSubjects is for writing to file
   unsigned int numOfSubjects;
   //currentNumOfSubjects is for adding records
   unsigned int currentNumOfSubjects;
};


// ============= Global Variables ====================================

StudentRecord gRecs[cMaxRecs];  // Student Record DB
int gNumRecs = -1;               // Number of records in the student DB
bool gDatabaseFull;

// ============= Private Function Prototypes =========================

void PrintRecord(int i);
int SearchRecords(char StudentNo[]);
void WriteFile();

void GetStudentStructureElement(int structureType, std::string line);
void PopulateField(int structureType, StudentRecord* record);
string StringToUpper(string str);
string StringToLower(string str);
// ============= Public Function Definitions =========================

// Reads data file into array
void ReadFile()
{	
    //clear console screen
	system("cls");

	if (gDatabaseFull == false)
	{
		std::fstream data;
		static std::string line;

		data.open(filePath, std::ios::in);

		if (data.is_open() == false)
		{
			cout << "Failed to read file: " << filePath << endl;
			return;
		}
		else
		{
			cout << "Successfully read file: " << filePath << endl;

			bool isStudentNumber = true;
			int lineOfStructureFile = STUDENT_NUMBER;
            //Copies one line at a time from the filePath
			while (std::getline(data, line))
			{
				if (lineOfStructureFile > STATUS)
				{
					isStudentNumber = true;

					for (unsigned int i = 0; line.length() > i; i++)
					{
						if (tolower(line[i]) >= 97 && tolower(line[i]) <= 122)
						{
							//Has Letter
							isStudentNumber = false;
						}
					}
					//If the isStudentNumber boolean is still true then it knows this is the start of a new record
					if (isStudentNumber == true)
					{
						GetStudentStructureElement(STUDENT_NUMBER, line);
						//Sets the integer to the eNUM of STUDENT_NUMBER + 1
						lineOfStructureFile = STUDENT_NUMBER + 1;
					}
					else
					{
						GetStudentStructureElement(lineOfStructureFile, line);
						lineOfStructureFile++;

						if (lineOfStructureFile > SUBJECT)
						{
							lineOfStructureFile = SUBJECT;
						}
					}
				}
				else
				{
					GetStudentStructureElement(lineOfStructureFile, line);
					lineOfStructureFile++;
				}
			}
		}
		//Closes the file 
		data.close();		
		gDatabaseFull = true;

	}
	//The file is already open. Alerting the user
	else
	{
		cout << endl;
		cout << "****  " << filePath << " has already been loaded." << "  ****" << endl;
		cout << endl;
	}
	//Displays how many records there are currently
	cout << gNumRecs + 1<< " records are in the database." << endl;									 
}

// Adds new record to the database
void AddRecord()
{
     StudentRecord newStudent;
     newStudent.numOfSubjects = 0;
     newStudent.currentNumOfSubjects = 0;
     
     
	cout << "AddRecord() called." <<endl; // for testing, remove this line
		
	cout << "Add record to database" << endl;
	cout << "----------------------" << endl;
    //Uses switch statement within the function 'PopulateField'
    PopulateField(STUDENT_NUMBER, &newStudent);
    PopulateField(FAMILY_NAME, &newStudent);
    PopulateField(FIRST_NAME, &newStudent);
    PopulateField(STATUS, &newStudent);
	
	PopulateField(SUBJECT, &newStudent);
	PopulateField(SUBJECT, &newStudent);
	//Checks if student is full time by comparing the first character with f
	if (tolower(newStudent.status[0]) == 'f')
	{
       PopulateField(SUBJECT, &newStudent);
       PopulateField(SUBJECT, &newStudent);
    }
	
	gNumRecs++;
	
	gRecs[gNumRecs] = newStudent;
	
	cout << gNumRecs + 1 << " records are in the database." << endl;
	WriteFile();
}

// Finds and displays specified record on screen
void SearchArray()
{
     char sNum[8];
     int recordIndex = 0;
    
     cout << "Enter student number: ";
     cin >> sNum;
    //Compares input to recorded student numbers to try and find a match, returning a index
     recordIndex = SearchRecords(sNum);
    //A return of -1 means no index was found, if it was found then the index will be 0 or higher
     if (recordIndex != -1)
     {
        //Prints the record of the matching student number using the index returned
        PrintRecord(recordIndex);
     }
     else
     {
         cout << "Record not found with the student number: " << sNum << endl;
     }
}

// Display all books on screen one at a time
void DisplayRecords()
{
 static char input[40];
 static bool flag = false;

	for(int i = 0; i < gNumRecs + 1; i++)
    {    
     if (input[0] == 'n')
     {
        break;         
     }          
     PrintRecord(i);   
     flag = false;
     
     //Checks if the user wants the records to keep being printed out
     while (flag == false)
     {
      cout << "Display next record (y/n): ";        
      cin >> input;
     
      if (tolower(input[0] == 'y'))
      {
         flag = true; 
      }
      else if (tolower(input[0] == 'n'))
      {
         flag = true; 
      }
      else
      {
         cout << "Please input a valid character. ('y' or 'n')" << endl;  
      }
    }
 }
}
//Added function that displays all records in database
void DisplayAllRecords()
{
     //Prints all records within the database
     for (int i = 0; i < gNumRecs + 1; i++)
     {
         PrintRecord(i);
         
     }    
}


// ============= Private Function Definitions =========================

// Prints record i on screen
void PrintRecord(int i)
{ 
     //Formatting the output 
    cout << endl; 
    cout << "Student No\t\t" << gRecs[i].studentNumber << endl;
    cout << "First Name\t\t" << gRecs[i].firstName << endl;
    cout << "Family Name\t\t" << gRecs[i].familyName << endl;
    cout << "Status\t\t\t" << gRecs[i].status << endl;
    cout << "Subjects\t" << gRecs[i].subject.c_str() << endl;
    cout << "Results\t\t" << gRecs[i].results.c_str() << endl;
    cout << "Grade\t\t" << endl;
    cout << endl;
}

// Returns index of matching record or -1 if not found
int SearchRecords(char StudentNo[])
{
    //i is the current index of the structure
    for (int i = 0; i < gNumRecs + 1; i++)
    {
        bool match = true;
        //checking if the student numbers match
        for(int j = 0; j < 8; j++)
        {
         //checks if the entered student number is the same as the student number in the current structure by comparing the characters of both
         if (gRecs[i].studentNumber[j] == StudentNo[j])
         {
          //it was a match
         }
         else
         {
          //it wasn't a match
          match = false;
          break;
         }
        }
        //checks if the numbers did indeed match
        if (match == true)
        {
         //return structure index of the record
         return i;
        }
    }
    return -1;
}

// Writes array to text data file
void WriteFile()
{
	fstream fileToSave;

	fileToSave.open("output.txt", std::ios::out); 
    
    //Makes sure the file is open before writing
	if (fileToSave.is_open() == true)
	{
		//Save everything
		int subStart = 0;
		int subEnd = 0;

		int resStart = 0;
		int resEnd = 0;
        
        //For every record within the database do this...
		for (int i = 0; i < gNumRecs + 1; i++)
		{
		    string tempSubjectSaveLine;
            string tempResultsLine;

		    string tempSubject;
		    string tempResult;

		    string results;
            
            //Saving everything into the file seperated by new lines
			fileToSave << gRecs[i].studentNumber << "\n";
			fileToSave << gRecs[i].familyName << "\n";
			fileToSave << gRecs[i].firstName << "\n";
			fileToSave << gRecs[i].status << "\n";

			tempSubjectSaveLine = gRecs[i].subject.substr(1, gRecs[i].subject.length() - 1);
			tempResultsLine = gRecs[i].results.substr(1, gRecs[i].results.length() - 1);
            
			for (int s = 0; s < tempResultsLine.length(); s++)
			{
                //Checks if the character is a space or capital letter and erases it if true
				if (tempResultsLine[s] == 32 || (tempResultsLine[s] >= 65 && tempResultsLine[s] <= 90))
				{
					tempResultsLine.erase(s, 1);
				}
				else
				{
					static string a;
					a = tempResultsLine[s];
					results.append(a);
				}
				
			}
			//Variables for the start and end point for substrings
			subStart = 0;
			subEnd = 0;

			resStart = 0;
			resEnd = 0;

			for (int j = 0; j < gRecs[i].numOfSubjects; j++)
			{
				subEnd = tempSubjectSaveLine.find('\t', subStart);				
				if (subEnd != -1)
				{
					//Safe to get substring
					tempSubject = tempSubjectSaveLine.substr(subStart, subEnd - subStart);
					subStart = subEnd + 1;
				}			
				else
				{
                    
					if (j == gRecs[i].numOfSubjects - 1)
					{
						//Safe to get substring
						tempSubject = tempSubjectSaveLine.substr(subStart, tempSubjectSaveLine.length() - subStart);
					}
				}
				resEnd = results.find('\t', resStart);
				if (resEnd != -1)
				{
					//Safe to get substring
					tempResult = results.substr(resStart, resEnd - resStart);
					resStart = resEnd + 1;
				}
				else
				{

					if (j == gRecs[i].numOfSubjects - 1)
					{
						//Safe to get substring
						tempResult = results.substr(resStart, results.length() - resStart);
					}
				}

				string finalString;
				
				finalString.append(tempSubject);
				finalString.append(" ");
				finalString.append(tempResult);
				finalString.append("\n");
				fileToSave << finalString;

			}

		}
		fileToSave.close();
	}
	else
	{
		//Do nothing
		cout << "Failed to save database." << endl;
	}
}

void GetStudentStructureElement(int structureType, std::string line)
{
     //Checks what Enum is selected
     if (structureType == STUDENT_NUMBER)
     {
      gNumRecs++;
      for (unsigned int i = 0; i < line.length(); i++)
      {
       gRecs[gNumRecs].studentNumber[i] = line[i];
      }
     }
     
     if (structureType == FAMILY_NAME)
     {
      for (unsigned int i = 0; i < line.length(); i++)
      {
       gRecs[gNumRecs].familyName[i] = line[i];
      }
     }
     
     if (structureType == FIRST_NAME)
     {
      for (unsigned int i = 0; i < line.length(); i++)
      {
       gRecs[gNumRecs].firstName[i] = line[i];
      }
     }
     
     if (structureType == STATUS)
     {
      for (unsigned int i = 0; i < line.length(); i++)
      {
       gRecs[gNumRecs].status[i] = line[i];
      }
     }
     
     if (structureType == SUBJECT)
     {
      std::string tempSubject;
      std::string tempResult;
        
      int indexOfSpace = line.find(" ");
        
      tempSubject = line.substr(0, line.length() - (line.length() - indexOfSpace));
      tempResult = line.substr(indexOfSpace + 1, line.length() - indexOfSpace);
        
      gRecs[gNumRecs].subject.append("\t");     
      gRecs[gNumRecs].subject.append(tempSubject);
        
        
      gRecs[gNumRecs].results.append("\t ");
        
      int result = atoi(tempResult.c_str());
      
      //Check what grade you get for your result and print it behind the mark
      if (result >= 85)
      {
       gRecs[gNumRecs].results.append("HD  ");
      }
      else if (result >= 75)
      {
       gRecs[gNumRecs].results.append("D  ");
      }
      else if (result >= 65)
      {
       gRecs[gNumRecs].results.append("C  ");
      }
      else if (result >= 50)
      {
       gRecs[gNumRecs].results.append("P  ");
      }
      else if (result < 50)
      {
       gRecs[gNumRecs].results.append("PC  ");     
      }                     
      //Print results
      gRecs[gNumRecs].results.append(tempResult);
        
      gRecs[gNumRecs].numOfSubjects++;
     }
}

void PopulateField(int structureType, StudentRecord* record) 
{
	char input[30];

	string inputAsString;


	bool allowed = false;

	switch (structureType)
	{
	case STUDENT_NUMBER:
		while (allowed == false)
		{
			allowed = true;
			cout << "Student Number\t\t- ";
	
			cin.getline(input, 20);
			inputAsString = input;


	

            //Checks if the string length equals 8
			if (inputAsString.length() != 8)
			{
				cout << "Bad Input: The length does not equal 8" << endl;
				allowed = false;	
			}
			else
			{
				for (unsigned int i = 0; i < inputAsString.length(); i++)
				{
                    //Checks if the character is between 0 and 9
					if (inputAsString[i] - '0' <= 9 && inputAsString[i] - '0' >= 0)
					{

					}
					else
					{
						cout << "Bad Input: Please have only numbers and be a length of 8." << endl;
						allowed = false;
						break;
					}
				}
			}


		}

		inputAsString.resize(inputAsString.length() + 1);
		inputAsString[inputAsString.length()] = '\0';

		for (unsigned int i = 0; i < inputAsString.length(); i++) //Copy the input array into our structure one character at a time
		{
			record->studentNumber[i] = inputAsString[i];
		}

		break;
	case FAMILY_NAME:
		while (allowed == false)
		{

			allowed = true;
			cout << "Family Name\t\t- ";

			cin.getline(input, 20);
			inputAsString = input;
			inputAsString = StringToLower(inputAsString);
			inputAsString[0] = toupper(inputAsString[0]);
            
            //Checks if the length exceeds 20 
			if (inputAsString.length() > 20)
			{
				cout << "Bad Input: Please have letters only and keep it between 1 and 20 characters long." << endl;
				allowed = false;
			}

			
			else
			{
				for (unsigned int i = 0; i < inputAsString.length(); i++)
				{
                    //Checks if the character is a letter
					if (tolower(inputAsString[i]) <= 122 && tolower(inputAsString[i]) >= 97)
					{

					}
					else
					{
						cout << "Bad Input: Please have letters only and keep it between 1 and 20 characters long." << endl;
						allowed = false;
						break;
					}
				}
			}

		}

		inputAsString.resize(inputAsString.length() + 1);
		inputAsString[inputAsString.length()] = '\0';

		for (unsigned int i = 0; i < inputAsString.length(); i++) //Copy the input array into our structure one character at a time
		{
			record->familyName[i] = inputAsString[i];
		}


		break;
	case FIRST_NAME:

		while (allowed == false)
		{

			allowed = true;
			cout << "First Name\t\t- ";

			cin.getline(input, 20);
			inputAsString = input;
			inputAsString = StringToLower(inputAsString);
			inputAsString[0] = toupper(inputAsString[0]);
            
            //Checks if the length exceeds 20 
			if (inputAsString.length() > 20)
			{
				cout << "Bad Input: Please have letters only and keep it between 1 and 20 characters long." << endl;
				allowed = false;
			}
			else
			{    //For every character do this
				for (unsigned int i = 0; i < inputAsString.length(); i++)
				{
                    //Checks if the character is a letter
					if (tolower(inputAsString[i]) <= 122 && tolower(inputAsString[i]) >= 97)
					{

					}
					else
					{
						cout << "Bad Input: Please have letters only and keep it between 1 and 20 characters long." << endl;
						allowed = false;
						break;
					}
				}
			}
		}

		inputAsString.resize(inputAsString.length() + 1);
		inputAsString[inputAsString.length()] = '\0';

		for (unsigned int i = 0; i < inputAsString.length(); i++) //Copy the input array into our structure one character at a time
		{
			record->firstName[i] = inputAsString[i];
		}

		break;
	case STATUS:
		
		while (allowed == false)
		{
			allowed = true;
			cout << "Status\t\t\t- ";

			cin.getline(input, 20);
			inputAsString = input;
			inputAsString = StringToUpper(inputAsString);

			if (inputAsString.length() == 2)
			{

				if (tolower(inputAsString[0]) == 'p' && tolower(inputAsString[1]) == 't')
				{
					record->numOfSubjects = 2;
				}
				else if (tolower(inputAsString[0]) == 'f' && tolower(inputAsString[1]) == 't')
				{
					record->numOfSubjects = 4;
				}
				else
				{
					cout << "Bad Input: Please have either 'FT' (full-time) or 'PT' (part-time)" << endl;
					allowed = false;
				}
			}
			else
			{
				cout << "Bad Input: Length is over 2, please have either 'FT' or 'PT'" << endl;
				allowed = false;
			}
		}

		inputAsString.resize(inputAsString.length() + 1);
		inputAsString[inputAsString.length()] = '\0';
        
        //Copy the input array into our structure one character at a time
		for (unsigned int i = 0; i < inputAsString.length(); i++) 
		{
			record->status[i] = inputAsString[i];
		}

		record->currentNumOfSubjects = 1;

		break;
	case SUBJECT:


		while (allowed == false)
		{
			string subject;
			string result;



			allowed = true;
			cout << "Subject (" << record->currentNumOfSubjects << " of " << record->numOfSubjects << ")\t- ";

			cin.getline(input, 30);			
			inputAsString = input;
			inputAsString = StringToUpper(inputAsString);

			int pos = 0;
			int spaceCount = 0;
			int spaceLoc = 0;

			pos = inputAsString.find(' ', 0);
			spaceLoc = pos;
			
			//While the string has position, do this.
			while (pos != string::npos)
			{
				spaceCount++;
				pos = inputAsString.find(' ', pos+1);
			}
			//SEARCHING SUBJECT
			if (spaceCount == 1)
			{
				subject = inputAsString.substr(0, spaceLoc);
				result = inputAsString.substr(spaceLoc + 1, inputAsString.length() - spaceLoc);

				bool searchingForLetters = true;

				for (unsigned int i = 0; i < subject.length(); i++)
				{
					if (searchingForLetters == true)
					{
                        //Check if the character is a letter
						if (tolower(subject[i]) <= 122 && tolower(subject[i]) >= 97)
						{

						}
						else
						{
							cout << "Bad Input: Please type in the subject code with 4 letters, followed by 3 numbers. E.g. 'MATH123' and then the mark you got seperated by a space" << endl;
							allowed = false;
							break;
						}
						if (i == 3)
						{
							searchingForLetters = false;
						}
					}
					else
					{
                        //Check if the character is a number
						if (subject[i] - '0' <= 9 && subject[i] - '0' >= 0)
						{

						}
						else
						{
							cout << "Bad Input: Please type in the subject code with 4 letters, followed by 3 numbers. E.g. 'MATH123' and then the mark you got seperated by a space" << endl;
							allowed = false;
							break;
						}
					}
				}

        
				for (unsigned int i = 0; i < result.length(); i++)
				{
                    //Check if the character is a number
					if (result[i] - '0' <= 9 && result[i] - '0' >= 0)
					{

					}
					else
					{
						cout << "Bad Input: Subject code 4 letters, 3 numbers, then a space and then type in the mark you got between 0 and 100" << endl;
						allowed = false;
						break;
					}
				}
			}
			else
			{
				cout << "Bad Input" << endl;
				allowed = false;
			}

			if (allowed == true)
			{
                //Produces grade for result
				record->results.append("\t ");
				int resultAsInt = atoi(result.c_str());
				if (resultAsInt < 50)
				{
					record->results.append("PC  ");
				}
				else if (resultAsInt < 65)
				{
					record->results.append("P  ");
				}
				else if (resultAsInt < 75)
				{
					record->results.append("C  ");
				}
				else if (resultAsInt < 85)
				{
					record->results.append("D  ");
				}
				else
				{
					record->results.append("HD  ");
				}


				subject = StringToUpper(subject);

				record->subject.append("\t");
				record->subject.append(subject);

				
				record->results.append(result);

				record->currentNumOfSubjects++;
			}
		}
		break;
	}
}
//Changes all characters within a string to uppercase
string StringToUpper(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
        //changes every character within the string to uppercase
		str[i] = toupper(str[i]);
	}

	return str;
}
//Changes all characters within a string to lowercase
string StringToLower(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
        //changes every character within the string to lowercase
		str[i] = tolower(str[i]);
	}

	return str;
}
