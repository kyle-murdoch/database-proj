// Kyle Murdoch
// kwm150130
// CS 1337 008

#include "BaseNode.h"
#include "DoubleLinkNode.h"
#include "LinkedList.h"

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

// function prototypes
void getData(ifstream &, LinkedList*);
void addRecord(LinkedList*, ifstream &, ofstream &);
void searchRecords(LinkedList*, ifstream &, ofstream &);
void editRecord(LinkedList*, ifstream &, ofstream &);
void deleteRecord(LinkedList*, ifstream &, ofstream &);
void sortRecords(LinkedList*, ifstream &, ofstream &);
void swapNode(LinkedList*, DoubleLinkNode* &, DoubleLinkNode* &);

int main() {
    ifstream update("update.txt", ios::binary);
    ifstream datFile("freeplay.dat", ios::binary);;
    ofstream logFile("freeplay.log");

    if (update.fail()) {
        cout << "ERROR: UPDATE FILE NOT FOUND" << endl;
        return 1;
    }

    // create linked list
    LinkedList *mylist = new LinkedList;

    // get data for linked list
    if (!datFile.fail()) {
        getData(datFile, mylist);
    }

    int num = 0;
    while (update >> num) {
    // determine which function to call
        switch (num) {
        case 1:
            addRecord(mylist, update, logFile);
            break;
        case 2:
            searchRecords(mylist, update, logFile);
            break;
        case 3:
            editRecord(mylist, update, logFile);
            break;
        case 4:
            deleteRecord(mylist, update, logFile);
            break;
        case 5:
            sortRecords(mylist, update, logFile);
            break;
        }
        cout << num << endl;
    }

    update.close();
    datFile.close();
    logFile.close();

    // print the linked list
    mylist->print();

    return 0;
}

void getData(ifstream &datFile, LinkedList *mylist) {
    string name; int highscore; int plays; float revenue;

    while (getline(datFile, name, ',')) {
        char *initials = new char[4];
        initials[3] = '\0';

        // get data from database file
        datFile >> highscore;
        datFile.seekg(1, ios::cur);
        datFile >> initials;
        initials[3] = '\0';
        datFile >> plays;
        datFile.seekg(3, ios::cur);
        datFile >> revenue;
        datFile.seekg(2, ios::cur);

        // create node and insert data
        DoubleLinkNode *node = new DoubleLinkNode;
        node->setName(name);
        node->setScore(highscore);
        node->setInitials(initials);
        node->setPlays(plays);
        node->setRevenue(revenue);

        // add node to linked list
        if (mylist->getTail() == nullptr || mylist->getHead() == nullptr) {
            mylist->setHead(node);
            mylist->setTail(node);
        }
        else {
            mylist->getHead()->setPrev(node);
            node->setNext(mylist->getHead());
            mylist->setHead(node);
        }
    }
}

void addRecord(LinkedList *mylist, ifstream &update, ofstream &logFile) {
    string name; int highscore; int plays; float revenue;
    char* initials = new char[4];
    initials[3] = '\0';

    // get data from update file
    int pos = update.tellg();
    update.seekg(2, ios::cur);
    getline(update, name, '"');
    update >> highscore;
    update >> initials;
    initials[3] = '\0';
    update >> plays;
    update.seekg(2, ios::cur);
    update >> revenue;

    // input validation
    if (highscore > 999999999 || highscore < 0) {
        logFile << "High Score OUT OF BOUNDS" << endl << endl;
        update.seekg(pos, ios::beg);
        string trash;
        getline(update, trash);
        return;
    }
    for (int i = 0; i < strlen(initials); i++) {
        if (isdigit(initials[i])) {
            logFile << "Initials MUST BE CHARACTERS" << endl << endl;
            update.seekg(pos, ios::beg);
            string trash;
            getline(update, trash);
            return;
        }
    }
    if (plays > 9999 || plays < 0) {
        logFile << "Plays OUT OF BOUNDS" << endl << endl;
        update.seekg(pos, ios::beg);
        string trash;
        getline(update, trash);
        return;
    }
    if (revenue > 9999.99 || revenue < 0) {
        logFile << "Revenue OUT OF BOUNDS" << endl << endl;
        update.seekg(pos, ios::beg);
        string trash;
        getline(update, trash);
        return;
    }

    // put data into a node
    DoubleLinkNode *node = new DoubleLinkNode;
    node->setName(name);
    node->setScore(highscore);
    node->setInitials(initials);
    node->setPlays(plays);
    node->setRevenue(revenue);

    // apply node to linked list
    if (mylist->getTail() == nullptr || mylist->getHead() == nullptr) {
        mylist->setHead(node);
        mylist->setTail(node);
    }
    else {
        mylist->getHead()->setPrev(node);
        node->setNext(mylist->getHead());
        mylist->setHead(node);
    }

    // log information
    logFile << "RECORD ADDED" << endl;
    logFile << *node;
}

void searchRecords(LinkedList *mylist, ifstream &update, ofstream &logFile) {
    // convert string into cstring
    bool found = false;
    string name1;
    update.seekg(1, ios::cur);
    int pos = update.tellg();
    getline(update, name1);

    update.seekg(pos, ios::beg);
    char *cstr = new char[name1.length()];
    update.get(cstr, name1.length());
    string term = cstr;
    int length = term.length();

    // determine if cstring is a number
    bool digit = false;
    for (int i = 0; i < length; i++) {
        if (isdigit(cstr[i])) {
            digit = true;
        }
        else {
            digit = false;
            break;
        }
    }

    // display node of position <pos>
    if (digit) {
        int num = atoi(cstr);
        if ((*mylist)[num] != nullptr) {
            logFile << "NODE #" << num << endl;
            logFile << *(*mylist)[num];
        }
        else {
            logFile << "NUMBER OUT OF BOUNDS" << endl << endl;
        }

        return;
    }

    // search the name of games for term
    DoubleLinkNode* node = mylist->getHead();
    while (node != nullptr) {
        // convert name into a cstring
        string name_str = node->getName();
        int nameLength = name_str.length();
        char *name = new char[nameLength + 1];
        strcpy(name, name_str.c_str());
        name[nameLength] = '\0';

        // determine if name matches search term
        bool match = false;
        for (int i = 0; i < nameLength; i++) {
            for (int j = 0; j < length; j++) {
                if (toupper(name[i + j]) == toupper(cstr[j])) {
                    match = true;
                }
                else {
                    match = false;
                    break;
                }
            }
            if (match) {
                break;
            }
        }

        // print out proper data
        if (match) {
            found = true;
            logFile << name << " FOUND" << endl;
            logFile << *node;
        }

        node = node->getNext();
    }

    // determine if nothing was found
    if (!found) {
        logFile << cstr << " NOT FOUND" << endl << endl;
    }

    cout << update.tellg() << endl;
}

void editRecord(LinkedList *mylist, ifstream &update, ofstream &logFile) {
    int pos = update.tellg();
    string name;
    update.seekg(2, ios::cur);
    getline(update, name, '"');

    DoubleLinkNode *node = mylist->getHead();
    bool found = false;

    while (!found && node != nullptr) {
        if (node->getName() == name) {
            found = true;
        }
        else {
            node = node->getNext();
        }
    }
    if (!found) {
        logFile << "RECORD NOT FOUND" << endl << endl;
        string trash;
        getline(update, trash);
        return;
    }

    int task = 0;
    update >> task;

    // validate input
    if (task > 3 || task < 1) {
        logFile << "Number OUT OF BOUNDS" << endl << endl;
        update.seekg(pos, ios::beg);
        string trash;
        getline(update, trash);
        return;
    }


    // determine which task to execute
    int highscore;
    char *initials = new char[4];
    initials[3] = '\0';
    int plays;
    string trash;
    switch (task) {
    case 1:
        update >> highscore;

        // validate input
        if (highscore > 999999999 || highscore < 0) {
            logFile << "High Score OUT OF BOUNDS" << endl << endl;
            update.seekg(pos, ios::beg);
            string trash;
            getline(update, trash);
            return;
        }

        update.seekg(-1, ios::cur);

        getline(update, trash);
        node->setScore(highscore);

        logFile << name << " UPDATED" << endl;
        logFile << "UPDATE TO High Score - VALUE " << highscore << endl;
        logFile << *node;
        break;
    case 2:
        update >> initials;
        initials[3] = '\0';

        // validate input
        for (int i = 0; i < strlen(initials); i++) {
            if (isdigit(initials[i])) {
                logFile << "Initials MUST BE CHARACTERS" << endl << endl;
                update.seekg(pos, ios::beg);
                string trash;
                getline(update, trash);
                return;
            }
        }

        update.seekg(-1, ios::cur);
        getline(update, trash);

        node->setInitials(initials);

        logFile << name << " UPDATED" << endl;
        logFile << "UPDATE TO Initials - VALUE " << initials << endl;
        logFile << *node;
        break;
    case 3:
        update >> plays;

        // validate input
        if (plays > 9999 || plays < 0) {
            logFile << "Plays OUT OF BOUNDS" << endl << endl;
            update.seekg(pos, ios::beg);
            string trash;
            getline(update, trash);
            return;
        }

        update.seekg(-1, ios::cur);
        getline(update, trash);

        node->setPlays(plays);

        logFile << name << " UPDATED" << endl;
        logFile << "UPDATE TO Plays - VALUE " << plays << endl;
        logFile << *node;
        break;
    }
}

void deleteRecord(LinkedList *mylist, ifstream &update, ofstream &logFile) {
    // get data from update file
    bool found = false;
    string name1;
    update.seekg(1, ios::cur);
    int pos = update.tellg();
    getline(update, name1);

    update.seekg(pos, ios::beg);
    char *cstr = new char[name1.length()];
    update.get(cstr, name1.length());
    string name = cstr;

    DoubleLinkNode *node = mylist->getHead();

    // determine if search term is in list
    while (node != nullptr) {
        if (node->getName() == name) {
            found = true;
            break;
        }
        else {
            node = node->getNext();
        }
    }
    if (!found) {
        logFile << "RECORD NOT FOUND" << endl << endl;
        string trash;
        getline(update, trash);
        return;
    }
    else {
        logFile << "RECORD DELETED" << endl;
        logFile << *node;
    }

    // remove node from linked list
    if (node->getPrev() != nullptr) {
        node->getPrev()->setNext(node->getNext());
    }
    if (node->getNext() != nullptr) {
        node->getNext()->setPrev(node->getPrev());
    }

    if (node == mylist->getTail()) {
        mylist->setTail(node->getPrev());
    }
    if (node == mylist->getHead()) {
        mylist->setHead(node->getNext());
    }

    // delete node
    delete node;
}

void sortRecords(LinkedList *mylist, ifstream &update, ofstream &logFile) {
    int pos = update.tellg();
    string type, command;
    update >> type;

    if (type != "asc" || type != "des") {
        logFile << "COMMAND NOT FOUND" << endl << endl;
        update.seekg(pos, ios::beg);
        string trash;
        getline(update, trash);
        return;
    }

    update >> command;

    if (command != "name" || command != "plays" || command != "revenue") {
        logFile << "COMMAND NOT FOUND" << endl << endl;
        update.seekg(pos, ios::cur);
        string trash;
        getline(update, trash);
        return;
    }

    DoubleLinkNode *node = mylist->getHead();

    // simple bubble sort based on command and type
    bool done = false;
    while (!done) {
        done = true;
        DoubleLinkNode *ptr1 = mylist->getHead();
        DoubleLinkNode *ptr2;
        while (ptr1->getNext() != nullptr) {
            ptr2 = ptr1->getNext();
            if (command == "name") {
                if (type == "des") {
                    if (ptr1->getName() > ptr2->getName()) {
                        swapNode(mylist, ptr1, ptr2);

                        done = false;
                    }
                }
                else if (type == "asc") {
                     if (ptr1->getName() < ptr2->getName()) {
                        swapNode(mylist, ptr1, ptr2);

                        done = false;
                    }
                }
            }
            else if (command == "plays") {
                if (type == "des") {
                    if (ptr1->getPlays() > ptr2->getPlays()) {
                        swapNode(mylist, ptr1, ptr2);

                        done = false;
                    }
                }
                else if (type == "asc") {
                     if (ptr1->getPlays() < ptr2->getPlays()) {
                        swapNode(mylist, ptr1, ptr2);

                        done = false;
                    }
                }
            }
            else if (command == "revenue") {
                if (type == "des") {
                    if (ptr1->getRevenue() > ptr2->getRevenue()) {
                        swapNode(mylist, ptr1, ptr2);

                        done = false;
                    }
                }
                else if (type == "asc") {
                     if (ptr1->getRevenue() < ptr2->getRevenue()) {
                        swapNode(mylist, ptr1, ptr2);

                        done = false;
                    }
                }
            }
            ptr1 = ptr1->getNext();
        }
    }
    logFile << "RECORDS SORTED BY " << command;
    if (type == "asc") {
        logFile << " ASCENDING" << endl << endl;
    }
    else if (type == "des") {
        logFile << " DESCENDING" << endl << endl;
    }
}

void swapNode(LinkedList *mylist, DoubleLinkNode* &ptr1, DoubleLinkNode* &ptr2) {
    if (ptr1 == mylist->getHead()) {
        mylist->setHead(ptr2);
    }
    if (ptr2 == mylist->getTail()) {
        mylist->setTail(ptr1);
    }
    if (ptr1->getPrev() != nullptr) {
        ptr1->getPrev()->setNext(ptr2);
    }
    if (ptr2->getNext() != nullptr) {
        ptr2->getNext()->setPrev(ptr1);
    }
    ptr1->setNext(ptr2->getNext());
    ptr2->setPrev(ptr1->getPrev());
    ptr2->setNext(ptr1);
    ptr1->setPrev(ptr2);

    DoubleLinkNode *temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;

    /**********************
    1 next points at 3
    4 prev points at 2
    2 next points at 4
    3 prev points at 1
    3 next points at 2
    2 prev points at 3
    ***********************/

    /***************************************************************

    SWAPPING 2 AND 3
    *********   *********   *********   *********   *********
    *       *   *       *   *       *   *       *   *       *
    *   1   *   *   2   *   *   3   *   *   4   *   *   5   *
    *       *   *       *   *       *   *       *   *       *
    *********   *********   *********   *********   *********

    ****************************************************************/
}
