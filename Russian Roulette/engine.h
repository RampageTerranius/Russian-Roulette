#ifndef ENGINE_H
#define ENGINE_H

#include "Gun.h"
#include "Item.h"

#include <memory>
#include <vector>


class Engine
{
public:
	// Shutdown and startup functions.
	void Initialize();

	// General engine functions.
	void GameLoop();
	void ProcessGameLogic();
	

	int ReturnState() { return returnState; }

private:
	unique_ptr<Item> GetRandomItem();
	void giveItems();

	Gun gun;

	// The state to return to the program upon exit.
	int returnState = 0;
	bool running = false;
	
	bool turn = false;
	shared_ptr <Player> players[2];
	vector<unique_ptr<Item>> items[2];	
	
	const int minimumItemsPerRound = 2;
	const int maximumItemsPerRound = 4;
	const int maxItemsAllowed = 8;
	
};

#endif
