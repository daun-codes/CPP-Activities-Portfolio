#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "student.h"
#include <vector>
#include <string>

class StudentList
{
private:

    std::vector<Student> Students;
    std::vector<Student> backUpStudents;
    int nextID;

    // Utility functions for student List
    // This can only be used inside the class
    int extractIDNumber(const std::string& fullID);
    void updateNextID();

public:
    StudentList();



    /*------------------------
        ACCESSOR FUNCTIONS 
    -------------------------*/
    // This will be used to access the specific student that can be use to display, add, delete, update the data.

    const std::vector<Student>& getStudents() const;  // For read-only
    std::vector<Student>& getStudents();              // For modification

    Student* findStudent(const std::string& id);


    const std::vector<Student>& getBackupStudents() const;  // For read-only
    std::vector<Student>& getBackupStudents();              // For modification


    /*------------------------
        MUTATOR FUNCTIONS
    -------------------------*/


    // Student operations
    void addStudent(std::string fn, std::string ln, std::string status, int scr, int attmpt, int rank, int crdt);

    void addbackupStudent(std::string id, std::string fn, std::string ln, std::string dateCreated, std::string dateDeleted, std::string status, int scr, int attmpt, int rank, int crdt);

    /*------------------------
        FILE OPERATIONS
    -------------------------*/


    void loadFromFile(const std::string& filename);
    void loadFromBackupFile(const std::string& filename);
    void saveToBackup(const std::string& filename);
    void saveToFile(const std::string& filename);


    /*------------------------
        DISPLAY FUNCTIONS
    -------------------------*/


    bool displayStudent(const std::string& userInput);
    void printList();


    /*------------------------
        DELETE FUNCTIONS
    -------------------------*/
    void deleteProfile(StudentList& list, StudentList& backuplist, const std::string& userInput);
};

#endif