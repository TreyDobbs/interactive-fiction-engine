// --------------------------------------------------------------------------
// Name: Trey Dobbs
// Description: This C++ project adds support for in-game items to our 
// interactive fiction engine. Item support has been added to Area and
// Player, the map constructor has been updated, five new commands including 
// search, inventory, take, leave, and examine have been added, and the help
// and cheat commands have been updated.
// --------------------------------------------------------------------------

class Player {
public:

	uLList<Item*> inventoryItems;

	Player() {
		lastLocation = NULL;
		currentLocation = NULL;
	}

	void setCurrent(areaNode* loc) {
		lastLocation = currentLocation;
		currentLocation = loc;
	}

	bool playerMoved() {
		return !(lastLocation == currentLocation);
	}
	areaNode* getCurrent() {
		return currentLocation;
	}

	//isGameOver should return: 0 for continue, 1 for win, 2 for lose
	int isGameOver() {
		if (currentLocation->info.getID() == true) {
			return 2;
		}
		else if (currentLocation->info.getGoal() == true) {
			return 1;
		}
		else {
			return 0;
		}
	}

	//search command prints the names of all items in the inventory
	void inventory() {
		inventoryItems.printNames();
	}
	void take(Item newItem) {
		inventoryItems.insertLast(&newItem);
	}

	void examine(const string& searchItem) {
		inventoryItems.printDescription(searchItem);
	}

	
protected:
	areaNode* currentLocation;
	areaNode* lastLocation;

};
#pragma once
