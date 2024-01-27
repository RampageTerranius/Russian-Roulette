#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <functional>

#include "gun.h"
#include "player.h"

class Engine
{
public:
	// Shutdown and startup functions.
	void Initialize();
	void Shutdown();

	// General engine functions.
	void GameLoop();
	void GetInput();
	void ProcessGameLogic();
	void Render();

	// Gun firing functions.
	void FireAtSelf();
	void FireAtOpponent();

	int ReturnState() { return returnState; }

private:
	// The state to return to the program upon exit.
	int returnState = 0;
	bool running = false;
	Gun gun;
	bool turn = false;
	Player players[2];
};

void Engine::Initialize()
{
	running = true;
	gun.LoadGun(2, 5);
}

void Engine::Shutdown()
{

}

void Engine::Render()
{
	cout << "Player 1 HP: " << players[0].Health() << " Player 2 HP: " << players[1].Health() << endl
		 << "What is your action?" << endl
		 << "1: Fire gun at opponent" << endl
		 << "2: Fire gun at self" << endl
		 << "3: Quit game" << endl;
}

void Engine::ProcessGameLogic()
{

}

// Fire gun at self.
void Engine::FireAtSelf()
{
	cout << "You aim the gun at yourself..." << endl
		 << "Click!" << endl;

	bool tookBullet = gun.Fire();

	if (tookBullet) 
	{
		cout << "BANG!... You have hit yourself" << endl;
		players[turn].TakeDamage();
	}
	else
	{
		cout << "Nothing..." << endl;
	}
}

// Fire gun at opponent
void Engine::FireAtOpponent()
{
	cout << "You aim the gun at your opponent..." << endl
		<< "Click!" << endl;

	bool tookBullet = gun.Fire();

	if (tookBullet)
	{
		cout << "BANG!... You have hit the opponent" << endl;
		players[!turn].TakeDamage();
	}
	else
	{
		cout << "Nothing..." << endl;
	}
}

void Engine::GetInput()
{
	string input;
	cin >> input;

	if (input == "1")
	{
		FireAtOpponent();
	}
	else if (input == "2")
	{
		FireAtSelf();
	}
	else  if (input == "3")
	{
		running = false;
	}
	else
	{
		cout << "Invalid input" << endl;
	}
}

// Primary game loop, does initialization and shutdown as well.
void Engine::GameLoop()
{
	Initialize();

	while (running)
	{
		Render();
		GetInput();		
	}

	Shutdown();
}

#endif