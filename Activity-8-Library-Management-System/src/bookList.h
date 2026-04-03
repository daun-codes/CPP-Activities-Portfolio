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

    size_t size() const;


    // Save Function

    void LoadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);

    // Display Books Function
    bool printBook(std::string userInput);
    void viewAllBooks(const int page, const int pageSize, char& choice, std::string option);

    void findMaxLengthString(int& max_id_len, int& max_title_len, int& max_author_len, int& max_category_len, int& max_publisher_len, int& max_yearPub_len, int& max_totalCopy_len, int& max_availCopy_len, int& max_borrowCopy_len, int start, int end);

    void deleteThisBook();


};


#endif