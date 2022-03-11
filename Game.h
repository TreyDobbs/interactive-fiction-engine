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
#include "Map.h"
#include "Player.h"

class Game {
private:
	Player player1;
	Map map;

public:
	Game() {
		player1.setCurrent(map.getStart());
	}

	void play() {
		string userInput;
		//cin.ignore();
		while (true) {
			//check game status
			if (player1.isGameOver() != 0) {
				player1.getCurrent()->info.displayArea();
				return;
			}
			//display area data
			if (player1.playerMoved()) {
				player1.getCurrent()->info.displayArea();
			}
			else {
				cout << "There appears to be no way to go that direction." << endl;
			}

			//get movement selection
			cout << "Which way would you like to go?  Enter u, d, l, or r" << endl;
			getline(cin, userInput);

			//update area
			if (userInput == "u") {
				player1.setCurrent(player1.getCurrent()->u);
			}
			else if (userInput == "d") {
				player1.setCurrent(player1.getCurrent()->d);
			}
			else if (userInput == "l") {
				player1.setCurrent(player1.getCurrent()->l);
			}
			else if (userInput == "r") {
				player1.setCurrent(player1.getCurrent()->r);
			}
			else if (userInput == "iseedeadpeople") { //iseedeadpeople cheat code to reveal map
				map.print();
			}
			else if (userInput == "reset") {
				//Reset game should first destroy the existing inventory list and then reset the map, etc
				player1.inventoryItems.destroyList();

				player1.setCurrent(map.getStart());

				//Destroying the existing items linked to an area
				map.deleteLinks();

				//Resetting the items to their initial position
				map.linkItems();

				cout << "Game Reset. SUCCESSFULL!" << endl;
			}
			else if (userInput == "exit") {
				cout << "Good bye!" << endl;
				return;
			}
			else if (userInput == "search") {
				if (player1.getCurrent()->info.areaItems.getState() == false) {
					cout << "No items are in this room." << endl;
				}
				else {
					cout << "The following items are in this room:" << endl;
					player1.getCurrent()->info.areaItems.printNames();
				}
			}

			else if (userInput == "inventory") {

				if (player1.inventoryItems.getState()==false) {
					cout << "No items are in your inventory." << endl;
				}
				else {
					cout << "You have the following items:" << endl;
					player1.inventoryItems.printNames();
				}
			}

			else if (userInput == "take") {
				
				Item* itemToTake;

				string itemName;
				cout << "Take what item?" << endl;
				getline(cin, itemName);

				//I am assuming that the player will enter the correct item name
				itemToTake = map.getItem(itemName);
				
				player1.getCurrent()->info.areaItems.deleteNode(itemToTake);

				player1.inventoryItems.insertLast(itemToTake);
				cout << "You have taken: " << itemName << endl;
			}

			else if (userInput == "leave") {


				Item* itemToLeave;

				string itemName;
				cout << "Leave what item?" << endl;
				getline(cin, itemName);

				//I am assuming that the player will enter the correct item name
				itemToLeave = map.getItem(itemName);

				player1.getCurrent()->info.areaItems.insertLast(itemToLeave);

				player1.inventoryItems.deleteNode(itemToLeave);
				cout << "You have dropped: " << itemName << endl;
			}

			else if (userInput == "examine") {
				//get the name of item to examine
				string itemName;
				cout << "Examine what item?" << endl;
				getline(cin, itemName);
				player1.examine(itemName);
				cout << endl;
			}

			else if (userInput == "help") {
				cout << "You may type: " << endl;
				cout << "\t u, d, l, or r: to move up, down, left or right on the map," << endl;
				cout << "\t inventory: prints out the name of all the items currently in the player’s inventory." << endl;
				cout << "\t search: to print out the name of all the items in a specific area." << endl;
                cout << "\t take: to take an item from the current area and add an item to your inventory." << endl;
				cout << "\t leave: to remove an item from your inventory." << endl;
				cout << "\t examine: to print out the description of a particular inventory." << endl;
                cout << "\t reset: to reset the game." << endl;
				cout << "\t exit: to exit the game." << endl;
				cout << endl;
			}

			else {
				cout << "I do not understand: " << userInput << endl << endl;
			}
		}//end while		
	}//end play()

};
#pragma once
