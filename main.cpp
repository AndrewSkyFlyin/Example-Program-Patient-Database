/*////////////////////////////////////////////////////////
Name: Andrew Nguyen
Assignment: Patient Records Database
////////////////////////////////////////////////////////*/

#include "date.h"
#include "patient.h"
#include <fstream>

using namespace std;

void display_menu();
void add_newPatient(Patient tot[20], Patient curr[10], int &total_pat, int &checked_in); //N function
void checkin_Patient(Patient y[20], Patient curr[10], int total_pat, int &checked_in); //R function
void checkout_Patient(Patient tot[20], Patient curr[10], int total_pat, int &checked_in, Date day); //O function
void search_print(Patient tot[20], int total_pat); //I function
void print_all(Patient curr[10], int checked_in); //P function
bool leave_program(Patient tot[20], int total_pat, int checked_in);  //Q function

int main()
{
	//Prerequisite variable and object declarations
	Patient all_patients[20];
	Patient currently_patients[10];

	ifstream fget;
	ofstream ftrace;

	Date today;
	
	bool exit_condition = false;
	int checked_in_number = 0;
	int Total_patients_number = 0;
	int local_day = 0;
	int local_month = 0;
	int local_year = 0;
	int condition = 0;
	char selection;
	char t;


	//For inputting today's date
	cout << "Enter today's date." << endl;
	cout << "Example: 2/25/2014" << endl;
	cin >> local_month >> t >> local_day >> t >> local_year;
	today.setDate(local_month, local_day, local_year); //sets the user inputted date
	
	
	//Reading patient information from CurrentPatients.bin
	fget.open("CurrentPatients.bin", ios::binary);
	
	if (fget.is_open())
	{
		fget.read((char*)&Total_patients_number, sizeof(int));
	
		for (int i = 0; i < Total_patients_number; i++)
		{
			fget.read((char*)&all_patients[i], sizeof(Patient));
		}
		fget.close();
	}
	else
	{
		cout << "Error. Unable to read file." << endl;
		system("pause");
		return 0;
	}
	
	cout << "Today is " << today << endl;

	///Menu
	display_menu();
	while (condition != 1)
	{
		cin >> selection;
		{
			switch (selection)
			{
			case 'N': case 'n':
				add_newPatient(all_patients, currently_patients, Total_patients_number, checked_in_number);
				break;

			case 'R': case 'r':
				checkin_Patient(all_patients, currently_patients, Total_patients_number, checked_in_number);
				break;

			case 'O': case 'o':
				checkout_Patient(all_patients, currently_patients, Total_patients_number, checked_in_number, today);
				break;

			case 'I': case 'i':
				search_print(all_patients, Total_patients_number);
				break;

			case 'P': case 'p':
				print_all(currently_patients, checked_in_number);
				break;

			case 'Q': case 'q':
				exit_condition = leave_program(all_patients, Total_patients_number, checked_in_number);
				if (exit_condition == true)
					condition = 1;
				break;

			default:
				cout << "That was not a valid input. " << endl;
				break;
			}
		}
	}

	system("pause");

	return 0;
}

void display_menu()
{
	cout << endl;
	cout << "------Patient's Records Menu Display------" << endl << endl;
	cout << "Press N to check in a new patient." << endl;
	cout << "Press R to check in a returning patient." << endl;
	cout << "Press O to check out a patient." << endl;
	cout << "Press I to search for a patient entry." << endl;
	cout << "Press P to display all currently checked in patients." << endl;
	cout << "Press Q to quit." << endl << endl;
}

void add_newPatient(Patient tot[20], Patient curr[10], int &total_pat, int &checked_in)
{
	bool placed = false;
	int ID = total_pat;
	int holder = 0;
	int month = 0;
	int day = 0;
	int year = 0;
	char firstName[15];
	char lastName[15];
	char t;
	Date  birthdate;
	int primaryDoctorID = 0;
	
	cout << "Enter first name : ";
	cin >> firstName;
	cout << "Enter last name : ";
	cin >> lastName;
	cout << "Enter patient's date of birth: ";
	cin >> month >> t >> day >> t >> year;
	cout << "Enter primary physician ID: ";
	cin >> primaryDoctorID;

	birthdate.setDate(month, day, year);

	Patient temp(ID, firstName, lastName, birthdate, primaryDoctorID);
	tot[total_pat] = temp;  //copy patient object into total array
	curr[checked_in] = temp;

	total_pat++;
	checked_in++;
	
	cout << "---------------------------------------------------" << endl;
	cout << "Profile created. Program will now return to menu." << endl;
	cout << "---------------------------------------------------" << endl << endl;
	system("pause");
	display_menu();

}

void checkin_Patient(Patient tot[20], Patient curr[10], int total_pat, int &checked_in)
{
	int ID = -1;
	int i = 0;
	int j = 0;
	int holder = 0;
	Patient temp;
	bool placed = false;
	bool already_found = false;
	bool found = false;

	cout << "Enter the returning patient's ID: ";
	cin >> ID;

	while(!already_found && i < checked_in)  //check if patient is already checked in
	{
		if (ID == curr[i].getID())
		{
			already_found = true;
		}
		else 
			i++;
	}
	
	if (!already_found) //search for patient in total patients
	{
		while (!found && j < total_pat)
		{
			if (ID == tot[j].getID())
			{
				found = true;
			}
			else
				j++;
		}
	}
	

	if (already_found)
	{
		cout << "The patient " << curr[i].getFirstName() << " "
			<< curr[i].getLastName() << " is already checked in." << endl;
	}
	else if (!found)
	{
		cout << "No match found. Returning to menu." << endl;
	}
	else if (found)
	{
		cout << "---Match found---" << endl;
		cout << "Checking in " << tot[j].getFirstName() << " " << tot[j].getLastName() << "." << endl;
		curr[checked_in] = tot[j];
		checked_in++;
	}
	
	system("pause");
	display_menu();
	return;
}

void checkout_Patient(Patient tot[20], Patient curr[10], int total_pat, int &checked_in, Date day) 
{
	bool found = false;
	bool total_found = false;
	bool update = false;
	int i = 0;
	int j = 0;
	int ID = -1;
	int prodID = 0;
	int prodproID = 0;
	
	if (checked_in == 0)
	{
		cout << "No patients are currently checked in." << endl;
		cout << "Returning to menu..." << endl;
	}

	else if (checked_in > 0)
	{
		cout << "Please enter patient's ID: ";
		cin >> ID;

		while (!found && i < checked_in)
		{
			if (ID == curr[i].getID())
			{
				found = true;
			}
			else
				i++;
		}
	}

	if (!found)
		cout << "No match found.  Returning to menu." << endl;

	else if (found)
	{
		cout << "Checking out " << curr[i].getFirstName() << " "
				<< curr[i].getLastName() << "." << endl << endl;

		cout << "Enter procedure ID: ";
		cin >> prodID;
		cout << "Enter procedure provider ID: ";
		cin >> prodproID;

		update = curr[i].enterProcedure(day, prodID, prodproID); //update patient procedures
				
		if (update == false)
			{
				cout << "--------------------------------------------------" << endl;
				cout << "Patient procedure records full, unable to update." << endl;
				cout << "--------------------------------------------------" << endl;
			}
		
		while (!total_found && j < total_pat)
		{
			if (curr[i].getID() == tot[j].getID())
			{
				tot[j] = curr[i]; //overwrite main patient object with updated object
				
				for (int move_index = i; move_index < checked_in - 1; move_index++) //move patient objects up
				{
					curr[move_index] = curr[move_index + 1];
				}
				checked_in--;

				cout << "Patient profile updated. " << endl;
				cout << "Patient checked out. Returning to menu...." << endl;
				total_found = true;
			}
			else
				j++;
		}

		if (!total_found && j == total_pat) //should never run
		{
			cout << "Error. Code is broke." << endl;
			system("pause");
		}
	}
	
	system("pause");
	display_menu();
	return;
	

}

void search_print(Patient tot[20], int total_pat)
{
	int ID = -1;
	int i = 0;
	bool found = false;

	cout << "Enter patient's ID: ";
	cin >> ID;

	
	while(!found && i < total_pat)
	{
		if (ID == tot[i].getID())
		{
			cout << "---Match found---" << endl;
			cout << "Patient: " << tot[i].getFirstName() << " " << tot[i].getLastName() << endl;
			cout << "DOB: " << tot[i].getBirthDate() << endl;
			cout << "Primary Physician ID: " << tot[i].getPrimaryDoctorID() << endl << endl;

			cout << "--Procedures--" << endl;
			tot[i].printAllProcedures();
			cout << "--End of procedures--" << endl;
			cout << "Returning to menu..." << endl;
			found = true;
		}
		else
			i++;
	}
	
	if (!found)
	{
		cout << "No match was found." << endl;
		cout << "Returning to menu..." << endl;
	}
	
	system("pause");
	display_menu();
	return;
	
}

void print_all(Patient curr[10], int checked_in)
{
	if (checked_in == 0)
	{
		cout << "No patients are currently checked in." << endl;
	}
	else
	{
		for (int i = 0; i < checked_in; i++)
		{
				cout << "-----------------------" << endl;
				cout << "Patient ID: " << curr[i].getID() << endl;
				cout << "Name: " << curr[i].getFirstName() << " " << curr[i].getLastName() << endl;
				cout << "Physician ID: " << curr[i].getPrimaryDoctorID() << endl;
				cout << "-----------------------" << endl;
		}
		cout << "End of file." << endl;
	}
	system("pause");
	display_menu();
	return;
}

bool leave_program(Patient tot[20], int total_pat, int checked_in)
{
	ofstream ftrace;
	
	if (checked_in > 0)
	{
		cout << "There are patients still checked in.  Returning to menu..." << endl;
		system("pause");
		display_menu();
		return false;
	}

	else
	{
		ftrace.open("CurrentPatients.bin", ios::binary);
		ftrace.write((char*)&total_pat, sizeof(total_pat)); //write in number of patients

		for (int i = 0; i < total_pat; i++)
		{
			ftrace.write((char*)&tot[i], sizeof(tot[i]));
		}
		ftrace.close();

		cout << "Patient data saved. Quitting." << endl;
		return true;
	}
}