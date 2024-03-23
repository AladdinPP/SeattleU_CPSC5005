// AUTHOR:  Hongru He
// FILE:    p2x.cpp
// DATE:    10/31/2023

#include "BSTx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    // welcome message
    cout << "\nWelcome to the PLAY WITH BST program! Here, you can play with\n"
            "the binary search tree using any files (text or numeric) you\n"
            "have. The program will create a BST based on the file you\n"
            "provide. You can get the height, three orders displays, insert\n"
            "new elements, remove elements, check if a specific element is\n"
            "in the tree, etc." << endl;

    // create general variables
    string filename, fileContent;

    // start with the integer BST
    cout << "\n* INTEGER BINARY SEARCH TREE *" << endl;

    // initiate the BST
    cout << "\n** CREATE TREE **" << endl;
    BSTx<int> treeInt;

    // display information before inserting anything
    cout << "# of nodes:    " << treeInt.size() << endl;
    cout << "# of leaves:   " << treeInt.getLeafCount() << endl;
    cout << "BST height:    " << treeInt.getHeight() << endl;
    cout << "BST width:     " << treeInt.getWidth() << endl;
    cout << "BST empty?     " << boolalpha << treeInt.empty() << endl;

    // prompt for integer file name
    cout << "\nEnter integer file:    ";
    cin >> filename;

    // open the file
    ifstream inFile(filename);
    stringstream display;
    while (getline(inFile, fileContent)) {
        stringstream ss;
        int element;
        ss << fileContent;
        ss >> element;
        treeInt.insert(element);
        display << fileContent << " ";
    }

    inFile.close();

    // display information of current tree
    cout << "\n** TEST INSERT **" << endl;
    cout << "Inserting in this order:   " << display.str() << endl;
    cout << "# of nodes:    " << treeInt.size() << endl;
    cout << "# of leaves:   " << treeInt.getLeafCount() << endl;
    cout << "BST height:    " << treeInt.getHeight() << endl;
    cout << "BST width:     " << treeInt.getWidth() << endl;
    cout << "BST empty?     " << boolalpha << treeInt.empty() << endl;

    // test traversal
    cout << "\n** TEST TRAVERSAL **" << endl;
    cout << "pre-order:     " << treeInt.getPreOrderTraversal() << endl;
    cout << "in-order:      " << treeInt.getInOrderTraversal() << endl;
    cout << "post-order:    " << treeInt.getPostOrderTraversal() << endl;

    // test level and ancestors
    cout << "\n** TEST LEVEL & ANCESTORS **" << endl;
    cout << "level(40): " << treeInt.getLevel(40) << ", ancestor(40): "
         << treeInt.getAncestors(40) << endl;
    cout << "level(20): " << treeInt.getLevel(20) << ", ancestor(20): "
         << treeInt.getAncestors(20) << endl;
    cout << "level(10): " << treeInt.getLevel(10) << ", ancestor(10): "
         << treeInt.getAncestors(10) << endl;
    cout << "level(30): " << treeInt.getLevel(30) << ", ancestor(30): "
         << treeInt.getAncestors(30) << endl;
    cout << "level(60): " << treeInt.getLevel(60) << ", ancestor(60): "
         << treeInt.getAncestors(60) << endl;
    cout << "level(50): " << treeInt.getLevel(50) << ", ancestor(50): "
         << treeInt.getAncestors(50) << endl;
    cout << "level(70): " << treeInt.getLevel(70) << ", ancestor(70): "
         << treeInt.getAncestors(70) << endl;

    // test contains
    cout << "\n** TEST CONTAINS **" << endl;
    cout << "contains(20):  " << boolalpha <<
         treeInt.contains(20) << endl;
    cout << "contains(40):  " << boolalpha <<
         treeInt.contains(40) << endl;
    cout << "contains(10):  " << boolalpha <<
         treeInt.contains(10) << endl;
    cout << "contains(70):  " << boolalpha <<
         treeInt.contains(70) << endl;
    cout << "contains(99):  " << boolalpha <<
         treeInt.contains(99) << endl;
    cout << "contains(-2):  " << boolalpha <<
         treeInt.contains(-2) << endl;
    cout << "contains(59):  " << boolalpha <<
         treeInt.contains(59) << endl;
    cout << "contains(43):  " << boolalpha <<
         treeInt.contains(43) << endl;

    // test get level in order
    cout << "\n** TEST GET LEVEL IN ORDER **" << endl;
    cout << "Display the BST from root to leaf, left to right, level by "
            "level:\n" << treeInt.getLevelOrder() << endl;

    // test remove
    cout << "\n** TEST REMOVE **" << endl;
    cout << "Removing in this order: 20 40 10 70 99 -2 59 43" << endl;
    int intList[8] = {20, 40, 10, 70, 99,
                      -2, 59, 43};
    for (int i : intList)
        treeInt.remove(i);
    cout << "# of nodes:    " << treeInt.size() << endl;
    cout << "# of leaves:   " << treeInt.getLeafCount() << endl;
    cout << "tree height:   " << treeInt.getHeight() << endl;
    cout << "BST width:     " << treeInt.getWidth() << endl;
    cout << "tree empty?    " << boolalpha << treeInt.empty() << endl;
    cout << "pre-order:     " << treeInt.getPreOrderTraversal() << endl;
    cout << "in-order:      " << treeInt.getInOrderTraversal() << endl;
    cout << "post-order:    " << treeInt.getPostOrderTraversal() << endl;

    // test insert again
    cout << "\n** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: 20 40 10 70 99 -1 59 43" << endl;
    for (int i : intList)
        treeInt.insert(i);
    cout << "# of nodes:    " << treeInt.size() << endl;
    cout << "# of leaves:   " << treeInt.getLeafCount() << endl;
    cout << "tree height:   " << treeInt.getHeight() << endl;
    cout << "BST width:     " << treeInt.getWidth() << endl;
    cout << "tree empty?    " << boolalpha << treeInt.empty() << endl;
    cout << "pre-order:     " << treeInt.getPreOrderTraversal() << endl;
    cout << "in-order:      " << treeInt.getInOrderTraversal() << endl;
    cout << "post-order:    " << treeInt.getPostOrderTraversal() << endl;

    // test with string file
    cout << "\n* TEST STRING BST *" << endl;

    // initiate the BST
    cout << "\n** CREATE BST **" << endl;
    BSTx<string> treeStr;

    // display information before inserting anything
    cout << "# of nodes:    " << treeStr.size() << endl;
    cout << "# of leaves:   " << treeStr.getLeafCount() << endl;
    cout << "BST height:    " << treeStr.getHeight() << endl;
    cout << "BST empty?     " << boolalpha << treeStr.empty() << endl;

    // prompt for string file name
    cout << "\nEnter string file:    ";
    cin >> filename;

    // open the file
    ifstream inFile1(filename);
    stringstream display1;
    while (getline(inFile1, fileContent)) {
        treeStr.insert(fileContent);
        display1 << fileContent << " ";
    }

    inFile1.close();

    // display information of current tree
    cout << "\n** TEST INSERT **" << endl;
    cout << "Inserting in this order:   " << display1.str() << endl;
    cout << "# of nodes:    " << treeStr.size() << endl;
    cout << "# of leaves:   " << treeStr.getLeafCount() << endl;
    cout << "BST height:    " << treeStr.getHeight() << endl;
    cout << "BST width:     " << treeStr.getWidth() << endl;
    cout << "BST empty?     " << boolalpha << treeStr.empty() << endl;

    // test traversal
    cout << "\n** TEST TRAVERSAL **" << endl;
    cout << "pre-order:     " << treeStr.getPreOrderTraversal() << endl;
    cout << "in-order:      " << treeStr.getInOrderTraversal() << endl;
    cout << "post-order:    " << treeStr.getPostOrderTraversal() << endl;

    // test level and ancestors
    cout << "\n** TEST LEVEL & ANCESTORS **" << endl;
    cout << "level(mary): " << treeStr.getLevel("mary") <<
         ", ancestor(mary): " << treeStr.getAncestors("mary") << endl;
    cout << "level(gene): " << treeStr.getLevel("gene") <<
         ", ancestor(gene): " << treeStr.getAncestors("gene") << endl;
    cout << "level(bea): " << treeStr.getLevel("bea") <<
         ", ancestor(bea): " << treeStr.getAncestors("bea") << endl;
    cout << "level(jen): " << treeStr.getLevel("jen") <<
         ", ancestor(jen): " << treeStr.getAncestors("jen") << endl;
    cout << "level(sue): " << treeStr.getLevel("sue") <<
         ", ancestor(sue): " << treeStr.getAncestors("sue") << endl;
    cout << "level(pat): " << treeStr.getLevel("pat") <<
         ", ancestor(pat): " << treeStr.getAncestors("pat") << endl;
    cout << "level(uma): " << treeStr.getLevel("uma") <<
         ", ancestor(uma): " << treeStr.getAncestors("uma") << endl;

    // test contains
    cout << "\n** TEST CONTAINS **" << endl;
    cout << "contains(gene):  " << boolalpha <<
         treeStr.contains("gene") << endl;
    cout << "contains(mary):  " << boolalpha <<
         treeStr.contains("mary") << endl;
    cout << "contains(bea):  " << boolalpha <<
         treeStr.contains("bea") << endl;
    cout << "contains(uma):  " << boolalpha <<
         treeStr.contains("uma") << endl;
    cout << "contains(yan):  " << boolalpha <<
         treeStr.contains("yan") << endl;
    cout << "contains(amy):  " << boolalpha <<
         treeStr.contains("amy") << endl;
    cout << "contains(ron):  " << boolalpha <<
         treeStr.contains("ron") << endl;
    cout << "contains(opal):  " << boolalpha <<
         treeStr.contains("opal") << endl;

    // test get level in order
    cout << "\n** TEST GET LEVEL IN ORDER **" << endl;
    cout << "Display the BST from root to leaf, left to right, level by "
            "level:\n" << treeStr.getLevelOrder() << endl;

    // test remove
    cout << "\n** TEST REMOVE **" << endl;
    cout << "Removing in this order: gene mary bea uma yan amy ron opal" <<
         endl;
    string strList[8] = {"gene", "mary", "bea", "uma",
                         "yan", "amy", "ron", "opal"};
    for (string j : strList)
        treeStr.remove(j);
    cout << "# of nodes:    " << treeStr.size() << endl;
    cout << "# of leaves:   " << treeStr.getLeafCount() << endl;
    cout << "tree height:   " << treeStr.getHeight() << endl;
    cout << "BST width:     " << treeStr.getWidth() << endl;
    cout << "tree empty?    " << boolalpha << treeStr.empty() << endl;
    cout << "pre-order:     " << treeStr.getPreOrderTraversal() << endl;
    cout << "in-order:      " << treeStr.getInOrderTraversal() << endl;
    cout << "post-order:    " << treeStr.getPostOrderTraversal() << endl;

    // test insert again
    cout << "\n** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: gene mary bea uma yan amy ron opal" <<
         endl;
    for (string j : strList)
        treeStr.insert(j);
    cout << "# of nodes:    " << treeStr.size() << endl;
    cout << "# of leaves:   " << treeStr.getLeafCount() << endl;
    cout << "tree height:   " << treeStr.getHeight() << endl;
    cout << "BST width:     " << treeStr.getWidth() << endl;
    cout << "tree empty?    " << boolalpha << treeStr.empty() << endl;
    cout << "pre-order:     " << treeStr.getPreOrderTraversal() << endl;
    cout << "in-order:      " << treeStr.getInOrderTraversal() << endl;
    cout << "post-order:    " << treeStr.getPostOrderTraversal() << endl;

    // goodbye message
    cout << "\nThanks for using PLAY WITH BST program! Goodbye!" << endl;

    return 0;
}
