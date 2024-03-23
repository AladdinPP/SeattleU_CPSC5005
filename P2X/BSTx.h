

#ifndef P2X_BSTX_H
#define P2X_BSTX_H

#include <iostream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

template <typename T>
class BSTx {
public:
    BSTx();
    ~BSTx();
    BSTx(const BSTx<T>&);
    BSTx&operator=(const BSTx<T>&);
    void insert(T);
    bool contains(T);
    void remove(T);
    bool empty();
    int size() const;
    int getLeafCount() const;
    int getHeight() const;
    int getWidth() const;
    int getLevel(T) const;
    string getPreOrderTraversal();
    string getInOrderTraversal();
    string getPostOrderTraversal();
    string getAncestors(T);
    string getLevelOrder() const;

private:
    struct Node {
        T data;
        Node * left;
        Node * right;
    };
    Node * root;

    void destroyTree(Node *&);
    void copyTree(Node*&, const Node*);
    void insert(Node *&, Node *);
    bool contains(T, Node *);
    void remove(Node *&, T);
    void makeDeletion(Node *&, T);
    int size(Node *) const;
    int getLeafCount(Node *) const;
    int getHeight(Node *) const;
    int getWidth(Node *, int) const;
    int getLevel(Node *, T, int) const;
    string getPreOrderTraversal(Node *);
    string getInOrderTraversal(Node *);
    string getPostOrderTraversal(Node *);
    string getAncestors(Node *, T);
    string reverseString(string &);
};

template <typename T>
BSTx<T>::BSTx() {
    root = nullptr;
}

template <typename T>
BSTx<T>::~BSTx() {
    destroyTree(root);
}

template <typename T>
void BSTx<T>::destroyTree(Node *&ptr) {
    if (ptr != nullptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
}

template <typename T>
BSTx<T>::BSTx(const BSTx<T>& origin) {
    root = nullptr;
    copyTree(root, origin.root);
}

template <typename T>
BSTx<T>& BSTx<T>::operator=(const BSTx<T>& target) {
    if (this != &target) {
        destroyTree(root);
        copyTree(root, target.root);
    }
    return *this;
}

template <typename T>
void BSTx<T>::copyTree(Node*& origin, const Node * ptr) {
    if (ptr != nullptr) {
        origin = new Node;
        origin->data = ptr->data;
        origin->left = nullptr;
        origin->right = nullptr;
        copyTree(origin->left, ptr->left);
        copyTree(origin->right, ptr->right);
    }
}

template <typename T>
void BSTx<T>::insert(T item) {
    Node * newNode = new Node;
    newNode->data = item;
    newNode->left = newNode->right = nullptr;
    insert(root, newNode);
}

template <typename T>
void BSTx<T>::insert(Node *& ptr, Node * newNode) {
    if (ptr == nullptr)
        ptr = newNode;
    else if (ptr->data > newNode->data)
        insert(ptr->left, newNode);
    else
        insert(ptr->right, newNode);
}

template <typename T>
bool BSTx<T>::contains(T item) {
    return contains(item, root);
}

template <typename T>
bool BSTx<T>::contains(T item, Node * ptr) {
    if (ptr == nullptr)
        return false;
    if (ptr->data == item)
        return true;
    if (ptr->data > item)
        return contains(item, ptr->left);
    return contains(item, ptr->right);
}

template <typename T>
void BSTx<T>::remove(T item) {
    remove(root, item);
}

template <typename T>
void BSTx<T>::remove(Node *& ptr, T item) {
    if (ptr != nullptr) {
        if (ptr->data > item)
            remove(ptr->left, item);
        else if (ptr->data < item)
            remove(ptr->right, item);
        else
            makeDeletion(ptr, item);
    }
}

template <typename T>
void BSTx<T>::makeDeletion(Node *& ptr, T item) {
    Node * curr = nullptr;
    if (ptr != nullptr) {
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
bool BSTx<T>::empty() {
    return root == nullptr;
}

template <typename T>
int BSTx<T>::size() const{
    return size(root);
}

template <typename T>
int BSTx<T>::size(Node * ptr) const {
    if (ptr == nullptr)
        return 0;
    return 1 + size(ptr->left) + size(ptr->right);
}

template <typename T>
int BSTx<T>::getLeafCount() const {
    if (root == nullptr)
        return 0;
    else
        return getLeafCount(root);
}

template <typename T>
int BSTx<T>::getLeafCount(Node * ptr) const {
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
int BSTx<T>::getHeight() const {
    return getHeight(root);
}

template <typename T>
int BSTx<T>::getHeight(Node * ptr) const {
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
int BSTx<T>::getWidth() const {
    int height = getHeight(root);
    int maxWidth = 0;

    for (int i = 0; i <= height + 1; ++i) {
        int levelWidth = getWidth(root, i);
        if (maxWidth < levelWidth)
            maxWidth = levelWidth;
    }
    return maxWidth;
}

template <typename T>
int BSTx<T>::getWidth(Node * ptr, int level) const {
    if (ptr == nullptr)
        return 0;

    if (level == 0)
        return 1;

    return getWidth(ptr->left, level - 1) + getWidth(ptr->right, level - 1);
}

template <typename T>
int BSTx<T>::getLevel(T item) const {
    int height = getHeight();
    if (getLevel(root, item, 0) > height)
        return -1;
    return getLevel(root, item, 0);
}

template <typename T>
int BSTx<T>::getLevel(Node * ptr, T item, int level) const {
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
string BSTx<T>::getPreOrderTraversal() {
    return getPreOrderTraversal(root);
}

template <typename T>
string BSTx<T>::getPreOrderTraversal(Node * ptr) {
    if (ptr == nullptr)
        return "";

    stringstream ss;
    ss << ptr->data << " ";
    ss << getPreOrderTraversal(ptr->left);
    ss << getPreOrderTraversal(ptr->right);

    return ss.str();
}

template <typename T>
string BSTx<T>::getInOrderTraversal() {
    return getInOrderTraversal(root);
}

template <typename T>
string BSTx<T>::getInOrderTraversal(Node * ptr) {
    if (ptr == nullptr)
        return "";

    stringstream ss;
    ss << getInOrderTraversal(ptr->left);
    ss << ptr->data << " ";
    ss << getInOrderTraversal(ptr->right);

    return ss.str();
}

template <typename T>
string BSTx<T>::getPostOrderTraversal() {
    return getPostOrderTraversal(root);
}

template <typename T>
string BSTx<T>::getPostOrderTraversal(Node * ptr) {
    if (ptr == nullptr)
        return "";

    stringstream ss;
    ss << getPostOrderTraversal(ptr->left);
    ss << getPostOrderTraversal(ptr->right);
    ss << ptr->data << " ";

    return ss.str();
}

template <typename T>
string BSTx<T>::getAncestors(T item) {
    return getAncestors(root, item);
}

template <typename T>
string BSTx<T>::getAncestors(Node * ptr, T item) {
    if (ptr->data == item)
        return "";
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

    return reverseString(ancestor);
}

template <typename T>
string BSTx<T>::reverseString(string & origin) {
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

template <typename T>
string BSTx<T>::getLevelOrder() const {
    if (root == nullptr)
        return "";

    stringstream ss;
    queue<Node *> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        Node * curr = nodeQueue.front();
        nodeQueue.pop();

        ss << curr->data << " ";

        if (curr->left != nullptr)
            nodeQueue.push(curr->left);
        if (curr->right != nullptr)
            nodeQueue.push(curr->right);
    }

    return ss.str();
}

#endif //P2X_BSTX_H
