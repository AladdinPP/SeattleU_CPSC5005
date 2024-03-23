// Author: Hongru He
// Program: BookList.h
// Date: 10/10/2023
// Purpose: this class initializes a dynamic array of book structs to store the
// book information. It allows user to add new books into the array

#ifndef P1_BOOKLIST_H
#define P1_BOOKLIST_H
#include <string>
using namespace std;

struct Book{
    int ISBN, yearPub;
    string author, title;
};

class BookList {
public:
    BookList(int);                             // default constructor
    ~BookList();
    BookList(const BookList &);
    BookList& operator=(const BookList &);

    void addBook(string, string, int);
    // add a new book into the array
    bool empty() const;
    int size() const;
    // return the number of book currently stored in the array
    string to_string() const;
    // convert all the book information into a string
    string to_string(int) const;
    // convert exact book information into a string

private:
    Book * list;            // the dynamic array storing book information
    int capacity;           // the size of the array
    int numElements;        // the number of books stored in the array
    void resize();
    // resize the array when it is full
};


#endif //P1_BOOKLIST_H
