# interactive-fiction-engine

Adding support for in-game items to the interactive fiction engine.

From the player perspective, items can be interacted with in-game. Every player has an inventory of items which is initially empty. 
The player can take an item (remove it from the area and add it to the player inventory), leave an item (take it from the player 
inventory and place it in the current area), and examine an item (this will print the item's description). Additionally, the player can
search an area (list all the items in the current area), and list the item's in his/her own inventory. In terms of the game engine, 
items are stored as objects; instances of the new Item class. Each Area instance will now have a data structure (an unordered linked-list) 
dedicated to storing the Item instances currently in that area. Likewise, the Player instance will have a similar data structure
where Item instances in the player's inventory are kept. The Game and Map classes will need to be updated to respond to a new set of item 
related user commands and experiences and to manage items as the player progresses.
