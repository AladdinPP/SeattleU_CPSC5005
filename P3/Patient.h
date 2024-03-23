// AUTHOR:      Hongru He
// FILENAME:    Patient.h
// DATE:        11/13/2023
// PURPOSE:     Creates the patient instance stored name, priority code,
//              arrival order; functions including constructors, overloaded
//              operators to compare, to_string, setters, and getters

#ifndef P3_PATIENT_H
#define P3_PATIENT_H
#include <iostream>
#include <sstream>

using namespace std;

class Patient {
public:
    Patient();
    // default constructor

    ~Patient();
    // destructor

    Patient(string, string);
    // overloaded constructor
    // pre:     none
    // post:    patient name and priority code are assigned to parameters

    Patient& operator=(const Patient &);
    // overloaded operator to assign the parameter instance to the original
    // instance
    // pre:     the original instance should be different from the parameter
    // post:    the original instance stored the values from the parameter

    bool operator>(const Patient &);
    // overloaded operator to compare the original instance to the parameter
    // pre:     none
    // post:    none

    bool operator<(const Patient &);
    // overloaded operator to compare the original instance to the parameter
    // pre:     none
    // post:    none

    void setArrivalOrder(int);
    // the setter of the arrival order
    // pre:     none
    // post:    the arrival order is assigned to the parameter

    int getPriorityLevel() const;
    // convert the priority code into specific integer
    // pre:     none
    // post:    none

    string getName() const;
    // the getter of the patient name
    // pre:     none
    // post:    none

    string getPriority() const;
    // the getter of the priority code
    // pre:     none
    // post:    none

    int getArrival() const;
    // the getter of the arrival order
    // pre:     none
    // post:    none

    string to_string() const;
    // convert the instance content into a string
    // pre:     none
    // post:    none

private:
    string name;
    string priorityCode;
    int arrivalOrder;
};

Patient::Patient() {
    arrivalOrder = 0;
}

Patient::~Patient() {
    name = "";
    priorityCode = "";
    arrivalOrder = 0;
}

Patient::Patient(string patName, string priCode) {
    name = patName;
    priorityCode = priCode;
}

Patient& Patient::operator=(const Patient & right) {
    // check if the original instance is the same as the parameter
    if (this != &right) {
        this->name = right.name;
        this->priorityCode = right.priorityCode;
        this->arrivalOrder = right.arrivalOrder;
    }
    return *this;
}

bool Patient::operator>(const Patient & right) {
    int pLevel = this->getPriorityLevel();
    int pLevelRight = right.getPriorityLevel();

    // define "greater" one as the prior patient, so use the max heap in the
    // priority queue
    if (pLevel == pLevelRight)
        return this->arrivalOrder < right.arrivalOrder;
    return pLevel < pLevelRight;
}

bool Patient::operator<(const Patient & right) {
    int pLevel = this->getPriorityLevel();
    int pLevelRight = right.getPriorityLevel();

    if (pLevel == pLevelRight)
        return this->arrivalOrder > right.arrivalOrder;
    return pLevel > pLevelRight;
}

void Patient::setArrivalOrder(int order) {
    arrivalOrder = order;
}

int Patient::getPriorityLevel() const {
    if (priorityCode == "immediate")
        return 1;
    else if (priorityCode == "emergency")
        return 2;
    else if (priorityCode == "urgent")
        return 3;
    else
        return 4;
}

string Patient::getName() const {
    return name;
}

string Patient::getPriority() const {
    return priorityCode;
}

int Patient::getArrival() const {
    return arrivalOrder;
}

string Patient::to_string() const {
    stringstream ss;
    ss << name << " { pri=" << priorityCode << ", arrive=" << arrivalOrder <<
    " }" << endl;
    return ss.str();
}

#endif //P3_PATIENT_H
