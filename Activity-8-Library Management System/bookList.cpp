#include "bookList.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;





BookList::BookList() : nextID(1) {}


int BookList::extractIDNumber(const string& fullID)
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


void BookList::updateNextID()
{
    int maxID = 0;

    for (const auto& b : Books)
    {
        int idNum = extractIDNumber(b.bookID);
        if (idNum > maxID) maxID = idNum;
    }

    nextID = maxID + 1;
}







void BookList::addBook(string title, string author, string isbn, string category, string publisher, string yearPub, int totalCopy, int availCopy)
{
    int digits = 2;

    if (nextID >= 100)
    {
        digits = 3;
    }

    if (nextID >= 1000)
    {
        digits = 4;
    }




    ostringstream oss;

    oss << "2026" << setw(digits) << setfill('0') << nextID;
    string bookID = oss.str();

    string status = "Available";


    Book newBook(bookID, title, author, isbn, category, publisher, yearPub, status, totalCopy, availCopy);


    Books.push_back(newBook);


    cout << "Book added with ID: " << bookID << "\n";

    cout << "\n" << "You have Successfully Added a Book!" << "\n\n";

    nextID++;


    updateNextID();

}



void BookList::printList()
{
    if (Books.empty())
    {
        cout << "No active Books found.\n";
        return;
    }

    cout << "ACTIVE BOOKS LIST (" << Books.size() << ")\n";
    cout << "\n";

    for (const auto& b : Books)
    {
        cout << "ID\t\t\t\t: " << b.bookID << endl;
        cout << "Book Title\t\t\t: " << b.bookTitle << endl;
        cout << "Author\t\t\t\t: " << b.author << endl;
        cout << "ISBN\t\t\t\t: " << b.ISBN << endl;
        cout << "Category\t\t\t: " << b.category << endl;
        cout << "Publisher\t\t\t: " << b.publisher << endl;
        cout << "Year Published\t\t: " << b.yearPublished << endl;
        cout << "Status\t\t\t: " << b.status << endl;
        cout << "Total Copies\t\t:\t\t " << b.totalCopies << endl;
        cout << "Available Copies\t\t: " << b.availCopies << endl;
        cout << "----------------------------------" << endl;
    }
}

