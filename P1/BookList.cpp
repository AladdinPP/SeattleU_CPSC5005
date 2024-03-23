// Author: Hongru He
// Program: BookList.cpp
// Date: 10/10/2023

#include "BookList.h"
#include <sstream>
#include <string>
using namespace std;

BookList::BookList(int cap) {
    list = new Book[cap];
    capacity = cap;
    numElements = 0;
}

BookList::~BookList() {
    delete [] list;
}

BookList::BookList(const BookList &obj) {
    // assign numElements and capacity (from obj)
    capacity = obj.capacity;
    numElements = obj.numElements;

    // allocate memory based on new capacity
    list = new Book[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numElements; i++) {
        list[i].ISBN = obj.list[i].ISBN;
        list[i].yearPub = obj.list[i].yearPub;
        list[i].author = obj.list[i].author;
        list[i].title = obj.list[i].title;
    }
}

BookList& BookList::operator=(const BookList &obj) {
    if (this != &obj) {
        // deallocate memory
        delete [] list;

        // assign numElements and capacity (from obj)
        capacity = obj.capacity;
        numElements = obj.numElements;

        // allocate memory based on new capacity
        list = new Book[capacity];

        // copy over elements (from obj)
        for (int i = 0; i < numElements; i++) {
            list[i].ISBN = obj.list[i].ISBN;
            list[i].yearPub = obj.list[i].yearPub;
            list[i].author = obj.list[i].author;
            list[i].title = obj.list[i].title;
        }
    }
    return *this;
}

void BookList::addBook(string person, string name, int year) {
    if (numElements >= capacity)
        resize();
    list[numElements].ISBN = numElements + 1;
    list[numElements].yearPub = year;
    list[numElements].author = person;
    list[numElements].title = name;
    numElements++;
}

bool BookList::empty() const {
    return numElements == 0;
}

int BookList::size() const {
    return numElements;
}

string BookList::to_string() const {
    stringstream ss;
    for(int i = 0; i < numElements; i++) {
        ss << list[i].ISBN << ", " << list[i].author << ", " <<
        list[i].title << ", " << list[i].yearPub << endl;
    }
    return ss.str();
}

string BookList::to_string(int isbnNum) const {
    stringstream ss;
    ss << list[isbnNum - 1].ISBN << ", " << list[isbnNum - 1].author << ", " <<
    list[isbnNum - 1].title << ", " << list[isbnNum - 1].yearPub;

    return ss.str();
}

void BookList::resize() {
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    Book * tempArr = new Book[capacity];

    // copy old array values to new array
    for (int i = 0; i < numElements; i++) {
        tempArr[i].ISBN = list[i].ISBN;
        tempArr[i].author = list[i].author;
        tempArr[i].title = list[i].title;
        tempArr[i].yearPub = list[i].yearPub;
    }

    // delete old array
    delete [] list;

    // reassign old array to new array
    list = tempArr;
}