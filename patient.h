#pragma once
#include "date.h"


const Date clean;

struct procedure
{
    Date dateOfProcedure;
	int procedureID;
	int procedureProviderID;
};

class Patient
{

public:
	
Patient ( int = -1, const char * = "blank", const char * = "blank" , Date = clean, int = -1); //Put in default values 
									// just as in Date class
									//Use the set functions so input values are checked  
	~Patient();
	Patient & setID (int x);
	Patient & setFirstName (const char *); //check if length of name string is < 
											// 15, if not, shorten to 14 letters.
	Patient & setLastName (const char *);  //check if length of name string is < 
											// 15, if not, shorten to 14 letters.
	Patient & setBirthDate (Date);
	Patient & setPrimaryDoctorID (int);

	int getID();
	const char * getFirstName();
	const char * getLastName();
	Date getBirthDate();
	int getPrimaryDoctorID();

	bool enterProcedure(Date procedureDate, int procedureID, 
	int procedureProviderID);//tries to add a new entry to record array, returns
	void printAllProcedures();//true if added, false if cannot be added
	Patient &operator=(Patient right_pat);

private:

	int ID;
	char firstName[15];
	char lastName [15];
	Date  birthdate;
	int primaryDoctorID;  
	procedure record[500];
	int currentCountOfProcedures;  // keeps track of how many procedures have
								   //been recorded.  if it reaches 500, no new procedures can
								   //be entered.

};

