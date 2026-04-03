#include "bookList.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>
using namespace std;





BookList::BookList() : nextID(1) {}

size_t BookList::size() const { return Books.size(); }


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


/*  ---------------------------
    DISPLAY FUNCTIONS SECTION
    ---------------------------*/


bool BookList::printBook(string userInput)
{

    bool Notfound = true;

    while (Notfound)
    {
        for (const auto& b : Books)
        {

            if (b.bookID == userInput || b.bookTitle == userInput)
            {

                clear();

                cout << "\n\n" << "ACTIVE BOOK FOUND!" << "\n\n";
                cout << "---------------------------------";
                cout << "\n";
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
                Notfound = false;

                break;

            }

        }

        break;
    }


    if (Notfound == true)
    {
        cout << "\n\n" << "Book not found!" << endl;

    }

    return !Notfound;

}




void BookList::viewAllBooks(const int page, const int pageSize, char& choice, string option)
{

    string id = "ID";
    string title = "Title";
    string author = "Author";
    string category = "Category";
    string publisher = "Publisher";
    string yearPub = "Year Published";
    string totalCopy = "Total Copy";
    string availCopy = "Avail Copy";
    string borrowCopy = "Borrowed Copy";

    int id_len = id.length();
    int title_len = title.length();
    int author_len = author.length();
    int categ_len = category.length();
    int pub_len = publisher.length();
    int yearPub_len = yearPub.length();
    int totalCop_len = totalCopy.length();
    int availCop_len = availCopy.length();
    int borrowCop_len = borrowCopy.length();


    int max_id_len = 0;
    int max_title_len = 0;
    int max_author_len = 0;
    int max_category_len = 0;
    int max_publisher_len = 0;
    int max_yearPub_len = 0;
    int max_totalCopy_len = 0;
    int max_availCopy_len = 0;
    int max_borrowCopy_len = 0;

    int start = page * pageSize;
    int end = min(start + pageSize, (int)Books.size());


    if (start >= end || Books.empty()) return; // safety check

    findMaxLengthString(max_id_len, max_title_len, max_author_len, max_category_len, max_publisher_len, max_yearPub_len, max_totalCopy_len, max_availCopy_len, max_borrowCopy_len, start, end);


    // Comparing the longest length from the list vs the title

    int new_id_len = max(id_len, max_id_len);
    int new_title_len = max(title_len, max_title_len);
    int new_author_len = max(author_len, max_author_len);
    int new_category_len = max(categ_len, max_category_len);
    int new_publisher_len = max(pub_len, max_publisher_len);
    int new_yearPub_len = max(yearPub_len, max_yearPub_len);
    int new_totalCopy_len = max(totalCop_len, max_totalCopy_len);
    int new_availCopy_len = max(availCop_len, max_availCopy_len);
    int new_borrowCopy_len = max(borrowCop_len, max_borrowCopy_len);




    // Creating the border for the table
    string border = string(new_id_len + new_title_len + new_author_len + new_category_len + new_publisher_len + new_yearPub_len + new_totalCopy_len + new_availCopy_len + new_borrowCopy_len + 9, '=');

    string in_border = string(new_id_len + new_title_len + new_author_len + new_category_len + new_publisher_len + new_yearPub_len + new_totalCopy_len + new_availCopy_len + new_borrowCopy_len + 9, ' ');



    int up_border_len = border.length();

    // Integer verifier

    if (up_border_len % 2 == 0)
    {
        up_border_len--;
    }
    else
    {
        up_border_len = up_border_len;
    }


    string up_space = string((up_border_len - 27) / 2, ' ');
    string dash = string(27, '-');

    //print Table Ttle


    cout << up_space << dash << up_space << "\n";
    cout << up_space << "| LIBARY MANAGEMENT TABLE |" << up_space << "\n";
    cout << up_space << dash << up_space << "\n";


    cout << border << "\n";


    for (int space = 0; space < new_id_len - id_len; space++) cout << " ";
    cout << id << "|";


    for (int space = 0; space < new_title_len - title_len; space++) cout << " ";
    cout << title << "|";


    for (int space = 0; space < new_author_len - author_len; space++) cout << " ";
    cout << author << "|";


    for (int space = 0; space < new_category_len - categ_len; space++) cout << " ";
    cout << category << "|";


    for (int space = 0; space < new_publisher_len - pub_len; space++) cout << " ";
    cout << publisher << "|";


    for (int space = 0; space < new_yearPub_len - yearPub_len; space++) cout << " ";
    cout << yearPub << "|";



    for (int space = 0; space < new_totalCopy_len - totalCop_len; space++) cout << " ";
    cout << totalCopy << "|";


    for (int space = 0; space < new_availCopy_len - availCop_len; space++) cout << " ";
    cout << availCopy << "|";


    for (int space = 0; space < new_borrowCopy_len - borrowCop_len; space++) cout << " ";
    cout << borrowCopy << "|";



    cout << "\n";
    cout << border << "\n";

    int count = 0;

    for (int i = start; i < end; i++)
    {

        {
            int num = Books[i].bookID.size();

            for (int space = 0; space < new_id_len - num; space++) cout << " ";
            cout << Books[i].bookID << "|";


            num = Books[i].bookTitle.size();

            for (int space = 0; space < new_title_len - num; space++) cout << " ";
            cout << Books[i].bookTitle << "|";

            num = Books[i].author.size();

            for (int space = 0; space < new_author_len - num; space++) cout << " ";
            cout << Books[i].author << "|";


            num = Books[i].category.size();

            for (int space = 0; space < new_category_len - num; space++) cout << " ";
            cout << Books[i].category << "|";


            num = Books[i].publisher.size();

            for (int space = 0; space < new_publisher_len - num; space++) cout << " ";
            cout << Books[i].publisher << "|";


            num = Books[i].yearPublished.size();

            for (int space = 0; space < new_yearPub_len - num; space++) cout << " ";
            cout << Books[i].yearPublished << "|";



            num = to_string(Books[i].totalCopies).size();


            for (int space = 0; space < new_totalCopy_len - num; space++) cout << " ";
            cout << Books[i].totalCopies << "|";


            num = to_string(Books[i].availCopies).size();


            for (int space = 0; space < new_availCopy_len - num; space++) cout << " ";
            cout << Books[i].availCopies << "|";


            num = to_string(Books[i].borrowedCopies).size();


            for (int space = 0; space < new_borrowCopy_len - num; space++) cout << " ";
            cout << Books[i].borrowedCopies << "|";



            cout << "\n" << in_border << "\n";

            count++;

        }

    }
    int in_border_len = in_border.length();
    string low_space = string((in_border_len - 30), ' ');


    cout << border << "\n";
    cout << "\n\n" << "Showing " << count << " of " << Books.size() << " books" << low_space << "Page " << page + 1;


    // View, Delete, and Search Options


    if (option == "view")
    {
        cout << "\n[N] Next | [P] Previous | [Q] Quit: ";
        cin.clear();
        cin >> choice;
    }
    else if (option == "modify")
    {
        cout << "\n[D] Delete | [E] Edit | [Q] Quit: ";
        cin.clear();
        cin >> choice;
    }
    else if (option == "search")
    {
        return;
    }

    else
    {
        return;
    }


    cout << endl;
}


// THESE ARE THE SUB FUNCTIONS FOR THE VIEW ALL BOOKS FUNCTION


void BookList::findMaxLengthString(int& max_id_len, int& max_title_len, int& max_author_len, int& max_category_len, int& max_publisher_len, int& max_yearPub_len, int& max_totalCopy_len, int& max_availCopy_len, int& max_borrowCopy_len, int start, int end)
{

    // ID Length Finder
    auto it = max_element(Books.begin() + start, Books.begin() + end,
        [](const Book& a, const Book& b) {
            return a.bookID.size() < b.bookID.size();
        });
    max_id_len = it->bookID.size();


    // Title Length Finder

    it = max_element(Books.begin() + start, Books.begin() + end,
        [](const Book& a, const Book& b) {
            return a.bookTitle.size() < b.bookTitle.size();
        });
    max_title_len = it->bookTitle.size();


    // Author Length Finder

    it = max_element(Books.begin() + start, Books.begin() + end,
        [](const Book& a, const Book& b) {
            return a.author.size() < b.author.size();
        });
    max_author_len = it->author.size();


    // Category Length Finder

    it = max_element(Books.begin() + start, Books.begin() + end,
        [](const Book& a, const Book& b) {
            return a.category.size() < b.category.size();
        });
    max_category_len = it->category.size();


    // Publisher Length Finder

    it = max_element(Books.begin() + start, Books.begin() + end,
        [](const Book& a, const Book& b) {
            return a.publisher.size() < b.publisher.size();
        });
    max_publisher_len = it->publisher.size();


    // Year Published Length Finder

    it = max_element(Books.begin() + start, Books.begin() + end,
        [](const Book& a, const Book& b) {
            return a.yearPublished.size() < b.yearPublished.size();
        });
    max_yearPub_len = it->yearPublished.size();


    // Total Copies Length Finder

    it = max_element(Books.begin() + start, Books.begin() + end,
        [](const Book& a, const Book& b) {
            return a.totalCopies < b.totalCopies;
        });
    max_totalCopy_len = to_string(it->totalCopies).size();


    // Available Copies Length Finder

    it = max_element(Books.begin() + start, Books.begin() + end,
        [](const Book& a, const Book& b) {
            return a.availCopies < b.availCopies;
        });
    max_availCopy_len = to_string(it->availCopies).size();


    // Borrowed Copies Length Finder

    it = max_element(Books.begin() + start, Books.begin() + end,
        [](const Book& a, const Book& b) {
            return a.borrowedCopies < b.borrowedCopies;
        });
    max_borrowCopy_len = to_string(it->borrowedCopies).size();

}

/* ---------------------------------
    DELETE FUNCTIONS SECTION
 ---------------------------------*/



void BookList::deleteThisBook()
{
}