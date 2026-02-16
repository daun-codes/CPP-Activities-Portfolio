// THIS IS THE HELPER FUNCTIONS TO BE USED IN THE PROGRAM


#include "utils.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <iostream>
#include <cstdlib> // use for clear screen in the console 



// trim leading and trailing spaces


std::string trim(const std::string& str)
{
    std::string s = str;

    // leading spaces
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](unsigned char c) { return !std::isspace(c); }));

    // trailing spaces
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](unsigned char c) { return !std::isspace(c); }).base(), s.end());

    return s;
}


// Conver the string to Title Case

std::string toTitleCase(std::string str)
{
    bool newWord = true;
    for (char& c : str)
    {
        if (isspace(c))
        {
            newWord = true;

        }
        else
        {
            if (newWord)
            {
                c = toupper(c);
                newWord = false;

            }
            else
            {
                c = tolower(c);
            }
        }
    }
    return str;
}


// clear the screen

void clearScreen()
{
    system("cls");
}



// Generate today's date
std::string getTodayDate()
{
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char buffer[11];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);

    return std::string(buffer);
}



