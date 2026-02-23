// THIS IS THE STUDENTLIST CLASS FUNCTIONS

#include "studentList.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <ctime>
#include <vector>


using namespace std;



/*-----------------
    ACCESSORS
-------------------*/
const vector<Student>& StudentList::getStudents() const {
    return Students;
}

vector<Student>& StudentList::getStudents() {
    return Students;
}

Student* StudentList::findStudent(const string& id)
{
    for (auto& student : Students) // find student inside the Students vector
    {
        if (student.id == id)
        {
            return &student; // return the address of the student
        }
    }

    for (auto& student : backUpStudents) //find student inside the backUpStudents vector
    {
        if (student.id == id)
        {
            return &student;    // return the address of the student
        }
    }
    return nullptr; // return nullptr if the student is not found
}

/*-----------------
    MUTATORS
-------------------*/
// This will be used to access the specific student that can be use to display, add, delete, update the data.


const vector<Student>& StudentList::getBackupStudents() const {
    return backUpStudents;
}

vector<Student>& StudentList::getBackupStudents() {
    return backUpStudents;
}


/*--------------------
    CREATE FUNCTIONS
----------------------*/


// CREATE A NEW STUDENT FOR STUDENT LIST STUDENTS VECTOR

void StudentList::addStudent(string fn, string ln, string status, int scr, int attmpt, int rank, int crdt)
{

    ostringstream oss;
    oss << "2026" << setw(2) << setfill('0') << nextID;
    string studentID = oss.str();



    string dateCreated = getTodayDate();



    Student newStudent(studentID, fn, ln, dateCreated, status, scr, attmpt, rank, crdt);

    Students.push_back(newStudent);


    cout << "Student added with ID: " << studentID << "\n";
    cout << "Created: " << newStudent.dateCreated << endl;


    nextID++;

}

// CREATE A NEW STUDENT FOR STUDENT LIST BACKUP STUDENTS VECTOR

void StudentList::addbackupStudent(string id, string fn, string ln, string dateCreated, string dateDeleted, string status, int scr, int attmpt, int rank, int crdt)
{

    Student backupStudent(id, fn, ln, dateCreated, dateDeleted, status, scr, attmpt, rank, crdt);


    backUpStudents.push_back(backupStudent);



}

/*----------------------
    UNIQUE ID GENERATOR
------------------------*/

// This will be used to generate a unique ID for each student that will remember the last generated ID

StudentList::StudentList() : nextID(1) {}

int StudentList::extractIDNumber(const string& fullID)
{
    if (fullID.length() >= 6)
    {
        string numStr = fullID.substr(4);
        try
        {
            return stoi(numStr);
        }
        catch (...)
        {

        }
    }
    return 0;
}


/*--------------------------------
    LOAD FROM FILE SECTIONS
--------------------------------*/

// This will be used to load the data from the file
// This will be added to the memory for faster access


void StudentList::loadFromFile(const string& filename)
{
    Students.clear();

    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "\n" << "No Active Students file found: " << filename << endl;
        nextID = 1;
        return;
    }

    cout << "\n" << "Loading active students from " << filename << "..." << endl;
    string line;


    int loadedCount = 0;
    int errorCount = 0;

    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty()) continue;

        istringstream iss(line);
        string id, firstName, lastName, dateCreated, status, scoreStr, attemptsStr, rankStr, creditsStr;

        if (!(getline(iss, id, ',') &&
            getline(iss, firstName, ',') &&
            getline(iss, lastName, ',') &&
            getline(iss, dateCreated, ',') &&
            getline(iss, status, ',') &&
            getline(iss, scoreStr, ',') &&
            getline(iss, attemptsStr, ',') &&
            getline(iss, rankStr, ',') &&
            getline(iss, creditsStr, ',')))
        {
            cout << "[WARNING]: Invalid CSV format in line: " << line << endl;
            errorCount++;
            continue;
        }

        try
        {
            int score = stoi(scoreStr);
            int attempts = stoi(attemptsStr);
            int rank = stoi(rankStr);
            int credits = stoi(creditsStr);

            Student newStudent(id, firstName, lastName, dateCreated, status, score, attempts, rank, credits);

            Students.push_back(newStudent); // Add the student to the vector for faster access

            loadedCount++;

        }

        catch (const exception& e)
        {
            cout << "\n" << "[WARNING]: Invalid data in line: " << line << endl;
            errorCount++;

        }


    }
    file.close();

    updateNextID(); // Update the next ID

    cout << "\n" << "Loaded: " << loadedCount << " active students" << endl;
    if (errorCount > 0)
    {
        cout << "\n" << "Errors: " << errorCount << " lines skipped" << endl;
    }


}

// This is used to load the data from the backup file

void StudentList::loadFromBackupFile(const string& filename)
{
    backUpStudents.clear();
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "\n" << "No backup file found: " << filename << endl;
        return;
    }

    int errorCount = 0;
    int loadedCount = 0;

    string line;
    getline(file, line); // Skip header

    while (getline(file, line))
    {
        if (line.empty()) continue;


        // Parse the line
        istringstream iss(line);
        string id, firstName, lastName, dateCreated, dateDeleted, status;
        string scoreStr, attemptsStr, rankStr, creditsStr;


        // check if the line is valid
        if (getline(iss, id, ',') &&
            getline(iss, firstName, ',') &&
            getline(iss, lastName, ',') &&
            getline(iss, dateCreated, ',') &&
            getline(iss, dateDeleted, ',') &&
            getline(iss, status, ',') &&
            getline(iss, scoreStr, ',') &&
            getline(iss, attemptsStr, ',') &&
            getline(iss, rankStr, ',') &&
            getline(iss, creditsStr, ','))
        {

            try
            {
                int score = stoi(scoreStr);
                int attempts = stoi(attemptsStr);
                int rank = stoi(rankStr);
                int credits = stoi(creditsStr);

                Student backupStudent(id, firstName, lastName, dateCreated,
                    dateDeleted, status, score, attempts, rank, credits);

                backUpStudents.push_back(backupStudent);
                loadedCount++;
            }
            catch (const exception& e)
            {
                cout << "\n" << "[WARNING]: Invalid number format in line: " << line << endl;
                errorCount++;
            }
        }
        else
        {

            cout << "\n\n" << "[WARNING]: Invalid CSV format in line: " << line << endl;
            errorCount++;
        }
    }

    file.close();
    updateNextID();

    cout << "\n" << "Loaded: " << loadedCount << " backup records" << endl;
    if (errorCount > 0)
    {
        cout << "\n" << "Errors: " << errorCount << " lines skipped" << endl;
    }
}

/*----------------------------
    UPDATE FUNCTION SECTIONS
------------------------------*/
// This will be used to update the next ID

void StudentList::updateNextID()
{
    int maxID = 0;

    for (const auto& s : Students)
    {
        int idNum = extractIDNumber(s.id);
        if (idNum > maxID) maxID = idNum;
    }


    for (const auto& s : backUpStudents)
    {
        int idNum = extractIDNumber(s.id);
        if (idNum > maxID) maxID = idNum;
    }


    nextID = maxID + 1;
}




/*  --------------------------
    SAVE FUNCTIONS SECTION
-----------------------------*/

// This is used to save the data to the backup file using the backupStudents vector

void StudentList::saveToBackup(const string& filename)
{
    if (backUpStudents.empty()) return;

    bool fileExists = false;
    bool fileEmpty = true;


    // check if the file exists
    ifstream checkFile(filename);
    if (checkFile.is_open())
    {
        fileExists = true;
        fileEmpty = checkFile.peek() == ifstream::traits_type::eof();
        checkFile.close();
    }

    ofstream file(filename, ios::out); // overwrite
    if (!file)
    {
        cerr << "\nError opening backup file!\n";
        return;
    }

    // write header
    file << "ID,FirstName,LastName,DateCreated,DateDeleted,Status,Score,Attempts,Rank,Credits\n";

    // write all backup students
    for (const auto& student : backUpStudents) // use backUpStudents vector
    {
        file << student.id << ","
            << student.firstName << ","
            << student.lastName << ","
            << student.dateCreated << ","
            << student.dateDeleted << ","
            << student.status << ","
            << student.score << ","
            << student.attempts << ","
            << student.rank << ","
            << student.credits << "\n";
    }

    file.close();

}


// This will be used to save the data to the file using the Students vector


void StudentList::saveToFile(const string& filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "\n" << "Failed to open file: " << filename << endl;
        return;
    }

    file << "id,firstName,lastName,dateCreated,status,score,attempts,rank,credits\n";

    for (auto& student : Students)
    {
        file << student.id << ","
            << student.firstName << ","
            << student.lastName << ","
            << student.dateCreated << ","
            << student.status << ","
            << student.score << ","
            << student.attempts << ","
            << student.rank << ","
            << student.credits << "\n";
    }

    file.close();
    cout << "Data saved: " << Students.size() << " Active Students" << endl;
}

/* --------------------------------
     DISPLAY FUNCTIONS SECTION
-----------------------------------*/

// This will be used to display the specific student passed by the user input and return a boolean


bool StudentList::displayStudent(const string& userInput)
{

    string trimUserInput = toTitleCase(trim(userInput));

    for (const auto& student : Students)
    {
        string fullName = student.firstName + " " + student.lastName;

        if (student.id == trimUserInput || fullName == trimUserInput)
        {
            student.displayInfo(); // display the info from the student.cpp
            return true;
        }
    }

    return false;

}




// PRINT ALL ACTIVE STUDENTS

void StudentList::printList()
{
    if (Students.empty())
    {
        cout << "No active students found.\n";
        return;
    }

    cout << "ACTIVE STUDENTS LIST (" << Students.size() << ")\n";
    cout << "\n";

    for (const auto& student : Students)
    {
        cout << "ID\t\t: " << student.id << endl;
        cout << "Name\t\t: " << student.firstName << " " << student.lastName << endl;
        cout << "Score\t\t: " << student.score << endl;
        cout << "Attempts\t: " << student.attempts << endl;
        cout << "Rank\t\t: " << student.rank << endl;
        cout << "Credits\t\t: " << student.credits << endl;
        cout << "Date Created\t: " << student.dateCreated << endl;
        cout << "----------------------------------" << endl;
    }
}

/*--------------------------------
    DELETE FUNCTION SECTIONS
----------------------------------*/
// This will be used to delete the specific student and update the backup file with the status and date deleted

void StudentList::deleteProfile(StudentList& list, StudentList& backupList, const string& userInput)
{

    string trimUserInput = toTitleCase(trim(userInput));

    for (auto it = list.Students.begin(); it != list.Students.end(); )
    {
        string fullName = it->firstName + " " + it->lastName;

        if (it->id == trimUserInput || fullName == trimUserInput)
        {
            string datedeleted = getTodayDate();
            string origdateCreated = it->dateCreated;


            Student backupCopy = *it;

            backupCopy.dateDeleted = datedeleted;
            backupCopy.status = "Deleted";

            // get the index of the student and match it to the backup students vector

            for (auto& student : backupList.backUpStudents)
            {
                if (student.id == backupCopy.id)
                {
                    student = backupCopy; // copy the backupCopy to the student
                    break;
                }
            }


            // save the data to the backup file

            backupList.saveToBackup("../data/backupInfo.csv");


            // delete the student
            it = list.Students.erase(it);

            cout << "\nProfile deleted successfully!\n";
            cout << "Date Created: " << origdateCreated << "\n";
            cout << "Date Deleted: " << datedeleted << "\n";
        }

        else
        {
            ++it;
        }
    }

}

// END of Class StudentList