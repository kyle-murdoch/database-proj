// Kyle Murdoch
// kwm150130
// CS 1337 008

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "DoubleLinkNode.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;

class LinkedList {
protected:
    DoubleLinkNode *head;
    DoubleLinkNode *tail;
public:
    // constructors
    LinkedList(); // default constructor
    LinkedList(DoubleLinkNode*, DoubleLinkNode*); // overloaded constructor
    LinkedList(const LinkedList&); // copy constructor

    // destructor
    ~LinkedList();
    void destructor(DoubleLinkNode*);

    // accessors
    DoubleLinkNode* getHead() {
        return head;
    }
    DoubleLinkNode* getTail() {
        return tail;
    }

    // mutators
    void setHead(DoubleLinkNode* h) {
        head = h;
    }
    void setTail(DoubleLinkNode* t) {
        tail = t;
    }

    // recursively write to file
    void print();
    void recursivePrint(DoubleLinkNode*, ofstream &);

    // overloaded operators
    DoubleLinkNode* &operator[] (int);

    // format numbers
    char* formatNum(int, int);
};

#endif // LINKEDLIST_H
