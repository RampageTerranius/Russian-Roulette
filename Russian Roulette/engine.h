#ifndef ENGINE_H
#define ENGINE_H

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
	void Render();

	int ReturnState() { return returnState; }

private:
	// The state to return to the program upon exit.
	int returnState = 0;
	bool running = false;
	Gun gun;
	Player mainPlayer;
	Player aiPlayer;
};

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