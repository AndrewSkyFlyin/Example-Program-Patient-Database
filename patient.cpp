#include <iostream>
#include "patient.h"
#include "date.h"


//Constructor set
Patient::Patient(int B_ID, const char* B_firstname, const char* B_lastname,
	Date B_bdate, int B_docID) 
{
	setID(B_ID);
	setFirstName(B_firstname);
	setLastName(B_lastname);
	setBirthDate(B_bdate);
	setPrimaryDoctorID(B_docID);
	currentCountOfProcedures = 0;
}
Patient::~Patient() {}


//Set patient ID
Patient & Patient::setID(int total_pat)  
{
	
	ID = total_pat;
	return (*this);
}


//Get patient ID
int Patient::getID()
{
	return ID;
}


//Set first name
Patient & Patient::setFirstName(const char *g)  
{
	if (strlen(g) > 14)
	{
		strncpy(firstName, g, 14);
		firstName[14] = '\0';
	}
	else
		strcpy(firstName, g);
	return (*this);
}


//Get patient first name
const char * Patient::getFirstName()
{
	return firstName;
}


//Set last name
Patient & Patient::setLastName(const char *g)  
{
	if (strlen(g) > 14)
	{
		strncpy(lastName, g, 14);
		lastName[14] = '\0';
	}
	else
		strcpy(lastName, g);
	return (*this);
}


//Get patient last name
const char* Patient::getLastName()
{
	return lastName;
}


//Set date of birth
Patient & Patient::setBirthDate(Date patient_date)
{
	birthdate = patient_date;
	return (*this);
}


//Get Birth Date
Date Patient::getBirthDate()
{
	return birthdate;
}


//Set Primary Doctor ID
Patient & Patient::setPrimaryDoctorID(int x)
{
	primaryDoctorID = x;
	return (*this);
}


//Get Primary Doctor ID
int Patient::getPrimaryDoctorID()
{
	return primaryDoctorID;
}


//tries to add a new entry to record array, returns
//true if added, false if cannot be added
bool Patient::enterProcedure(Date today, int prodID, int prodproID)
{
	if (currentCountOfProcedures > 499)
		return false;
	else
	{
		record[currentCountOfProcedures].dateOfProcedure = today;
		record[currentCountOfProcedures].procedureID = prodID;
		record[currentCountOfProcedures].procedureProviderID = prodproID;
		currentCountOfProcedures++;
		return true;
	}

}

void Patient::printAllProcedures()
{
	for (int i = 0; i < currentCountOfProcedures; i++)
	{
		cout << "---------------------------------" << endl;
		cout << "Date of procedure: " << record[i].dateOfProcedure << endl;
		cout << "Procedure ID: " << record[i].procedureID << endl;
		cout << "Procedure Provider ID: " << record[i].procedureProviderID << endl;
		cout << "---------------------------------" << endl;
	}

}

Patient &Patient::operator=(Patient right_pat)
{
	ID = right_pat.ID;
	setFirstName(right_pat.firstName);
	setLastName(right_pat.lastName);
	birthdate = right_pat.birthdate;
	primaryDoctorID = right_pat.primaryDoctorID;
	currentCountOfProcedures = right_pat.currentCountOfProcedures;
	
	for (int i = 0; i < currentCountOfProcedures; i++)
	{
		record[i].dateOfProcedure = right_pat.record[i].dateOfProcedure;
		record[i].procedureID = right_pat.record[i].procedureID;
		record[i].procedureProviderID = right_pat.record[i].procedureProviderID;

	}
	return *this;
}