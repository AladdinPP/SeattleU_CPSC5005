// Author: Hongru He
// Program: RatingList.cpp
// Date: 10/10/2023

#include "RatingList.h"
#include <sstream>
#include <string>
using namespace std;

RatingList::RatingList(int cap) {
    list = new int*[cap];
    for(int i = 0; i < cap; i++)
        list[i] = new int[cap];
    capacity = cap;
    bookNum = 0;
    memberNum = 0;
}

RatingList::~RatingList() {
    for (int i = 0; i < capacity; i++) {
        delete [] list[i];
    }
    delete [] list;
}

RatingList::RatingList(const RatingList &obj) {
    capacity = obj.capacity;
    bookNum = obj.bookNum;
    memberNum = obj.memberNum;

    list = new int*[capacity];
    for(int i = 0; i < capacity; i++)
        list[i] = new int[capacity];

    for (int i = 0; i < bookNum; i++) {
        for (int j = 0; j < memberNum; j++)
            list[i][j] = obj.list[i][j];
    }
}

RatingList& RatingList::operator=(const RatingList &obj) {
    if (this != &obj) {
        delete [] list;

        capacity = obj.capacity;
        bookNum = obj.bookNum;
        memberNum = obj.memberNum;

        list = new int*[capacity];
        for(int i = 0; i < capacity; i++)
            list[i] = new int[capacity];

        for (int i = 0; i < bookNum; i++) {
            for (int j = 0; j < memberNum; j++)
                list[i][j] = obj.list[i][j];
        }
    }
    return *this;
}

void RatingList::addRating(int rate, int account, int book) {
    list[book - 1][account - 1] = rate;
}

void RatingList::addBook(int book) {
    if (book > capacity)
        resize();

    for (int i = 0; i < memberNum; i++)
        list[book - 1][i] = 0;

    bookNum++;
}

void RatingList::addMember(int account) {
    if (account > capacity)
        resize();

    for (int i = 0; i < bookNum; i++)
        list[i][account - 1] = 0;

    memberNum++;
}

bool RatingList::empty() const {
    return (bookNum == 0 && memberNum == 0);
}

string RatingList::to_string() const {
    stringstream ss;
    for (int i = 0; i < bookNum; i++) {
        for (int j = 0; j < memberNum; j++) {
            ss << list[i][j] << " ";
        }
        ss << endl;
    }
    return ss.str();
}

int RatingList::getRating(int row, int col) const {
    return list[row][col];
}

void RatingList::resize() {
    capacity *= 2;

    int ** tempArr = new int*[capacity];
    for (int i = 0; i < capacity; i++)
        tempArr[i] = new int[capacity];

    for (int i = 0; i < bookNum; i++) {
        for (int j = 0; j < memberNum; j++) {
            tempArr[i][j] = list[i][j];
        }
    }

    for (int i = 0; i < bookNum; i++) {
        delete [] list[i];
    }
    delete [] list;

    list = tempArr;
}

int RatingList::findSimilarity(int acc1, int acc2) const {
    int similarity = 0;
    for (int i = 0; i < bookNum; i++) {
        similarity += list[i][acc1 - 1] * list[i][acc2 - 1];
    }
    return similarity;
}

int RatingList::getRec(int accNum) const {
    int maxSim = -999999;
    int accRec = -1;

    for (int i = 1; i <= memberNum; i++) {
        if (i != accNum) {
            int sim = findSimilarity(accNum, i);
            if (sim > maxSim) {
                maxSim = sim;
                accRec = i;
            }
        }
    }

    return accRec;
}