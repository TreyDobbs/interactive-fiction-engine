// --------------------------------------------------------------------------
// Name: Trey Dobbs
// Description: This C++ project adds support for in-game items to our 
// interactive fiction engine. Item support has been added to Area and
// Player, the map constructor has been updated, five new commands including 
// search, inventory, take, leave, and examine have been added, and the help
// and cheat commands have been updated.
// --------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "ull.h"
#include "Item.h"

using namespace std;

class Area {
public:
    uLList<Item*> areaItems;

    void setDescription(string desc) {
        description = desc;
    }
    void setGoal(bool g) {
        goal = g;
    }
    void setID(bool id) {
        instadeath = id;
    }
    string getDescription() {
        return description;
    }
    bool getID() {
        return instadeath;
    }
    bool getGoal() {
        return goal;
    }
    void displayArea() {
        cout << description << endl;
    }

    //search command prints the names of all items in an area
    void search() {
        areaItems.printNames();
    }


private:
    string description;
    bool instadeath;
    bool goal;
};
#pragma once
