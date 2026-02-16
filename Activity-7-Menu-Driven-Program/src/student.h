#ifndef STUDENT_H
#define STUDENT_H
#include <string>

struct Student {

    std::string id;
    std::string firstName;
    std::string lastName;
    std::string dateCreated;
    std::string dateDeleted;
    std::string status;

    int score;
    int attempts;
    int rank;
    int credits;

    Student(std::string id, std::string firstName, std::string lastName, std::string dateCreated, std::string status, int score, int attempts, int rank, int credits);


    Student(std::string id, std::string firstName, std::string lastName, std::string dateCreated, std::string dateDeleted, std::string status, int score, int attempts, int rank, int credits);


    void displayInfo() const;

};


#endif