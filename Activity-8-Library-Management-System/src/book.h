#ifndef BOOK_H
#define BOOK_H
#include <string>

struct Book {
    std::string bookID;
    std::string bookTitle;
    std::string author;
    std::string ISBN;
    std::string category;
    std::string publisher;
    std::string yearPublished;
    std::string status;
    int totalCopies;
    int availCopies;
    int borrowedCopies;

    // 11-parameter constructor (backup / full)
    // 10-parameter constructor delegates to 11-param constructor
    Book(std::string bookID, std::string bookTitle, std::string author,
        std::string ISBN, std::string category, std::string publisher,
        std::string yearPublished, std::string status,
        int totalCopies, int availCopies, int borrowedCopies);

    Book(std::string bookID, std::string bookTitle, std::string author,
        std::string ISBN, std::string category, std::string publisher,
        std::string yearPublished, std::string status,
        int totalCopies, int availCopies);
};

#endif