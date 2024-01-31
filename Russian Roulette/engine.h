#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <functional>

#include "gun.h"
#include "player.h"
#include "turnResult.h"

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
	// The state to return to the program upon exit.
	int returnState = 0;
	bool running = false;
	Gun gun;
	bool turn = false;
	shared_ptr <Player> players[2];
};

void Engine::Initialize()
{
	running = true;
	gun.LoadGun();

	players[0] = make_shared<Player_Human>();
	players[1] = make_shared<Player_AI>();
}

void Engine::ProcessGameLogic()
{
	cout << endl;

	if (!turn)
	{
		cout << "Player 1 HP: " << players[0]->Health() << " Player 2 HP: " << players[1]->Health() << endl
			 << "What is your action?" << endl
			 << "1: Fire gun at opponent" << endl
			 << "2: Fire gun at self" << endl
			 << "3: Quit game" << endl;
	}


	TurnResult turnResult = players[turn]->TakeTurn(&gun);
	
	// Process the result of the players turn.
	switch (turnResult)
	{
		case TurnResult::noDamageSelf:
			cout << "Nothing... the player gets another turn" << endl;
			break;

		case TurnResult::noDamageOpponent:
			cout << "Nothing... the gun is handed to the other player..." << endl;
			turn = !turn;
			break;

		case TurnResult::damageOpponent:
			if (!turn)
			{
				cout << "BANG!... You hit the dealer!" << endl;
			}
			else
			{
				cout << "BANG!... the dealer hits you!" << endl;
			}

			players[!turn]->TakeDamage(1);

			turn = !turn;
			break;

		case TurnResult::damageSelf:
			if (!turn)
			{
				cout << "BANG!... You have hit yourself" << endl;
			}
			else
			{
				cout << "BANG!... the dealer hits himself" << endl;
			}

			players[turn]->TakeDamage(1);
			turn = !turn;
			break;

		case TurnResult::closeGame:
			running = false;
			break;
	}

	// Check if gun needs to be reloaded.
	if (gun.isEmpty())
	{
		gun.LoadGun();
	}
}

// Primary game loop, does initialization and shutdown as well.
void Engine::GameLoop()
{
	Initialize();

	while (running)
	{
		ProcessGameLogic();
	}
}

#endif