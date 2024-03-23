// Author: Hongru He
// Program: MemberList.h
// Date: 10/10/2023
// Purpose: this class initializes a dynamic array of member structs to store
// the member information. It allows user to add new members, log in, and log
// out.

#ifndef P1_MEMBERLIST_H
#define P1_MEMBERLIST_H
#include <string>
using namespace std;

struct Member {
    string name;
    int account;
    bool loggedin = false;             // trace the login status
};

class MemberList {
public:
    MemberList(int);                   // default constructor
    ~MemberList();
    MemberList(const MemberList &);
    MemberList& operator=(const MemberList &);

    void addMember(string);
    // add a new member to the array
    void login(int);
    // let a member to login
    void logout(int);
    // let a member to logout
    bool empty() const;
    int size() const;
    string to_string() const;
    string getName(int) const;
    // get the exact member's name using their account number

private:
    Member * list;          // the array storing member information
    int capacity;           // the size of the array
    int numElements;        // the number of members stored in the array
    void resize();
    // resize the array when it is full
};


#endif //P1_MEMBERLIST_H
