// --------------------------------------------------------------------------
// Name: Trey Dobbs
// Course-Section: CS 255-01
// Assignment: Project #6
// Date Due: 11/20/2020
// Description: This C++ project adds support for in-game items to our 
// interactive fiction engine. Item support has been added to Area and
// Player, the map constructor has been updated, five new commands including 
// search, inventory, take, leave, and examine have been added, and the help
// and cheat commands have been updated.
// --------------------------------------------------------------------------
#include <iostream>

using namespace std;

class LinkData {
public:
	static const int SIZE = 4;

	void setDigits(int u, int d, int l, int r) {
		//u,l,d,r
		digits[0] = u;
		digits[1] = d;
		digits[2] = l;
		digits[3] = r;
	}
	int getDigit(int pos) {
		return digits[pos];
	}

private:
	int digits[4];
};
#pragma once
