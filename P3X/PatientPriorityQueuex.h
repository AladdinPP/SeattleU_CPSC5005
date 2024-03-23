// AUTHOR:      Hongru He
// FILENAME:    PatientPriorityQueuex.h
// DATE:        11/13/2023
// PURPOSE:     Create the patient priority queue instance; functions
//              including constructor, add, peek, remove, size, and
//              to_string; every change made to the vector based on heap order

#include "Patient.h"
#ifndef P3X_PATIENTPRIORITYQUEUEX_H
#define P3X_PATIENTPRIORITYQUEUEX_H
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

class PatientPriorityQueuex {
public:
    PatientPriorityQueuex();
    // default constructor
    // pre:     none
    // post:    nextPatientNumber is initialized

    void add(Patient &);
    // add a new patient into the priority queue
    // pre:     none
    // post:    nextPatientNumber gets increment, priority queue added and
    //          sorted in heap order

    Patient peek() const;
    // get the first patient in the queue
    // pre:     the queue shouldn't be empty
    // post:    none

    Patient remove();
    // get the first patient in the queue and remove it from the queue
    // pre:     the queue shouldn't be empty
    // post:    remove the first patient in the queue

    string change(int, string &);
    // change a specific Patient's priority code
    // pre:     none
    // post:    the queue order may be changed

    int size() const;
    // get the number of patients in the queue
    // pre:     none
    // post:    none

    string to_string() const;
    // convert the instance content into a string
    // pre:     none
    // post:    none

    string to_fileStr();
    // convert the queue into a command string
    // pre:     none
    // post:    none

private:
    int nextPatientNumber, patientNum;
    vector<Patient> vp;

    void siftUp(int);
    // sort the queue in max heap order
    // pre:     none
    // post:    the queue is sorted by max heap order

    void siftDown(int);
    // sort the queue in max heap order
    // pre:     none
    // post:    the queue is sorted by max heap order

    void sortArrival(int);
    // selection sort the queue by arrival number
    // pre:     none
    // post:    the queue is sorted in ascending order by arrival number

    int binarySearch(int) const;
    // binary search for a specific patient by given arrival number
    // pre:     none
    // post:    none

    int getParent(int) const;
    // get the parent index of the given index
    // pre:     none
    // post:    none

    int getLeftChild(int) const;
    // get the left child index of the given index
    // pre:     none
    // post:    none

    int getRightChild(int) const;
    // get the right child index of the given index
    // pre:     none
    // post:    none
};

PatientPriorityQueuex::PatientPriorityQueuex() {
    nextPatientNumber = 1;
    patientNum = 0;
}

void PatientPriorityQueuex::add(Patient & pNew) {
    // assign the arrivalOrder to the new patient based on nextPatientNumber
    pNew.setArrivalOrder(nextPatientNumber);

    // increment
    nextPatientNumber++;
    patientNum++;

    // add to the vector
    vp.push_back(pNew);

    // sort the vector in max heap order
    if (patientNum > 1)
        siftUp(patientNum - 1);
}

Patient PatientPriorityQueuex::peek() const {
    assert(!vp.empty());
    return vp.front();
}

Patient PatientPriorityQueuex::remove() {
    // check if the queue is empty
    assert(!vp.empty());

    // remove the first patient and sort the vector in max heap order again
    Patient temp = vp.front();
    vp[0] = vp.back();
    vp.pop_back();
    patientNum--;
    if (patientNum > 1)
        siftDown(0);
    return temp;
}

string PatientPriorityQueuex::change(int arrival, string & priority){
    // sort the queue by arrival
    sortArrival(patientNum - 1);

    // search for the target index
    int patientFound = binarySearch(arrival);

    // get the name
    string patientName;

    if (patientFound == -1)
        patientName = "";

    else {
        patientName = vp[patientFound].getName();

        // create the new patient instance to change
        Patient temp = Patient(patientName, priority);
        temp.setArrivalOrder(arrival);

        vp[patientFound] = temp;
    }

    // restore the triage heap order
    siftDown(0);

    return patientName;
}

int PatientPriorityQueuex::size() const {
    return patientNum;
}

string PatientPriorityQueuex::to_string() const {
    stringstream ss;
    for (int i = 0; i < patientNum; i++)
        ss << "     " << vp[i].getArrival() << "\t\t" << vp[i].getPriority()
        << "  \t" << vp[i].getName() << endl;
    return ss.str();
}

string PatientPriorityQueuex::to_fileStr() {
    stringstream ss;

    // sort by arrival
    sortArrival(patientNum - 1);

    for (int i = 0; i < patientNum; i++)
        ss << "add " << vp[i].getPriority() << " " << vp[i].getName() << endl;

    // restore the priority heap order
    siftDown(0);

    return ss.str();
}

void PatientPriorityQueuex::siftUp(int index) {
    int parentIdx;
    Patient temp;

    // check there are more than one patient in the queue
    if (index != 0) {
        parentIdx = getParent(index);

        // if the parent is smaller, swap
        if (vp[parentIdx] < vp[index]) {
            temp = vp[parentIdx];
            vp[parentIdx] = vp[index];
            vp[index] = temp;
            siftUp(parentIdx);
        }
    }
}

void PatientPriorityQueuex::siftDown(int index) {
    int leftIdx, rightIdx, maxIdx;
    Patient temp;
    leftIdx = getLeftChild(index);
    rightIdx = getRightChild(index);

    // check if there are any children and find the max child
    if (rightIdx >= patientNum) {
        if (leftIdx >= patientNum)
            return;
        else
            maxIdx = leftIdx;
    }
    else {
        if (vp[leftIdx] > vp[rightIdx])
            maxIdx = leftIdx;
        else
            maxIdx = rightIdx;
    }

    // if the max child is greater, swap
    if (vp[index] < vp[maxIdx]) {
        temp = vp[maxIdx];
        vp[maxIdx] = vp[index];
        vp[index] = temp;
        siftDown(maxIdx);
    }
}

void PatientPriorityQueuex::sortArrival(int index) {
    // selection sort
    int min_Idx;
    Patient temp;

    for (int i = 0; i < index - 1; i++) {

        min_Idx = i;
        for (int j = i + 1; j < index; j++) {
            if (vp[j].getArrival() < vp[min_Idx].getArrival())
                min_Idx = j;
        }

        // swap
        if (min_Idx != i) {
            temp = vp[i];
            vp[i] = vp[min_Idx];
            vp[min_Idx] = temp;
        }
    }
}

int PatientPriorityQueuex::binarySearch(int key) const {
    // binary search
    int leftIdx, rightIdx, midIdx;
    leftIdx = 0;
    rightIdx = size();

    while (leftIdx <= rightIdx) {
        midIdx = leftIdx + (rightIdx - 1) / 2;

        if (vp[midIdx].getArrival() == key)
            return midIdx;

        if (vp[midIdx].getArrival() < key)
            leftIdx = midIdx + 1;

        else
            rightIdx = midIdx - 1;
    }
    return -1;
}

int PatientPriorityQueuex::getParent(int index) const {
    return (index - 1) / 2;
}

int PatientPriorityQueuex::getLeftChild(int index) const {
    return 2 * index + 1;
}

int PatientPriorityQueuex::getRightChild(int index) const {
    return 2 * index + 2;
}

#endif //P3X_PATIENTPRIORITYQUEUEX_H
