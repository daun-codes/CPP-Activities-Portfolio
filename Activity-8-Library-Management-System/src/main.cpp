// Library Management System version 1.0
/*
    This program will help the librarian administrator to manage the books in the library. They can add new books, delete books, view all books, and search for a specific boook.


    Note: The Program is still under development. I will be adding more features to the program.


    Features Available:

    1. Add new book.
    2. Display All book that was added.



    Limitations:

    1. The program is not going to save this data to a file.
    2. The user will have to enter the data again if they want to add another book.


*/

#include "book.h"
#include "bookList.h"
#include <iostream> 
#include <limits>
using namespace std;




// PROTOTYPE FUNCTIONS FOR MAIN.

void addNewBook(BookList& list);
void displayAllBooks(BookList& list);


int main() {


    BookList list;

    int choice;


    do {


        cout << "\n\n" << "Welcome to the Library Management System" << "\n\n";
        cout << "[MENU OPTIONS]" << "\n\n";

        cout << "[1] Add new book" << "\n";
        cout << "[2] Edit book details" << "\n";
        cout << "[3] Delete book" << "\n";
        cout << "[4] View all books" << "\n";
        cout << "[5] Search" << "\n";
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
            displayAllBooks(list);
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
            cout << "Please enter to return to Menu...";
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



}


void displayAllBooks(BookList& list)
{
    cin.clear();

    cout << "\n\n" << "[List of All Books]";
    cout << "\n\n";

    cout << "------------------------------------" << endl;

    list.printList();


}