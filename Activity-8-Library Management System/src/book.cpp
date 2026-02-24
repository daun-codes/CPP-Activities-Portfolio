#include "book.h"
#include <iostream>
#include <vector>
#include <iomanip>


// Constructor for Backup File 
Book::Book(std::string bookID, std::string bookTitle, std::string author, std::string ISBN, std::string category, std::string publisher, std::string yearPublished, std::string status, int totalCopies, int availCopies, int borrowedCopies)
    : bookID(bookID),
    bookTitle(bookTitle),
    author(author),
    ISBN(ISBN),
    category(category),
    publisher(publisher),
    yearPublished(yearPublished),
    status(status),
    totalCopies(totalCopies),
    availCopies(availCopies),
    borrowedCopies(borrowedCopies)
{
}


// Initial Constructor for new Book that has no Status yet
Book::Book(std::string bookID, std::string bookTitle, std::string author,
    std::string ISBN, std::string category, std::string publisher,
    std::string yearPublished, std::string status,
    int totalCopies, int availCopies)
    : Book(bookID, bookTitle, author, ISBN, category, publisher,
        yearPublished, status, totalCopies, availCopies, 0) //
{
}

