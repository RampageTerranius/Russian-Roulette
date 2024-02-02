#ifndef ITEM_H
#define ITEM_H

using namespace std;

#include <iostream>

#include "player.h"
#include "gun.h"

// Pure virtual base class for all items.
// Children must implement all functions.
class Item
{
public:
	// Use the item, return true if item was used, false if it was not.
	virtual bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun) = 0;
	virtual string ItemExplaination() = 0;
	virtual string ItemName() = 0;
private:
};

// Item that racks the gun, removing a shell from the gun.
class RackGun : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Rack the gun: Removes current round from gun"; };
	string ItemName() { return "Beer"; };
};

bool RackGun::Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun)
{
	cout << "The gun is racked... ";

	gun->Fire() 
		? cout << "A live shell is ejected..."
		: cout << "A blank shell is ejected...";

	cout << endl;

	return true;
}

// Item that gives the user an extra life.
class GainLife : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Smoke cigarette: Gain one HP"; };
	string ItemName() { return "Smokes"; };
};

bool GainLife::Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun)
{
	turnPlayer->HealDamage(1);

	return true;
}

// Item that doubles the damage for the next shot.
class DoubleDamage : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Saw off the barrel: Double the damage from the gun for current turn"; };
	string ItemName() { return "Hack Saw"; };
};

bool DoubleDamage::Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun)
{
	// Check if a hack saw has already been used.
	if (gun->nextRoundDoubleDamage)
	{
		cout << "The barrel of the gun has already been sawed off..." << endl;
		return false;
	}
	else
	{
		gun->nextRoundDoubleDamage = true;
		cout << "The barrel of the gun is sawed off..." << endl;
		return true;
	}
}

// Item that allows the user to check if the next shell is live.
class InspectShell : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Inspect gun: check if the current round in the gun is live or blank"; };
	string ItemName() { return "Magnifying Glass"; };
};

bool InspectShell::Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun)
{
	cout << "The current shell in the gun is checked..." << endl;

	Player_AI* aiPlayer = dynamic_cast<Player_AI*>(turnPlayer);

	// Check if the player usign the item is an ai.
	if (aiPlayer != nullptr)
	{
		aiPlayer->isAwareOfNextShell = true;
		cout << "Hmmm... very interesting....." << endl;
	}
	else
	{
		gun->isNextRoundLive()
			? cout << "The next round is live."
			: cout << "The next roudn is a blank.";

		cout << endl;
	}

	return true;
}

// Item that forces the opponenet to skip their turn.
class SkipOpponenetTurn : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Hand cuff opponent: Your opponenet skips their next turn"; };
	string ItemName() { return "Hand cuffs."; };
};

bool SkipOpponenetTurn::Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun)
{
	if (opponentPlayer->skipNextTurn)
	{
		cout << "Opponenet is already cuffed" << endl;
		return false;
	}
	else
	{
		cout << "Cuffs are applied to the opponent" << endl;
		opponentPlayer->skipNextTurn = true;
		return true;
	}
}

// Randomly chooses an item and returns it.
// Items are as follows:
// 0 = RackGun
// 1 = GainLife
// 2 = DoubleDamage
// 3 = InspectShell
// 4 = SkipOpponenetTurn

unique_ptr<Item> GetRandomItem()
{
	// Create a random device for seeding.
	random_device rd;

	// Specify to make our device a Mersenne Twister random number engine.
	mt19937 gen(rd());

	// Setup a uniform distribution between 0 and the maximum type of items(-1) then randomly generate a number.
	std::uniform_int_distribution<> distribution(0, 4);
	int itemToDistribute = distribution(gen);

	switch (itemToDistribute)
	{
		case 0:
			return make_unique<RackGun>();
			break;

		case 1:
			return make_unique<GainLife>();
			break;

		case 2:
			return make_unique<DoubleDamage>();
			break;

		case 3:
			return make_unique<InspectShell>();
			break;

		case 4:
			return make_unique<SkipOpponenetTurn>();
			break;
	}
}

#endif