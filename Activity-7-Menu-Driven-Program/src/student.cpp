#include "student.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;



// THIS IS FOR INITIAL CONSTRUCTOR 

Student::Student(string id, string firstName, string lastName, string dateCreated, string status, int score, int attempts, int rank, int credits)
    : id(id), firstName(firstName), lastName(lastName), dateCreated(dateCreated), status(status), score(score), attempts(attempts), rank(rank), credits(credits)
{

    dateDeleted = ""; // default value
}


// THIS IS FOR BACKUP CONSTRUCTOR

Student::Student(string id, string firstName, string lastName, string dateCreated, string dateDeleted, string status, int score, int attempts, int rank, int credits)
    :id(id), firstName(firstName), lastName(lastName), dateCreated(dateCreated), dateDeleted(dateDeleted), status(status), score(score), attempts(attempts), rank(rank), credits(credits)
{

}



// THIS IS FOR DISPLAYING THE SELECTED STUDENT

void Student::displayInfo() const
{
    cout << "\n--- Student Information ---\n";
    cout << left << setw(14) << "Name" << " :" << firstName + " " + lastName << endl;
    cout << left << setw(14) << "ID" << " :" << id << endl;
    cout << left << setw(14) << "Score" << " :" << score << endl;
    cout << left << setw(14) << "Attempts" << " :" << attempts << endl;
    cout << left << setw(14) << "Rank" << " :" << rank << endl;
    cout << left << setw(14) << "Date Created" << " :" << dateCreated << endl;
    cout << left << setw(14) << "Credits" << " :" << credits << endl;
    cout << "----------------------------\n";
}
