#ifndef QUIZ_H
#define QUIZ_H
#include "studentList.h"


#include <string>
#include <vector>
#include <list>
using namespace std;



struct Question
{
    int id;
    string question;
    string options[4];
    char correctAnswer;
    int points;


};

class QuizManager
{

private:

    vector<Question> questions;


public:


    bool loadQuestions(const string& filename);
    void beginQuiz(StudentList& list, StudentList& backupList, QuizManager& quizList, const string& studentID);

};

#endif