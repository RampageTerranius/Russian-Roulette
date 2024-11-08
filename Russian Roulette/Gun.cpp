#include "Gun.h"

#include <random>
#include <iostream>
#include <algorithm>

// Fully loads the gun with random rounds.
void Gun::LoadGun(int liveShells, int blankShells)
{
	while (clip.size() > 0)
	{
		clip.pop_front();
	}

	for (int i = 0; i < liveShells; i++)
	{
		clip.push_front(true);
	}

	for (int i = 0; i < blankShells; i++)
	{
		clip.push_front(false);
	}

	// Create a random device for seeding.
	random_device rd;

	// Specify to make our device a Mersenne Twister random number engine.
	mt19937 gen(rd());

	shuffle(clip.begin(), clip.end(), gen);

	cout << "--||The dealer shows " << liveShells << " live and " << blankShells << " blank shells, they are inserted in an unknown order||--" << endl;;
}

// Fully loads the gun, randomly chooses how many live rounds.
void Gun::LoadGun()
{
	// Create a random device for seeding.
	random_device rd;

	// Specify to make our device a Mersenne Twister random number engine.
	mt19937 gen(rd());

	// Setup a uniform distribution for either 1 or 4 then randomly generate a number.
	std::uniform_int_distribution<> distribution(1, 4);
	int randomNumber = distribution(gen);

	LoadGun(randomNumber, 7 - randomNumber);
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
	clip.pop_front();

	return wasLiveRound;
}

// Return the probability that the next shell is live.
double Gun::LiveRoundProbability()
{
	int liveRounds = 0;
	for (int i = 0; i < clip.size(); i++)
	{
		if (clip[i] == true)
		{
			liveRounds++;
		}
	}

	return ((double)liveRounds / clip.size());
}

// Check if the gun is empty or not.
// Return true if empty, false if it still has rounds.
bool Gun::isEmpty()
{
	if (clip.size() == 0)
	{
		return true;
	}

	return false;
};

// Check if the next round is live.
// Return true if live, false if blank.
bool Gun::isNextRoundLive()
{
	return clip.front();
}
