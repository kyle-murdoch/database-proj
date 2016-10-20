// Kyle Murdoch
// kwm150130
// CS 1337 008

#include "DoubleLinkNode.h"

// default constructor
DoubleLinkNode::DoubleLinkNode() : BaseNode() {
    prev = nullptr;
    next = nullptr;
}

// overloaded constructor
DoubleLinkNode::DoubleLinkNode(string n, int h, char *i, int p, float r, DoubleLinkNode *pv, DoubleLinkNode *nx) : BaseNode(n, h, i, p, r) {
    prev = pv;
    next = nx;
}

// copy constructor
DoubleLinkNode::DoubleLinkNode(const DoubleLinkNode &obj) : BaseNode(obj) {
    prev = obj.prev;
    next = obj.next;
}
