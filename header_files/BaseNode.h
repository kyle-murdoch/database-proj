// Kyle Murdoch
// kwm150130
// CS 1337 008

#ifndef BASENODE_H
#define BASENODE_H

#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

class BaseNode; // forward declaration
ostream& operator<< (ostream&, const BaseNode&);
istream& operator>> (istream&, const BaseNode&);

class BaseNode {
protected:
    string name;
    int highscore;
    char *initials;
    int plays;
    float revenue;
public:
    BaseNode(); // default constructor
    BaseNode(string, int, char*, int, float); // overloaded constructor
    BaseNode(const BaseNode&); // copy constructor

    // accessors
    string getName() {
        return name;
    }
    int getScore() {
        return highscore;
    }
    char* getInitials() {
        return initials;
    }
    int getPlays() {
        return plays;
    }
    float getRevenue() {
        return revenue;
    }

    // mutators
    virtual void setName(string n) = 0; // pure virtual function

    void setScore(int h) {
        highscore = h;
    }
    void setInitials(char *i) {
        initials = i;
    }

    void setPlays(int);

    void setRevenue(float r) {
        revenue = r;
    }

    // overloaded operators
    friend ostream& operator<< (ostream&, const BaseNode&);
    friend istream& operator>> (istream&, BaseNode&);
};

#endif // BASENODE_H
