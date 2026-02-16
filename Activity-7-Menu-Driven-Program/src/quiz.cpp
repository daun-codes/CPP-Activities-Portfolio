#include "studentList.h"
#include "quiz.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
using namespace std;


void registerStudent(StudentList& list, StudentList& backupList, QuizManager& quizList);



bool QuizManager::loadQuestions(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "\nFailed to open Quiz File: " << filename << endl;
        return false;
    }

    string line;

    // Skip header
    if (!getline(file, line))
    {
        file.close();
        return false;
    }

    int loadCount = 0;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        istringstream iss(line);
        string idStr, question, optA, optB, optC, optD, correct, pointStr;

        if (getline(iss, idStr, ',') &&
            getline(iss, question, ',') &&
            getline(iss, optA, ',') &&
            getline(iss, optB, ',') &&
            getline(iss, optC, ',') &&
            getline(iss, optD, ',') &&
            getline(iss, correct, ',') &&
            getline(iss, pointStr, ','))
        {
            try
            {
                if (correct.empty()) continue;

                Question q;
                q.id = stoi(idStr);
                q.question = question;
                q.options[0] = optA;
                q.options[1] = optB;
                q.options[2] = optC;
                q.options[3] = optD;
                q.correctAnswer = toupper(correct[0]);
                q.points = stoi(pointStr);

                questions.push_back(q);
                loadCount++;
            }
            catch (...)
            {
                continue;
            }
        }
    }

    file.close();
    return loadCount > 0;
}

void QuizManager::beginQuiz(StudentList& list, StudentList& backupList, QuizManager& quizList, const string& studentID)
{


    if (questions.empty())
    {
        cout << "\n" << "No Questions Loaded!" << endl;
        return;

    }


    Student* currentStudent = nullptr;
    for (auto& student : list.getStudents())
    {
        if (student.id == studentID)
        {
            currentStudent = &student;
            break;
        }
    }


    if (currentStudent == nullptr && studentID != "new")
    {
        cout << "\n" << "Student ID not found. Please create a new profile first..." << endl;
        registerStudent(list, backupList, quizList);
        list.saveToFile("../data/studentInfo.csv");
        backupList.saveToBackup("../data/backupInfo.csv");


        if (!list.getStudents().empty())
        {
            currentStudent = &list.getStudents().back();

        }
    }


    int totalScore = 0;
    int totalPossible = 0;


    cout << "\n" << "QUIZ STARTED!" << "\n";
    cout << string(35, '-') << endl;


    for (const auto& q : questions)
    {
        cout << "\nQuestion " << q.id << ": " << q.question << endl;
        cout << "A. " << q.options[0] << endl;
        cout << "B. " << q.options[1] << endl;
        cout << "C. " << q.options[2] << endl;
        cout << "D. " << q.options[3] << endl;

        char answer;

        cout << "\nYour Answer (A/B/C/D): ";
        cin >> answer;
        answer = toupper(answer);


        totalPossible += q.points;

        if (answer == q.correctAnswer)
        {
            totalScore += q.points;
            cout << "\n" << "Correct! +" << q.points << " points" << endl;
        }

        else
        {
            cout << "\n" << "Incorrect! The Correct Answer is: " << q.correctAnswer << endl;

        }

        clearScreen();
    }


    cout << "\n" << string(40, '=') << endl;
    cout << "\n" << "FINAL SCORE: " << totalScore << "/" << totalPossible << endl;

    double percentage = (totalScore * 100.0) / totalPossible;
    cout << "\n" << "PERCENTAGE: " << percentage << "%" << endl;


    if (currentStudent)
    {
        currentStudent->score = totalScore;
        currentStudent->attempts++;


        if (percentage >= 90) currentStudent->rank = 1;
        else if (percentage >= 75) currentStudent->rank = 2;
        else if (percentage >= 60) currentStudent->rank = 3;
        else currentStudent->rank = 4;

    }

    if (percentage >= 90) cout << "RANK: Excellent!" << endl;
    else if (percentage >= 75) cout << "RANK: Very Good!" << endl;
    else if (percentage >= 60) cout << "RANK: Good!" << endl;
    else  cout << "RANK: Needs Improvement" << endl;


    for (auto& bStudent : backupList.getBackupStudents())
    {
        if (bStudent.id == currentStudent->id)
        {
            bStudent.score = currentStudent->score;
            bStudent.attempts = currentStudent->attempts;
            bStudent.rank = currentStudent->rank;
            break;
        }
    }


    list.saveToFile("../data/studentInfo.csv");
    backupList.saveToBackup("../data/backupInfo.csv");

    cout << "\nQuiz results saved!" << endl;


}

