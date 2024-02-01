#ifndef ITEM_H
#define ITEM_H

#include "player.h"
#include "gun.h"

// Pure virtual base class for all items.
// Children must implement all functions.
class item
{
public:
	virtual void use(Player *turnPlayer, Player *opponentPlayer, Gun *gun) const = 0;
	virtual string itemExplaination() const = 0;
	virtual string itemName() const = 0;
private:
};

// Item that racks the gun, removign a shell from the gun.
class rackGun : public item
{
};

// Item that gives the user an extra life.
class gainLife : public item
{

};

// Item that doubles the damage for the next shot.
class doubleDamage : public item
{

};

// Item that allows the user to check if the next shell is live.
class inspectShell : public item
{
};

#endif