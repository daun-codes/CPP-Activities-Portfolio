// Activity 7: Student Management System
// This is the main file for the student management system
// Features:

// 1. The program can allow user to register a new student profile.
// 2. The user can also delete a student profile.
// 3. The user must have to provide the assigned user ID to play the quiz
// 4. The data that was saved in the file will be loaded in the program.
// 5. The program will save the data when the user exits the program.
// 6. The program will automatically save or make a copy of the data when the user wants to delete a student profile or register a new student profile.
// 7. The programm will add points and attempts to the student profile when the user answers a question correctly.


// Improvements:


// 1. The UI can be improved by adding a loading bar or a progress bar to show the user the progress of the program.
// 2. I will be adding a feature to the program where the user can view the rank of the students accurately based on their score.
// 3. Validation for credits points can be added to the program. That will or not allow the user to play the quiz if they don't have enough credits points.






#include "studentList.h"
#include "quiz.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;



// MAIN FUNCTIONS prototype 
// This is the prototype of the main functions


void startquiz(StudentList& list, StudentList& backupList, QuizManager& quizList);
void registerStudent(StudentList& list, StudentList& backupList, QuizManager& quizList);
void displayStudents(StudentList& list, StudentList& backupList);
void deleteStudent(StudentList& list, StudentList& backupList, string userInput);
void displayCurrentStudent(StudentList& list, StudentList& backuplist);

int main() {

    StudentList list; // created an object of the StudentList class
    StudentList backupList; // created an object of the StudentList class
    QuizManager quizList; // created an object of the QuizManager class

    int choice;


    // Load the data from the files
    quizList.loadQuestions("../data/quiz_question.csv");
    list.loadFromFile("../data/studentInfo.csv");
    backupList.loadFromBackupFile("../data/backupInfo.csv");



    do
    {
        clearScreen();

        cout << "Welcome to Student Management System!" << "\n\n";

        cout << "MENU OPTIONS\n\n";

        cout << "[1] Start Quiz" << "\n";
        cout << "[2] View High Score" << "\n";
        cout << "[3] View Instructions" << "\n";
        cout << "[4] View Profile" << "\n";
        cout << "[0] Exit" << "\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Response. Enter a number: ";

        }

        switch (choice)
        {
        case 1:
            cout << "\n" << "You have selected 'Start the Quiz'" << "\n";
            startquiz(list, backupList, quizList);
            break;
        case 2:
            cout << "\n" << "You have selected 'View High Scores'" << "\n";
            list.loadFromFile("../data/studentInfo.csv");
            displayStudents(list, backupList);
            break;
        case 3:
            cout << "\n" << "You have selected 'View Instructions'" << "\n";
            break;
        case 4:
            cout << "\n" << "You have selected 'View Profile'" << "\n";
            displayCurrentStudent(list, backupList);
            break;
        case 0:
            cout << "\n" << "Thanks for playing! Goodbye!" << "\n";
            break;

        default:
            cout << "\n" << "Invalid choice. Please try again.\n";
            break;
        }

        if (choice != 0) {

            cout << "\nPress Enter to return to Menu...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    return 0;
}


// CREATE A NEW STUDENT FUNCTIONS

void registerStudent(StudentList& list, StudentList& backupList, QuizManager& quizList)
{
    string firstName, lastName;
    string status = "Active";
    int credits = 100;
    int score = 0;
    int rank = 0;
    int attempt = 0;



    // get user input with validation
    bool valid = false; // This is for Input validation
    cout << "\n\n" << "[REGISTRATION FORM!]" << "\n\n";
    while (!valid)
    {
        cout << "Enter your First Name: ";
        getline(cin, firstName);
        cout << "Enter your last Name: ";
        getline(cin, lastName);

        if (firstName.empty() || lastName.empty())
        {
            cout << "\n" << "Name cannot be empty. Please try again.\n\n";
        }
        else
        {
            valid = true; // Success!
        }
    }

    cout << "\n\n" << "Great! You have successfully created your account!\n\n";


    string fname = toTitleCase(trim(firstName));
    string lname = toTitleCase(trim(lastName));



    list.addStudent(fname, lname, status, score, attempt, rank, credits);


    string newID = list.getStudents().back().id;
    string newDC = list.getStudents().back().dateCreated;
    string newDD = "";


    // add the new student to the backup list
    
    backupList.addbackupStudent(newID, fname, lname, newDC, newDD, status, score, attempt, rank, credits);

}


// INITIALIZE THE QUIZ FUNCTION 

void startquiz(StudentList& list, StudentList& backupList, QuizManager& quizList)
{

    clearScreen();

    char choice;


    cout << "\n" << "Do you already have a Profile? (y)/(n): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string studentID;
    if (choice == 'y' || choice == 'Y')
    {
        cout << "\n" << "Great! Just please enter your student ID: ";
        cin >> studentID;
        quizList.beginQuiz(list, backupList, quizList, studentID);

    }
    else
    {
        cout << "\n" << "Please Register First..." << endl;
        registerStudent(list, backupList, quizList);
        list.saveToFile("../data/studentInfo.csv");
        backupList.saveToBackup("../data/backupInfo.csv");

    }


    return;


}



// DISPLAY ALL STUDENTS


void displayStudents(StudentList& list, StudentList& backupList)
{
    clearScreen();

    list.printList();

}




// DISPLAY THE CURRENT STUDENT PROFILE


void displayCurrentStudent(StudentList& list, StudentList& backupList) // pass the list by reference
{
    clearScreen();

    cout << "\n-----------------------" << "\n";
    cout << " STUDENT PROFILE LOCATOR " << "\n";
    cout << "-------------------------";

    cout << "\n";

    string userInput;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n\n" << "Enter the user ID or the Full Name of the student: ";
    getline(cin, userInput);

    bool found = list.displayStudent(userInput);

    string border(20, '-');
    int choice;

    if (!found)
    {
        cout << "\n" << "Student not found: " << userInput << endl;
    }

    else
    {
        cout << "\n\n";
        cout << border << "\t\t\t" << border << "---\n";
        cout << "|" << "[1] Use this Profile" << "|" << "\t\t" << "\t" << "|[0] Delete this Profile" << "|" << "\n";
        cout << border << "\t\t\t" << border << "---"
            << endl;
        cout << "\n\n" << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\n\n" << "You are going to take the exam now!" << endl;

        }
        else if (choice == 0)
        {
            deleteStudent(list, backupList, userInput);
        }
        else
        {
            cout << "\n\n" << "[NOTE]: Invalid Input!" << endl;
        }
    }


}


// DELETE A STUDENT PROFILE


void deleteStudent(StudentList& list, StudentList& backupList, string userInput)
{
    clearScreen();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char confirm;

    cout << "\n-------------------" << "\n";
    cout << "PROFILE TO DELETE " << "\n";
    cout << "---------------------";

    cout << "\n";

    list.displayStudent(userInput);

    cout << "Do you wish to proceed? (y)/(n): ";
    cin >> confirm;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y')
    {
        list.deleteProfile(list, backupList, userInput);

    }
    else
    {
        cout << "\n\n" << "Deletion cancelled." << endl;
        return;
    }


    list.saveToFile("../data/studentInfo.csv");

}