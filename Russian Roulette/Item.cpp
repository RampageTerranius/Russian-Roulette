#include "item.h"

#include <iostream>
#include <random>

bool RackGun::Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun)
{
	cout << "The gun is racked... ";

	gun->Fire()
		? cout << "A live shell is ejected..."
		: cout << "A blank shell is ejected...";

	cout << endl;

	return true;
}

bool GainLife::Use(Player* turnPlayer, Player* opponentPlayer, Gun* gun)
{
	turnPlayer->HealDamage(1);

	return true;
}


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