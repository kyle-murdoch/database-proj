// Kyle Murdoch
// kwm150130
// CS 1337 008

#ifndef DOUBLELINKNODE_H
#define DOUBLELINKNODE_H

#include "BaseNode.h"
using namespace std;

class DoubleLinkNode : public BaseNode{
protected:
    DoubleLinkNode *next;
    DoubleLinkNode *prev;
public:
    // constructors
    DoubleLinkNode(); // default constructor
    DoubleLinkNode(string, int, char*, int, float, DoubleLinkNode*, DoubleLinkNode*); // overloaded constructor
    DoubleLinkNode(const DoubleLinkNode&); // copy constructor

    // accessors
    DoubleLinkNode* getPrev() {
        return prev;
    }
    DoubleLinkNode* getNext() {
        return next;
    }

    // mutators
    void setPrev(DoubleLinkNode *p) {
        prev = p;
    }
    void setNext(DoubleLinkNode *n) {
        next = n;
    }

    // virtual function
    void setName(string n) {
        name = n;
    }
};

#endif // DOUBLELINKNODE_H
