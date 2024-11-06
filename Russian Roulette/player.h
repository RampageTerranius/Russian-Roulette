#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

#include "turnResult.h"
#include "gun.h"

// Base player class.
class Player
{
public:
	bool TakeDamage(int damage);
	void HealDamage(int damage);
	int Health() { return health; }
	virtual TurnResult TakeTurn(Gun *gun) = 0;
	bool skipNextTurn = false;

private:
	int health = 5;

};

// Class implementation specifically for a human.
class Player_Human : public Player
{
public:
	TurnResult TakeTurn(Gun* gun);
};

// Class implementation of palyer specifically for a AI.
class Player_AI : public Player
{
public:
	TurnResult TakeTurn(Gun* gun);

	bool isAwareOfNextShell = false;

private:
	// Probability data for determining if AI will fire or not.
	const double guaranteedFireOpponent = 0.75; // Fire if chance is >= this.
	const double guaranteedFireSelf = 0.25; // Fire at self if chance is <= this.

};

#endif
