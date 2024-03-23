// Author: Hongru He
// Program: RatingList.h
// Date: 10/10/2023
// Purpose: this class initializes and holds a dynamic 2D array, in which it
// stores all the existing ratings. It allows user to add new ratings. The 2D
// array will grow when new books and members are added into MemberList class
// and BookList class.

#ifndef P1_RATINGLIST_H
#define P1_RATINGLIST_H
#include <string>
using namespace std;

class RatingList {
public:
    RatingList(int);                           // default constructor
    ~RatingList();
    RatingList(const RatingList &);
    RatingList& operator=(const RatingList &);

    void addRating(int, int, int);
    // add a new rating to an existing book for a member
    void addBook(int);
    // add a new row for the newly-added book
    void addMember(int);
    // add a new column for the newly-added member

    bool empty() const;
    // check if the array is emepty
    string to_string() const;
    // convert the array content into a string
    int getRating(int, int) const;
    // get the exact rating of a book for a member
    int getRec(int) const;
    // get the account number used for recommendation for a specific member
    int findSimilarity(int, int) const;
    // get the rating similarity between two members

private:
    int ** list;        // the dynamic 2D array storing ratings
    int capacity;       // the size of the 2D array
    int bookNum;        // the number of books (also the number of rows)
    int memberNum;      // the number of members (also the number of columns)
    void resize();
    // resize the 2D array when it is full
};


#endif //P1_RATINGLIST_H
