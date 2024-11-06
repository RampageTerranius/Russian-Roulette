#include "Player.h"

#include <iostream>
#include <random>

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

// Heal damage.
// Return true if player is still alive, false if dead.
void Player::HealDamage(int damage)
{
	health += damage;
}

TurnResult Player_Human::TakeTurn(Gun* gun)
{
	if (skipNextTurn)
	{
		return TurnResult::turnSkipped;
	}

	string input;

	while (true)
	{

		cin >> input;

		// Shoot at opponent.
		if (input == "1")
		{
			cout << "You aim the gun at the dealer..." << endl;
			if (gun->Fire())
			{
				return TurnResult::damageOpponent;
			}
			else
			{
				return TurnResult::noDamageOpponent;
			}
		}

		// Shoot at self.
		else if (input == "2")
		{
			cout << "You aim the gun at yourself..." << endl;
			if (gun->Fire())
			{
				return TurnResult::damageSelf;
			}
			else
			{
				return TurnResult::noDamageSelf;
			}
		}
		// Close game.
		else if (input == "0")
		{
			cout << "Closing game..." << endl;
			return TurnResult::closeGame;
		}
		else
		{
			cout << "Invalid input" << endl;
		}
	}
}

TurnResult Player_AI::TakeTurn(Gun* gun)
{
	if (skipNextTurn)
	{
		return TurnResult::turnSkipped;
	}

	// Calculate the probability that the AI will fire.
	// First lets get the chance the next bulelt will be live;
	double chanceOfLive = gun->LiveRoundProbability();

	cout << "AI probabilty of self hit: " << chanceOfLive << endl;

	// If the AI is aware there is no bullets then shoot at self.
	if (chanceOfLive == 0)
	{
		cout << "The dealer points the gun at himself..." << endl;
		gun->Fire();
		return TurnResult::noDamageSelf;
	}

	// Otherwise if the AI is aware there is ONLY bullets left then shoot at player.
	else if (chanceOfLive == 1)
	{
		cout << "The dealer points the gun at you..." << endl;
		gun->Fire();
		return TurnResult::damageOpponent;
	}

	// If we are at a high chance to hit then just fire.
	else if (chanceOfLive >= guaranteedFireOpponent)
	{
		cout << "The dealer points the gun at you..." << endl;
		return gun->Fire() ? TurnResult::damageOpponent : TurnResult::noDamageOpponent;

	}

	// if we are at a low chance to hit then fire at self.
	else if (chanceOfLive <= guaranteedFireSelf)
	{
		cout << "The dealer points the gun at himself..." << endl;
		bool wasLive = gun->Fire();

		return gun->Fire() ? TurnResult::damageSelf : TurnResult::noDamageSelf;
	}

	// Otherwise, flip a coin and determine who we shoot.
	else
	{
		// Create a random device for seeding.
		random_device rd;

		// Specify to make our device a Mersenne Twister random number engine.
		mt19937 gen(rd());

		// Setup a uniform distribution for either 0 or 1 then randomly generate a number.
		std::uniform_int_distribution<> distribution(0, 1);
		int randomNumber = distribution(gen);

		bool wasLive = gun->Fire();

		switch (randomNumber)
		{
		case 0:
			cout << "The dealer points the gun at you..." << endl;
			if (wasLive)
			{
				return TurnResult::damageOpponent;
			}
			else
			{
				return TurnResult::noDamageOpponent;
			}
			break;
		case 1:
			cout << "The dealer points the gun at himself..." << endl;
			if (wasLive)
			{
				return TurnResult::damageSelf;
			}
			else
			{
				return TurnResult::noDamageSelf;
			}
			break;
		}
	}


	cout << "something went wrong with the dealer AI... ending turn..." << endl;
	return TurnResult::noDamageOpponent;
}
