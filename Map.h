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
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>


#include "IFDParser.h"
#include "LinkData.h"
#include "Area.h"

using namespace std;

struct areaNode
{
	Area info;
	areaNode* u;
	areaNode* d;
	areaNode* l;
	areaNode* r;
};

class Map {
private:
	vector<areaNode*> areasVec;
	int areacnt;

	vector<Item> itemsVec;

	//Here is the instance of IFDParser
	IFDParser parser;

	//Some additional class attributes here
	vector<LinkData*> linkVec;
	string nextToken;

	bool ifderr;

public:
	Map() {
		ifderr = false;
		parser.tokenIt();

		nextToken = parser.getNext();

		if (nextToken == "<game>") {
			parser.eatToken();
			nextToken = parser.getNext();
			while (nextToken != "</game>") {   //consider what happens when run out of tokens && not error state
				if (nextToken == "<area>") {
					parser.eatToken();
					nextToken = parser.getNext();
					makeArea();
				}
				else if (nextToken == "<links>") {
					parser.eatToken();
					nextToken = parser.getNext();
					makeLinks();
				}

				else if (nextToken == "<item>") {
					parser.eatToken();
					nextToken = parser.getNext();
					makeItems();
				}

				else {
					cout << "Parse Error Location 1" << endl;
					ifderr = true;
					break;
				}
				parser.eatToken();
				nextToken = parser.getNext();
			}// while !</game>

			if (ifderr) {
				cout << " :: ERROR :: IF Document Formatting Error" << endl;
				cout << "Game Loading Failed" << endl;
				cout << "General Area of Parsing Failure:" << endl;
				cout << "-------------------------------------" << endl;
				cout << nextToken << endl;
				parser.eatToken();
				nextToken = parser.getNext();
				cout << nextToken << endl;
				parser.eatToken();
				nextToken = parser.getNext();
				cout << nextToken << endl;
				parser.eatToken();
				nextToken = parser.getNext();
				cout << nextToken << endl;
				cout << "-------------------------------------" << endl;
				return;
			}
		}
		else {
			cout << " :: ERROR :: No \"<game>\" tag found." << endl;
			cout << "Game Loading Failed" << endl;
		}

		//Linking items to their respective areas
		linkItems();

		//link up areas
		linkLinks();
	}//constructor

    // makeItems function to create items in-game
	void makeItems() {
		string xstr;
		Item newItem;

		while (nextToken != "</item>") {
			if (nextToken == "<name>") {
				parser.eatToken();
				nextToken = parser.getNext();
				newItem.setName(nextToken);
			}
			else if (nextToken == "<desc>") {
				parser.eatToken();
				nextToken = parser.getNext();
				newItem.setDesc(nextToken);
			}
			else if (nextToken == "<star>") {
				parser.eatToken();
				nextToken = parser.getNext();

				istringstream ss(nextToken);
				getline(ss, xstr, '<');
				newItem.setSR(atoi(xstr.c_str()));
			}
			else if (nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>") {
				//do nothing
			}
			else {
				cout << "Parse Error Location 2" << endl;
				ifderr = true;
				break;
			}

			parser.eatToken();
			nextToken = parser.getNext();
		}//while !</item>
		
		itemsVec.push_back(newItem); //Maintaing a list of items in Map separately
	}

	void makeArea() {
		int id;
		int goal;
		string xstr;

		areaNode* tempNodePtr = new areaNode;

		while (nextToken != "</area>") {
			if (nextToken == "<desc>") {
				parser.eatToken();
				nextToken = parser.getNext();

				tempNodePtr->info.setDescription(nextToken);
			}
			else if (nextToken == "<feats>") {
				parser.eatToken();
				nextToken = parser.getNext();

				istringstream ss(nextToken);
				getline(ss, xstr, ',');
				tempNodePtr->info.setID(atoi(xstr.c_str()));

				getline(ss, xstr, ',');
				tempNodePtr->info.setGoal(atoi(xstr.c_str()));
			}
			else if (nextToken == "</desc>" || nextToken == "</feats>") {
				//do nothing
			}
			else {
				cout << "Parse Error Location 2" << endl;
				ifderr = true;
				break;
			}

			parser.eatToken();
			nextToken = parser.getNext();
		}//while !</area>

		//add area to vector
		areasVec.push_back(tempNodePtr);

	} //end makeArea()

	void makeLinks() {
		string xstr;
		int u, d, l, r;
		while (nextToken != "</links>") {
			if (nextToken == "<linkset>") {
				parser.eatToken();
				nextToken = parser.getNext();

				LinkData* tempLDPtr = new LinkData;

				istringstream ss(nextToken);
				getline(ss, xstr, ',');
				u = atoi(xstr.c_str());
				getline(ss, xstr, ',');
				d = atoi(xstr.c_str());
				getline(ss, xstr, ',');
				l = atoi(xstr.c_str());
				getline(ss, xstr, ',');
				r = atoi(xstr.c_str());

				tempLDPtr->setDigits(u, d, l, r);
				linkVec.push_back(tempLDPtr);
			}
			else if (nextToken == "</linkset>") {
				//do nothing
			}
			else {
				cout << "Parse Error Location 3" << endl;
				ifderr = true;
				break;
			}
			parser.eatToken();
			nextToken = parser.getNext();
		}//while !</links>
	}//makeLinks()

	void printArea() {
	
		for (int i = 0; i < areasVec.size(); i++) {
			areasVec[i]->info.areaItems.printNames();
		}
	}

	//Deleteing the Items currently associated with an area
	void deleteLinks() {
		for (int i = 0; i < areasVec.size(); i++) {
			areasVec[i]->info.areaItems.destroyList();
		}
	}

	void linkItems() {
		for (int i = 0; i < itemsVec.size(); i++) {
			int star = (itemsVec[i].getSR())-1;
			areasVec[star]->info.areaItems.insertLast(&itemsVec[i]);
		}
	}

	void linkLinks() {
		for (int i = 0; i < linkVec.size(); i++) {
			areasVec[i]->u = areasVec[(linkVec[i]->getDigit(0)) - 1];
			areasVec[i]->d = areasVec[(linkVec[i]->getDigit(1)) - 1];
			areasVec[i]->l = areasVec[(linkVec[i]->getDigit(2)) - 1];
			areasVec[i]->r = areasVec[(linkVec[i]->getDigit(3)) - 1];
		}
	}

	areaNode* getStart() {
		return areasVec[0];  //returns a pointer to the first area listed
	}

	void print(){
		cout<<"******************************************************************"<<endl;
		cout<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
		cout<<"******************************************************************"<<endl;
		for(int i=0; i<areasVec.size(); i++){
			cout<<"This is area: "<<i+1<<endl;
			cout<<areasVec[i]->info.getDescription()<<endl;
			if(areasVec[i]->info.getID() == 1){
				cout<<"Area is INSTADEATH."<<endl;
			}
			if(areasVec[i]->info.getGoal() == 1){
				cout<<"Area is GOAL."<<endl;
			}
			cout<<"Connections:"<<endl;
			cout<<"\t u: Area #"<<reverseLookUp(areasVec[i]->u)<<endl;
			cout<<"\t d: Area #"<<reverseLookUp(areasVec[i]->d)<<endl;
			cout<<"\t l: Area #"<<reverseLookUp(areasVec[i]->l)<<endl;
			cout<<"\t r: Area #"<<reverseLookUp(areasVec[i]->r)<<endl;

			cout << "\n";
		}
		cout << "\n";

		cout << "******************************************************************" << endl;
		cout << "CHEATING!!!! ITEM LOCATIONS FOR ALL NON-INVENTORY ITEMS." << endl;
		cout << "******************************************************************" << endl;
		for (int i = 0; i < areasVec.size(); i++) {
			cout << "Items for Area #: " << i + 1;
			cout << " "<<areasVec[i]->info.getDescription() << endl;

			areasVec[i]->info.areaItems.printNames();
			cout << "\n";
		}

	}

	Item* getItem(string itemName) {
		for (int i = 0; i < itemsVec.size(); i++) {
			if (itemsVec[i].getName() == itemName) {
				return &itemsVec[i];
			}
		}
	}

	friend ostream& operator<<(ostream&, Map&);

	int reverseLookUp(areaNode* addy) {
		for (int i = 0; i < areasVec.size(); i++) {
			if (areasVec[i] == addy) {
				return i + 1;
			}
		}
		//this should not happen
		return -1;
	}

};

ostream& operator<<(ostream& osObject, Map& map)
{
	osObject << "******************************************************************" << endl;
	osObject << "CHEATING!!!! Printing the set of areas and connections on the map." << endl;
	osObject << "******************************************************************" << endl;
	for (int i = 0; i < map.areasVec.size(); i++) {
		cout << "This is area: " << i + 1 << endl;
		cout << map.areasVec[i]->info.getDescription() << endl;
		if (map.areasVec[i]->info.getID() == 1) {
			cout << "Area is INSTADEATH." << endl;
		}
		if (map.areasVec[i]->info.getGoal() == 1) {
			cout << "Area is GOAL." << endl;
		}
		cout << "Connections:" << endl;
		cout << "\t u: Area #" << map.reverseLookUp(map.areasVec[i]->u) << endl;
		cout << "\t d: Area #" << map.reverseLookUp(map.areasVec[i]->d) << endl;
		cout << "\t l: Area #" << map.reverseLookUp(map.areasVec[i]->l) << endl;
		cout << "\t r: Area #" << map.reverseLookUp(map.areasVec[i]->r) << endl;
	}

	return osObject;
}
#pragma once
