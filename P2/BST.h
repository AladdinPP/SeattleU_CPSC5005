// AUTHOR:      Hongru He
// FILENAME:    BST.h
// DATE:        10/31/2023
// PURPOSE:     This header file create a template BST class, to which user
//              can operate insert, remove, get leaf count, get level count,
//              get height, three traversal, etc. There are also default
//              constructor, destructor, copy, and overloaded assignment.

#ifndef P2_BST_H
#define P2_BST_H
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
class BST {
public:
    BST();
    // Default constructor
    // precondition: none
    // postcondition: root set to nullptr

    ~BST();
    // Destructor
    // precondition: none
    // postcondition: delete the whole BST

    BST(const BST<T>&);
    // Copy an existing BST
    // precondition: none
    // postcondition: create a new BST which has the same structure and
    //                elements with the given BST

    BST&operator=(const BST<T>&);
    // Overloaded assignment operator
    // precondition: none
    // postcondition: set the original BST with the same structure and
    //                elements as the given BST

    void insert(T);
    // Insert element into a BST
    // precondition: none
    // postcondition: a new element was added into the BST

    bool contains(T);
    // Check if an element is in the BST
    // precondition: none
    // postcondition: return if the element is in the BST

    void remove(T);
    // Remove element from the BST
    // precondition: none
    // postcondition: remove the given element from the BST

    bool empty();
    // Check if the BST is empty
    // precondition: none
    // postcondition: return if the BST is empty

    int size() const;
    // Count how many elements are in the BST
    // precondition: none
    // postcondition: return the number of elements in the BST

    int getLeafCount() const;
    // Count how many leaf nodes are in the BST
    // precondition: none
    // postcondition: return the number of leaf nodes in the BST

    int getHeight() const;
    // Count the height of the BST
    // precondition: none
    // postcondition: return the height of the BST

    int getLevel(T) const;
    // Find which level the given element is in
    // precondition: none
    // postcondition: return the level the given element is in

    string getPreOrderTraversal();
    // Use a string to store the preorder traversal
    // precondition: none
    // postcondition: return the string containing the preorder traversal

    string getInOrderTraversal();
    // Use a string to store the inorder traversal
    // precondition: none
    // postcondition: return the string containing the inorder traversal

    string getPostOrderTraversal();
    // Use a string to store the postorder traversal
    // precondition: none
    // postcondition: return the string containing the postorder traversal

    string getAncestors(T);
    // Find all ancestors of the given element
    // precondition: none
    // postcondition: return a string containing all the ancestors

private:
    struct Node {
        T data;
        Node * left;
        Node * right;
    };
    Node * root;            // the start point of the BST

    void destroyTree(Node *&);
    // Delete all the elements in the BST
    // precondition: none
    // postcondition: delete all the elements in preorder traversal

    void copyTree(Node*&, const Node*);
    // Copy from one BST to a new BST
    // precondition: none
    // postcondition: create a new BST which has the same structure and
    //                elements with the given BST

    void insert(Node *&, Node *);
    // Insert the given element into the appropriate position
    // precondition: none
    // postcondition: new element was added to the right position

    bool contains(T, Node *);
    // Traverse the BST to find the given element
    // precondition: none
    // postcondition: return if the given element was found

    void remove(Node *&, T);
    // Find the node which stores the given value to delete
    // precondition: none
    // postcondition: the specific node was deleted

    void makeDeletion(Node *&, T);
    // Find the node which should replace the deleted node's position
    // precondition: none
    // postcondition: the deleted node's position was replaced by appropriate
    //                node which could remain the BST's functional structure

    int size(Node *) const;
    // Traverse and count the number of nodes
    // precondition: none
    // postcondition: return the number of nodes

    int getLeafCount(Node *) const;
    // Traverse and count the number of leaf nodes
    // precondition: none
    // postcondition: return the number of leaf nodes

    int getHeight(Node *) const;
    // Traverse and find the height of the BST
    // precondition: none
    // postcondition: return the height of the BST

    int getLevel(Node *, T, int) const;
    // Traverse and find the level of the given element
    // precondition: none
    // postcondition: return the level of the given element

    string getPreOrderTraversal(Node *);
    // Store the preorder traversal in a string
    // precondition: none
    // postcondition: return the string storing preorder traversal

    string getInOrderTraversal(Node *);
    // Store the inorder traversal in a string
    // precondition: none
    // postcondition: return the string storing inorder traversal

    string getPostOrderTraversal(Node *);
    // Store the postorder traversal in a string
    // precondition: none
    // postcondition: return the string storing postorder traversal

    string getAncestors(Node *, T);
    // Traverse and store all ancestors of the given node in a string
    // precondition: none
    // postcondition: return the string storing all ancestors of the node

    string reverseString(string &);
    // Reverse the order of elements in a string
    // precondition: none
    // postcondition: return the reversed string
};

template <typename T>
BST<T>::BST() {
    root = nullptr;
}

template <typename T>
BST<T>::~BST() {
    destroyTree(root);
}

template <typename T>
void BST<T>::destroyTree(Node *&ptr) {
    if (ptr != nullptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
}

template <typename T>
BST<T>::BST(const BST<T>& origin) {
    // create a new BST
    root = nullptr;
    copyTree(root, origin.root);
}

template <typename T>
BST<T>& BST<T>::operator=(const BST<T>& target) {
    // the given BST should not be the same as the assigned BST
    if (this != &target) {
        // delete the original BST
        destroyTree(root);
        copyTree(root, target.root);
    }
    return *this;
}

template <typename T>
void BST<T>::copyTree(Node*& origin, const Node * ptr) {
    // traverse until reach the nullptr
    if (ptr != nullptr) {
        // create the new node to copy
        origin = new Node;
        origin->data = ptr->data;
        origin->left = nullptr;
        origin->right = nullptr;

        // traverse
        copyTree(origin->left, ptr->left);
        copyTree(origin->right, ptr->right);
    }
}

template <typename T>
void BST<T>::insert(T item) {
    Node * newNode = new Node;
    newNode->data = item;
    newNode->left = newNode->right = nullptr;
    insert(root, newNode);
}

template <typename T>
void BST<T>::insert(Node *& ptr, Node * newNode) {
    if (ptr == nullptr)
        ptr = newNode;
    else if (ptr->data > newNode->data)
        insert(ptr->left, newNode);
    else
        insert(ptr->right, newNode);
}

template <typename T>
bool BST<T>::contains(T item) {
    return contains(item, root);
}

template <typename T>
bool BST<T>::contains(T item, Node * ptr) {
    // when reach the leaf node, no found
    if (ptr == nullptr)
        return false;

    // or, do binary search
    if (ptr->data == item)
        return true;
    if (ptr->data > item)
        return contains(item, ptr->left);
    return contains(item, ptr->right);
}

template <typename T>
void BST<T>::remove(T item) {
    remove(root, item);
}

template <typename T>
void BST<T>::remove(Node *& ptr, T item) {
    if (ptr != nullptr) {
        // binary search to find the node to delete
        if (ptr->data > item)
            remove(ptr->left, item);
        else if (ptr->data < item)
            remove(ptr->right, item);
        else
            makeDeletion(ptr, item);
    }
}

template <typename T>
void BST<T>::makeDeletion(Node *& ptr, T item) {
    Node * curr = nullptr;
    if (ptr != nullptr) {
        // if the deleted node only have one side of children, replace with
        // the closest one
        if (ptr->left == nullptr) {
            curr = ptr;
            ptr = ptr->right;
            delete curr;
        }
        else if (ptr->right == nullptr) {
            curr = ptr;
            ptr = ptr->left;
            delete curr;
        }
        // or, traverse to find the most small child, replace with it
        else {
            curr = ptr->right;

            while (curr->left != nullptr)
                curr = curr->left;
            ptr->data = curr->data;
            remove(ptr->right, curr->data);
        }
    }
}

template <typename T>
bool BST<T>::empty() {
    return root == nullptr;
}

template <typename T>
int BST<T>::size() const{
    return size(root);
}

template <typename T>
int BST<T>::size(Node * ptr) const {
    if (ptr == nullptr)
        return 0;
    return 1 + size(ptr->left) + size(ptr->right);
}

template <typename T>
int BST<T>::getLeafCount() const {
    if (root == nullptr)
        return 0;
    else
        return getLeafCount(root);
}

template <typename T>
int BST<T>::getLeafCount(Node * ptr) const {
    int leafCount = 0;
    if (ptr != nullptr) {
        if (ptr->left == nullptr && ptr->right == nullptr)
            leafCount++;
        else {
            leafCount += getLeafCount(ptr->left);
            leafCount += getLeafCount(ptr->right);
        }
    }
    return leafCount;
}

template <typename T>
int BST<T>::getHeight() const {
    return getHeight(root);
}

template <typename T>
int BST<T>::getHeight(Node * ptr) const {
    // decrease height by 1 when reach to the nullptr (decrease the one of
    // leaf node)
    if (ptr == nullptr)
        return -1;

    int heightLeft = getHeight(ptr->left);
    int heightRight = getHeight(ptr->right);

    if (heightLeft >= heightRight)
        return 1 + heightLeft;
    else
        return 1 +heightRight;
}

template <typename T>
int BST<T>::getLevel(T item) const {
    int height = getHeight();

    // if the result is greater than the height, the given element is not in
    // the BST
    if (getLevel(root, item, 0) > height)
        return -1;
    return getLevel(root, item, 0);
}

template <typename T>
int BST<T>::getLevel(Node * ptr, T item, int level) const {
    // keep counting when reach to the nullptr, so if there is no element
    // found, the result will exceed the height of BST
    if (ptr == nullptr)
        return 1 + level;
    if (ptr->data == item)
        return level;
    if (ptr->data < item)
        return getLevel(ptr->right, item, 1 + level);
    else
        return getLevel(ptr->left, item, 1 + level);
}

template <typename T>
string BST<T>::getPreOrderTraversal() {
    return getPreOrderTraversal(root);
}

template <typename T>
string BST<T>::getPreOrderTraversal(Node * ptr) {
    if (ptr == nullptr)
        return "";

    stringstream ss;
    ss << ptr->data << " ";
    ss << getPreOrderTraversal(ptr->left);
    ss << getPreOrderTraversal(ptr->right);

    return ss.str();
}

template <typename T>
string BST<T>::getInOrderTraversal() {
    return getInOrderTraversal(root);
}

template <typename T>
string BST<T>::getInOrderTraversal(Node * ptr) {
    if (ptr == nullptr)
        return "";

    stringstream ss;
    ss << getInOrderTraversal(ptr->left);
    ss << ptr->data << " ";
    ss << getInOrderTraversal(ptr->right);

    return ss.str();
}

template <typename T>
string BST<T>::getPostOrderTraversal() {
    return getPostOrderTraversal(root);
}

template <typename T>
string BST<T>::getPostOrderTraversal(Node * ptr) {
    if (ptr == nullptr)
        return "";

    stringstream ss;
    ss << getPostOrderTraversal(ptr->left);
    ss << getPostOrderTraversal(ptr->right);
    ss << ptr->data << " ";

    return ss.str();
}

template <typename T>
string BST<T>::getAncestors(T item) {
    return getAncestors(root, item);
}

template <typename T>
string BST<T>::getAncestors(Node * ptr, T item) {
    // the ptr is the start point from which this function traverse till the
    // given nod, so if the start point is the same as the given node, there
    // is no ancestors
    if (ptr->data == item)
        return "";

    // if the given node is not in the BST, return empty string
    if (!contains(item))
        return "";

    stringstream ss;
    string ancestor;
    ss << ptr->data << " ";

    if (ptr->data > item)
        ss << getAncestors(ptr->left, item);
    else
        ss << getAncestors(ptr->right, item);

    ancestor = ss.str();

    // reverse the string to get the required result
    return reverseString(ancestor);
}

template <typename T>
string BST<T>::reverseString(string & origin) {
    istringstream iss(origin);
    string ancestor;
    string reversedString;

    while (iss >> ancestor) {
        if (!reversedString.empty()) {
            reversedString = ancestor + " " + reversedString;
        }
        else {
            reversedString = ancestor;
        }
    }

    return reversedString;
}

#endif //P2_BST_H
