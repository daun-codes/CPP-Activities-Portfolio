// Library Management System version 1.0
/*
    This program will help the librarian administrator to manage the books in the library. They can add new books, delete books, view all books, and search for a specific boook.


    Note: The Program is still under development. I will be adding more features to the program.


    Features Available:

    1. Add new book.
    2. Display All book that was added.
    3. Save the data to a file.



    Limitations:

    1. The user will not be able to delete the book that is no longer available
    2. The user will not be able to borrow any book yet
    3. The user will not be able to search for a specific book yet


*/

#include "book.h"
#include "bookList.h"
#include <iostream> 
#include <limits>
#include <cmath>
#include <unordered_set>
using namespace std;




// PROTOTYPE FUNCTIONS FOR MAIN.

void addNewBook(BookList& list);
void displayBooks(BookList& list);



int main() {



    BookList list;
    BookList backupList;

    list.LoadFromFile("../data/backupInfo.csv");
    list.LoadFromFile("../data/bookInfo.csv");

    int choice;


    do {


        cout << "\n\n" << "Welcome to the Library Management System" << "\n\n";
        cout << "[MENU OPTIONS]" << "\n\n";

        cout << "[1] Add new book" << "\n";
        cout << "[2] Edit book details" << "\n";
        cout << "[3] Delete book" << "\n";
        cout << "[4] View all books" << "\n";
        cout << "[5] Search a book" << "\n";
        cout << "[0] Exit" << "\n\n";


        cout << "Enter your choice: ";

        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Response. Enter a number: ";
        }


        switch (choice)
        {
        case 1:
            cout << "\n\n" << "You choose to Add a new Book" << "\n";
            addNewBook(list);
            break;
        case 2:
            cout << "\n\n" << "You choose to Edit a Book" << "\n";
            break;
        case 3:
            cout << "\n\n" << "You choose to Delete a Book" << "\n";
            
            break;
        case 4:
            cout << "\n\n" << "You choose to View all Books" << "\n";
            list.LoadFromFile("../data/bookInfo.csv");
            displayBooks(list);
            break;
        case 5:
            cout << "\n\n" << "You choose to Search a Book by: " << "\n";
            break;

        case 0:
            cout << "\n\n" << "You choose to Exit the program" << "\n";
            cout << "Thank you and have a nice day!" << endl;
            break;

        default:
            break;
        }

        if (choice != 0) {
            cout << "\n\n" << "Please enter to return to Menu...";
            cin.ignore();
            cin.get();
        }


    } while (choice != 0);


    return 0;
}



void addNewBook(BookList& list)
{
    string title, author, isbn, category, publisher, yearPub;
    int totalCopy, availCopy;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    cout << "\n\n" << "Book Information Form" << "\n";

    cout << "\n" << "Enter the book Title: ";
    getline(cin, title);
    cout << "Enter the Author's name: ";
    getline(cin, author);
    cout << "Enter the ISBN: ";
    getline(cin, isbn);
    cout << "Enter the Category: ";
    getline(cin, category);
    cout << "Enter the publisher: ";
    getline(cin, publisher);
    cout << "Enter the Year Published: ";
    cin >> yearPub;
    cout << "\n" << "Enter the Total Copies: ";
    cin >> totalCopy;

    availCopy = totalCopy;


    list.addBook(title, author, isbn, category, publisher, yearPub, totalCopy, availCopy);


    list.saveToFile("../data/bookInfo.csv");



}



void displayBooks(BookList& list)
{
    char choice;

    int pageSize = 10;
    int currentPage = 0;

    do {
        list.viewAllBooks(currentPage, pageSize);

        cout << "\n[N] Next | [P] Previous | [Q] Quit: ";
        cin >> choice;

        if (choice == 'N' || choice == 'n') {
            if ((currentPage + 1) * pageSize < list.size()) {
                currentPage++;
            }
        }
        else if (choice == 'P' || choice == 'p') {
            if (currentPage > 0) {
                currentPage--;
            }
        }

    } while (choice != 'Q' && choice != 'q');
}



    