#include "bookList.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;





BookList::BookList() : nextID(1) {}


int BookList::extractIDNumber(const string& fullID)
{
    if (fullID.length() >= 4)
    {
        string numStr = fullID.substr(2);
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





// This function adds a book to the list with the required parameters.

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

    oss << "BO" << setw(digits) << setfill('0') << nextID;
    string bookID = oss.str();

    string status = "Available";


    Book newBook(bookID, title, author, isbn, category, publisher, yearPub, status, totalCopy, availCopy);


    Books.push_back(newBook);


    cout << "Book added with ID: " << bookID << "\n";

    cout << "\n" << "You have Successfully Added a Book!" << "\n\n";

    nextID++;

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
        cout << "ID\t\t\t: " << b.bookID << endl;
        cout << "Book Title\t\t: " << b.bookTitle << endl;
        cout << "Author\t\t\t: " << b.author << endl;
        cout << "ISBN\t\t\t: " << b.ISBN << endl;
        cout << "Category\t\t: " << b.category << endl;
        cout << "Publisher\t\t: " << b.publisher << endl;
        cout << "Year Published\t\t: " << b.yearPublished << endl;
        cout << "Status\t\t\t: " << b.status << endl;
        cout << "Total Copies\t\t: " << b.totalCopies << endl;
        cout << "Available Copies\t: " << b.availCopies << endl;
        cout << "----------------------------------" << endl;
    }
}


void BookList::LoadFromFile(const string& filename)
{
    Books.clear();

    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "\n" << "No Active Book file found" << filename << endl;
        return;
    }

    cout << "/n" << "Loading book library from " << filename << "..." << endl;

    string line;

    int loadedCount = 0;
    int errorCount = 0;

    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty()) continue;

        istringstream iss(line);
        string bookID, bookTitle, author, ISBN, category, publisher, yearPublished, status, totalCopiesStr, availCopiesStr, borrowedCopiesStr;

        if (!(getline(iss, bookID, ',') &&
            getline(iss, bookTitle, ',') &&
            getline(iss, author, ',') &&
            getline(iss, ISBN, ',') &&
            getline(iss, category, ',') &&
            getline(iss, publisher, ',') &&
            getline(iss, yearPublished, ',') &&
            getline(iss, status, ',') &&
            getline(iss, totalCopiesStr, ',') &&
            getline(iss, availCopiesStr, ',') &&
            getline(iss, borrowedCopiesStr, ',')))

        {
            cout << "[WARNING]: Invalid CSV format in line: " << line << endl;
            errorCount++;
            continue;
        }

        try
        {
            int totalCopies = stoi(totalCopiesStr);
            int availCopies = stoi(availCopiesStr);
            int borrowedCopies = stoi(borrowedCopiesStr);


            Book newBook(bookID, bookTitle, author, ISBN, category, publisher, yearPublished, status, totalCopies, availCopies, borrowedCopies);

            Books.push_back(newBook);

            loadedCount++;
        }
        catch (const std::exception& e)
        {
            cout << "\n" << "[WARNING]: Invalid data in line: " << line << endl;

            errorCount++;
        }

    }


    file.close();

    updateNextID();

    cout << "\n" << "Loaded: " << loadedCount << " active Books." << endl;

    if (errorCount > 0)
    {
        cout << "\n" << "Errors: " << errorCount << " lines skipped." << endl;
    }

}




void BookList::saveToFile(const string& filename)
{
    ofstream file(filename);
    if (!(file.is_open()))
    {
        cout << "\n" << "Failed to open file: " << filename << endl;
        return;
    }

    file << "bookID, bookTitle, author, ISBN, category, publisher, yearPublished, status, totalCopies, availCopies, borrowedCopies\n";

    for (auto& book : Books)
    {
        file << book.bookID << ","
            << book.bookTitle << ","
            << book.author << ","
            << book.ISBN << ","
            << book.category << ","
            << book.publisher << ","
            << book.yearPublished << ","
            << book.status << ","
            << book.totalCopies << ","
            << book.availCopies << ","
            << book.borrowedCopies << "\n";
    }

    file.close();

    cout << "Data saved: " << Books.size() << " Active Books." << endl;

}
