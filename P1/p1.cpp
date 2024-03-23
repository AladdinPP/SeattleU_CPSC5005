// Author: Hongru He
// Program: p1.cpp
// Date: 10/10/2023

#include "BookList.h"
#include "MemberList.h"
#include "RatingList.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void viewRating(int, BookList &, MemberList &, RatingList &);
// display all the ratings of one specific login user
void viewRecommendation(int, BookList &, MemberList &, RatingList &);
// display the recommendation list for a specific login user
MemberList addMember(MemberList, int);
// add a new member to memberList
BookList addBook(BookList, int);
// add a new book to bookList
RatingList rateBook(RatingList, BookList &, int &, int &);
// add a new rating

int main() {
    // create variables
    string fileBook, fileRating, bookContent, ratingContent;

    // initialize three classes
    BookList bookList(100);
    MemberList memberList(100);
    RatingList ratingList(100);

    // welcome message
    cout << "Welcome to the Book Recommendation Program.\n" <<
    "You can add new book, add new member(get an account number)\n" <<
    "before you log into the system. After you log in, you can\n" <<
    "also rate books, view all your ratings, and see the book\n" <<
    "recommendation for you.\n" << endl;

    // prompt for user input of filename
    cout << "Enter books file: ";
    cin >> fileBook;
    cout << "\nEnter rating file: ";
    cin >> fileRating;
    cout << endl;

    // open the book file
    string author, title, year;
    int bookCount = 0;
    ifstream infile;
    infile.open(fileBook);

    // read through the file and write into bookList
    if (infile) {
        while (getline(infile, bookContent)) {
            stringstream str(bookContent);

            getline(str, author, ',');
            getline(str, title, ',');
            getline(str, year, ',');

            int yearP;
            stringstream yearStr;
            yearStr << year;
            yearStr >> yearP;

            bookList.addBook(author, title, yearP);

            // initialize ratingList
            ratingList.addBook(bookCount + 1);

            // trace the number of books
            bookCount++;
        }
    }
    else {
        cout << "ERROR: can not open the file.\n";
    }

    // close the book file
    infile.close();

    // open the rating file
    int membersCount = 0;
    int lineCount = 0;
    infile.open(fileRating);

    // read through the file and write into memberList and ratingList
    if (infile) {
        while (getline(infile, ratingContent)) {

            // fill names in the memberList
            if (lineCount % 2 == 0) {
                memberList.addMember(ratingContent);
                ratingList.addMember(membersCount + 1);

                // trace the line reading
                lineCount++;

                // trace the account numbers
                membersCount++;
            }

            // fill ratings in the ratingList
            else {
                istringstream ratingLine(ratingContent);
                string rating;
                int bookISBN = 1;

                // extract single numerical string from a line
                while (ratingLine >> rating) {
                    // convert the string into integer
                    stringstream ratingS;
                    ratingS << rating;
                    int ratingI = 0;
                    ratingS >> ratingI;

                    // fill the integer into the ratings array
                    ratingList.addRating(ratingI, membersCount, bookISBN);

                    // trace the ISBN number of next book
                    bookISBN++;
                }
                lineCount++;
            }
        }
    }
    else {
        cout << "ERROR: cannot open file.\n";
    }

    // close the rating file
    infile.close();

    // display the book and member numbers
    cout << "# of books: " << bookCount << endl;
    cout << "# of memberList: " << membersCount << endl;

    // while loop for non-logged-in menu operation
    string opBeforeLog = "";
    while (opBeforeLog != "4") {

        // display the menu
        cout << "\nMENU\n1. Add a new member\n2. Add a new book\n3." <<
             " Login\n4. Quit\n" << endl;

        // prompt for user input
        cout << "Enter a menu option: ";
        cin >> opBeforeLog;

        // conditional statement for different options
        // add new member
        if (opBeforeLog == "1") {
            memberList = addMember(memberList, membersCount);
            // trace the number of members
            membersCount++;
            // add a member column to ratingList
            ratingList.addMember(membersCount);
        }

        // add new book
        else if (opBeforeLog == "2") {
            bookList = addBook(bookList, bookCount);
            // trace the number of books
            bookCount++;
            // add a book row to ratingList
            ratingList.addBook(bookCount);
        }

        // login
        else if (opBeforeLog == "3") {
            int accNum;

            // prompt for user input and check the validation
            do {
                cout << "\nEnter member account (not greater than " <<
                     membersCount << "): ";
                cin >> accNum;
            } while (accNum > membersCount);

            // change the login status
            memberList.login(accNum);
            cout << memberList.getName(accNum) <<
            ", you are logged in!" << endl;

            // while loop for logged-in menu operation
            string opAfterLog = "";
            while (opAfterLog != "6") {
                // display the menu after logged in
                cout << "\nMENU\n1. Add a new member\n2. Add a new book\n3." <<
                     " Rate book\n4. View ratings\n5. See Recommendations" <<
                     "\n6. Logout\n" << endl;

                // prompt for user input
                cout << "Enter a menu option: ";
                cin >> opAfterLog;

                // conditional statement for different options
                // add new member
                if (opAfterLog == "1") {
                    memberList = addMember(memberList,
                                           membersCount);
                    // trace the number of members
                    membersCount++;
                    // add a member column to ratingList
                    ratingList.addMember(membersCount);
                }

                // add new book
                else if (opAfterLog == "2") {
                    bookList = addBook(bookList, bookCount);
                    // trace the number of books
                    bookCount++;
                    // add a book row to ratingList
                    ratingList.addBook(bookCount);
                }

                // rate a book
                else if (opAfterLog == "3") {
                    ratingList = rateBook(ratingList, bookList,
                             accNum, bookCount);
                }

                // view ratings
                else if (opAfterLog == "4") {
                    viewRating(accNum, bookList,
                               memberList, ratingList);
                }

                // view recommendation
                else if (opAfterLog == "5") {
                    viewRecommendation(accNum, bookList,
                                       memberList, ratingList);
                }

                // logout
                else {
                    // change the login status
                    memberList.logout(accNum);
                }
            }
        }
    }

    // delocate the memory
    bookList.~BookList();
    memberList.~MemberList();
    ratingList.~RatingList();

    // display the goodbye message
    cout << "\nThank you for using the Book Recommendation Program!" << endl;

    return 0;
}



void viewRating(int num, BookList & blist, MemberList & mlist,
                RatingList & rlist) {
    cout << mlist.getName(num) << "'s ratings..." << endl;
    int bookNum = blist.size();
    for (int i = 1; i <= bookNum; i++) {
        cout << blist.to_string(i) << " => rating: "
        << rlist.getRating(i - 1, num - 1) << endl;
    }
}

void viewRecommendation(int num, BookList & blist, MemberList & mlist,
                        RatingList & rlist) {
    // get the member account used for recommendation
    int accRec = rlist.getRec(num);

    // get the member's name
    string nameRec = mlist.getName(accRec);

    // initializes two array to store books rated as 5 (MostLike) and 3 (Like)
    int * bookML = new int[blist.size()];
    int * bookL = new int[blist.size()];

    // trace the number of these two ratings
    int countML = 0, countL = 0;

    // fill the MostLike and Like list
    for (int i = 0; i < blist.size(); i++) {
        if (rlist.getRating(i, accRec - 1) == 5) {
            bookML[countML] = i + 1;
            countML++;
        }
        else if (rlist.getRating(i, accRec - 1) == 3) {
            bookL[countL] = i + 1;
            countL++;
        }
    }

    // display the recommendation information
    cout << "You have similar taste in books as " << nameRec << "!" << endl;

    cout << "Here are the books they really liked:" << endl;
    for (int j = 0; j < countML; j++) {
        cout << blist.to_string(bookML[j]) << endl;
    }

    cout << "\nAnd here are the books they liked:" << endl;
    for (int k = 0; k < countL; k++) {
        cout << blist.to_string(bookL[k]) << endl;
    }

    // delocate the dynamic arrays
    delete [] bookML;
    delete [] bookL;
}

MemberList addMember(MemberList mlist, int memCount) {
    string newName;
    // prompt for user input
    cout << "\nEnter the name of the new member: ";

    // get the whole line of input ignoring the space
    getline(cin >> ws, newName);

    // add new member to memberList
    mlist.addMember(newName);
    memCount++;

    cout << "\n" << mlist.getName(memCount) << " (account #: " <<
         memCount << ") was added." << endl;

    return mlist;
}

BookList addBook(BookList blist, int boCount) {
    string auName, bookTitle;
    int yearPub;
    // prompt for user input
    cout << "\nEnter the author of the new book: ";
    getline(cin >> ws, auName);
    cout << "\nEnter the title of the new book: ";
    getline(cin >> ws, bookTitle);
    cout << "\nEnter the publish year of the new book: ";
    cin >> yearPub;

    // add new book to bookList
    blist.addBook(auName, bookTitle, yearPub);
    boCount++;

    cout << blist.to_string(boCount) << " was added." << endl;

    return blist;
}

RatingList rateBook(RatingList rlist, BookList & blist, int & accNum,
              int & boCount) {
    int isbnNum = 0;
    // prompt for ISBN number and check the validation
    do {
        cout << "\nEnter the ISBN for the book you'd like to rate (not" <<
        " greater than " << boCount << ") : ";
        cin >> isbnNum;
    } while (isbnNum > boCount);

    int newRating;
    // show the rating choices and meaning of each one
    cout << "\nRATING MENU\n-5: Hated it!\n-3: Didn't like it\n" <<
    "1: ok - neither hot nor cold about it\n3: Liked it!\n" <<
    "5: Really liked it!" << endl;

    // prompt for rating
    cout << "Enter your rating: ";
    cin >> newRating;

    // add new rating into ratingList
    rlist.addRating(newRating, accNum, isbnNum);
    cout << "Your new rating for " << blist.to_string(isbnNum) <<
    " => rating: " << newRating << endl;

    return rlist;
}