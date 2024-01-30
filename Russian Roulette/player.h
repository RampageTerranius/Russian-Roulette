#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

#include <iostream>

#include "turnResult.h"
#include "gun.h"



class Player
{
public:
	Player();
	bool TakeDamage(int damage);
	int Health() { return health; }
	virtual TurnResult TakeTurn(Gun *gun);
private:
	int health;
};

Player::Player()
{
	health = 4;
}

// Invalid use of TakeTurn, base class shoudl never be used
TurnResult Player::TakeTurn(Gun *gun)
{
	cout << "Invalid use of TakeTurn(Gun gun), please use a child class instead of Player" << endl;
	return TurnResult::noDamageOpponent;
}

// Take damage from a gun shot.
// Return true if player is still alive, false if dead.
bool Player::TakeDamage(int damage)
{
	health -= damage;

	if (health > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

class Player_Human : public Player
{
public:
	TurnResult TakeTurn(Gun *gun);
};

TurnResult Player_Human::TakeTurn(Gun *gun)
{
	string input;	

	while (true)
	{

		cin >> input;

		if (input == "1")
		{
			if (gun->Fire())
			{
				return TurnResult::damageOpponent;
			}
			else
			{
				return TurnResult::noDamageOpponent;
			}
		}
		else if (input == "2")
		{
			if (gun->Fire())
			{
				return TurnResult::damageSelf;
			}
			else
			{
				return TurnResult::noDamageSelf;
			}
		}
		else if (input == "3")
		{
			return TurnResult::closeGame;
		}
		else
		{
			cout << "Invalid input" << endl;
		}
	}
}

class Player_AI : public Player
{
public:
	TurnResult TakeTurn(Gun *gun);
};

TurnResult Player_AI::TakeTurn(Gun *gun)
{
	cout << "The dealer skips his turn (due to having no AI yet...)" << endl;
	return TurnResult::noDamageOpponent;
}

#endif