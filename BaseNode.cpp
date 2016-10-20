// Kyle Murdoch
// kwm150130
// CS 1337 008

#include "BaseNode.h"

// constructors
BaseNode::BaseNode() { // default constructor
    name = "";
    highscore = 0;
    initials = new char [4];
    *initials = '\0';
    plays = 0;
    revenue = 0.00;
}
BaseNode::BaseNode(string n, int h, char *i, int p, float r) { // overloaded constructor
    name = n;
    highscore = h;
    initials = new char [4];
    strncpy(initials, i, 3);
    initials[3] = '\0';
    plays = p;
    revenue = r;
}
BaseNode::BaseNode(const BaseNode& obj) { // copy constructor
    name = obj.name;
    highscore = obj.highscore;
    initials = new char[4];
    strncpy(initials, obj.initials, 3);
    initials[3] = '\0';
    plays = obj.plays;
    revenue = obj.revenue;
}

// member functions
void BaseNode::setPlays(int p) {
    plays = p;
    if (plays > 500) {
        revenue = plays * 0.25;
    }
    else {
        revenue = plays * 0.50;
    }
}

// overloaded operators
ostream& operator<< (ostream &out, const BaseNode &obj) {
    out << "Name: " << obj.name << endl
        << "High Score: " << obj.highscore << endl
        << "Initials: " << obj.initials << endl
        << "Plays: " << obj.plays << endl
        << fixed << setprecision(2)
        << "Revenue: $" << obj.revenue << endl << endl;

    return out;
}
istream& operator>> (istream &in, BaseNode &obj) {
    cout << "Enter name of game ==> ";
    getline(in, obj.name);
    cout << "Enter High Score ==> ";
    in >> obj.highscore;
    cout << "Enter initials ==> ";
    in >> obj.initials;
    cout << "Enter number of plays ==> ";
    in >> obj.plays;
    cout << "Enter the revenue ==> ";
    in >> obj.revenue;
    cout << endl;

    return in;
}
