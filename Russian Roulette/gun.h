#ifndef GUN_H
#define GUN_H

using namespace std;

#include <queue>
#include <random>
#include <iostream>

// A gun, is used by the dealer and the player as part of the game to either shoot themselves or the opposite user
class Gun
{
	public:
		bool LoadRound(int total);
		bool Fire();

	private:
		queue<bool> clip;
		int clipMaxSize = 7;
};

// Loads rounds randomly into the gun.
// Return true if able to load a shell, false if unable(gun is full).
bool Gun::LoadRound(int total)
{
	if (clip.size() >= clipMaxSize)
	{
		cout << "The gun is already full";
		return false;
	}

	// Create a random device for seeding first.
	random_device rd;

	// Specify to make our device a Mersenne Twister random number engine.
	mt19937 gen(rd());

	// Setup a uniform distribution for either 0 or 1
	std::uniform_int_distribution<> distribution(0, 1);

	for (int i = 0; i < total; i++)
	{
		clip.push(distribution(gen));
	}	

	return true;
}

// Fire the weapon.
// Return true if the bullet fired was live, false if it was a blank.
bool Gun::Fire()
{
	if (clip.size() <= 0)
	{
		return false;
	}

	bool wasLiveRound = clip.front();
	clip.pop();

	return wasLiveRound;
}

#endif