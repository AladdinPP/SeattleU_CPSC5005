// AUTHOR:      Hongru He
// FILENAME:    PatientPriorityQueue.h
// DATE:        11/13/2023
// PURPOSE:     Create the patient priority queue instance; functions
//              including constructor, add, peek, remove, size, and
//              to_string; every change made to the vector based on heap order

#include "Patient.h"
#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

class PatientPriorityQueue {
public:
    PatientPriorityQueue();
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

    int size() const;
    // get the number of patients in the queue
    // pre:     none
    // post:    none

    string to_string() const;
    // convert the instance content into a string
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

PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 1;
    patientNum = 0;
}

void PatientPriorityQueue::add(Patient & pNew) {
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

Patient PatientPriorityQueue::peek() const {
    assert(!vp.empty());
    return vp.front();
}

Patient PatientPriorityQueue::remove() {
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

int PatientPriorityQueue::size() const {
    return patientNum;
}

string PatientPriorityQueue::to_string() const {
    stringstream ss;
    for (int i = 0; i < patientNum; i++)
        ss << "     " << vp[i].getArrival() << "\t\t" << vp[i].getPriority()
        << "  \t" << vp[i].getName() << endl;
    return ss.str();
}

void PatientPriorityQueue::siftUp(int index) {
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

void PatientPriorityQueue::siftDown(int index) {
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

int PatientPriorityQueue::getParent(int index) const {
    return (index - 1) / 2;
}

int PatientPriorityQueue::getLeftChild(int index) const {
    return 2 * index + 1;
}

int PatientPriorityQueue::getRightChild(int index) const {
    return 2 * index + 2;
}

#endif //P3_PATIENTPRIORITYQUEUE_H
