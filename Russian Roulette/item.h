#ifndef ITEM_H
#define ITEM_H

#include "player.h"
#include "gun.h"

#include <xhash>

// Pure virtual base class for all items.
// Children must implement all functions.
class Item
{
public:
	// Use the item, return true if item was used, false if it was not.
	virtual bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun) = 0;
	virtual string ItemExplaination() = 0;
	virtual string ItemName() = 0;
};

// Item that doubles the damage for the next shot.
class DoubleDamage : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Saw off the barrel: Double the damage from the gun for current turn"; };
	string ItemName() { return "Hack Saw"; };
};

// Item that gives the user an extra life.
class GainLife : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Smoke cigarette: Gain one HP"; };
	string ItemName() { return "Smokes"; };
};

// Item that allows the user to check if the next shell is live.
class InspectShell : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Inspect gun: check if the current round in the gun is live or blank"; };
	string ItemName() { return "Magnifying Glass"; };
};

// Item that racks the gun, removing a shell from the gun.
class RackGun : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Rack the gun: Removes current round from gun"; };
	string ItemName() { return "Beer"; };
};

// Item that forces the opponenet to skip their turn.
class SkipOpponenetTurn : public Item
{
public:
	bool Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun);
	string ItemExplaination() { return "Hand cuff opponent: Your opponenet skips their next turn"; };
	string ItemName() { return "Hand cuffs."; };
};

#endif
