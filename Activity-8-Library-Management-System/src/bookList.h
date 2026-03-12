#ifndef BOOKLIST_H
#define BOOKLIST_H
#include "book.h"
#include <string>
#include <vector>






class BookList
{

private:

    std::vector<Book> Books;
    std::vector<Book> BackupBooks;
    int nextID;


    int extractIDNumber(const std::string& fullID);
    void updateNextID();


public:

    BookList();

    void addBook(std::string title, std::string author, std::string isbn, std::string category, std::string publisher, std::string yearPub, int totalCopy, int availCopy);


    void printList();


    // Save Function

    void LoadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);





};


#endif