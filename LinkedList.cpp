// Kyle Murdoch
// kwm150130
// CS 1337 008

#include "LinkedList.h"

// default constructor
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

// overloaded constructor
LinkedList::LinkedList(DoubleLinkNode *h, DoubleLinkNode *t) {
    head = h;
    tail = h;
}

// copy constructor
LinkedList::LinkedList(const LinkedList &obj) {
    head = obj.head;
    tail = obj.tail;
}

// destructor
LinkedList::~LinkedList() {
    destructor(head);
}

void LinkedList::destructor(DoubleLinkNode *ptr) {
    if (ptr != nullptr) {
        destructor(ptr->getNext());
        delete ptr;
    }
    else
        return;
}

// recursively write to file
void LinkedList::print() {
    ofstream datFile("freeplay.dat");
    recursivePrint(head, datFile);
    datFile.close();
}

void LinkedList::recursivePrint(DoubleLinkNode *ptr, ofstream &datFile) {
    if (ptr != nullptr) {
        recursivePrint(ptr->getNext(), datFile);

        datFile << ptr->getName() << ", "
            << formatNum(ptr->getScore(), 9) << ", "
            << ptr->getInitials() << ", "
            << formatNum(ptr->getPlays(), 4) << ", $";
            float revenue = ptr->getRevenue();
            int rev1 = revenue;
            int rev2 = (float) (revenue - rev1) * 100;
        datFile << formatNum(rev1, 4) << "." << formatNum(rev2, 2) << endl;
    }
    else
        return;
}

// overloaded operators
DoubleLinkNode* & LinkedList::operator[] (int pos) {
    DoubleLinkNode *ptr = this->head;
    for (int i = 0; i < pos; i++) {
        if (ptr == nullptr) {
            return ptr;
        }
        else {
            ptr = ptr->getNext();
        }
    }
    return ptr;
}

// format numbers
char* LinkedList::formatNum(int num, int length) {
    if (num / (int) pow(10, length) != 0) {
        string number = to_string(num);
        char *cstr = new char[number.length()];
        strcpy(cstr, number.c_str());
        return cstr;
    }

    int numZeros = 0;
    for (int i = 0; i < length; i++) {
        if (num / (int) pow(10, i) == 0) {
            numZeros++;
        }
    }

    char *number = new char[length + 1];
    int j;
    for (j = 0; j < numZeros; j++) {
        number[j] = '0';
    }
    string str = to_string(num);
    for (int k = 0; k < length - numZeros; k++) {
        number[k + j] = str[k];
    }
    number[length] = '\0';

    return number;
}
