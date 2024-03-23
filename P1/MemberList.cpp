// Author: Hongru He
// Program: MemberList.cpp
// Date: 10/10/2023

#include "MemberList.h"
#include <sstream>
#include <string>
using namespace std;

MemberList::MemberList(int cap) {
    list = new Member[cap];
    capacity = cap;
    numElements = 0;
}

MemberList::~MemberList() {
    delete [] list;
}

MemberList::MemberList(const MemberList &obj) {
    capacity = obj.capacity;
    numElements = obj.numElements;

    list = new Member[capacity];

    for (int i = 0; i < numElements; i++) {
        list[i].account = obj.list[i].account;
        list[i].name = obj.list[i].name;
        list[i].loggedin = obj.list[i].loggedin;
    }
}

MemberList& MemberList::operator=(const MemberList &obj) {
    if (this != &obj) {
        delete [] list;

        capacity = obj.capacity;
        numElements = obj.numElements;

        list = new Member[capacity];

        for (int i = 0; i < numElements; i++) {
            list[i].name = obj.list[i].name;
            list[i].account = obj.list[i].account;
            list[i].loggedin = obj.list[i].loggedin;
        }
    }
    return *this;
}

void MemberList::addMember(string person) {
    if (numElements >= capacity)
        resize();
    list[numElements].account = numElements + 1;
    list[numElements].name = person;
    list[numElements].loggedin = false;
    numElements++;
}

void MemberList::login(int accNum) {
    list[accNum - 1].loggedin = true;
}

void MemberList::logout(int accNum) {
    list[accNum - 1].loggedin = false;
}

bool MemberList::empty() const {
    return numElements == 0;
}

int MemberList::size() const {
    return numElements;
}

string MemberList::to_string() const {
    stringstream ss;
    for (int i = 0; i < numElements; i++) {
        ss << list[i].account << ", " << list[i].name << endl;
    }
    return ss.str();
}

string MemberList::getName(int accNum) const {
    return list[accNum - 1].name;
}

void MemberList::resize() {
    capacity *= 2;

    Member * tempArr = new Member[capacity];

    for (int i = 0; i < numElements; i++) {
        tempArr[i].account = list[i].account;
        tempArr[i].name = list[i].name;
        tempArr[i].loggedin = list[i].loggedin;
    }

    delete [] list;

    list = tempArr;
}