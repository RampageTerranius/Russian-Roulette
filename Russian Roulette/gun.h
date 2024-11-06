#ifndef GUN_H
#define GUN_H

using namespace std;

#include <deque>

// A gun, is used by the dealer and the player as part of the game to either shoot themselves or the opposite user
class Gun
{
	public:		
		void LoadGun(int liveShells, int blankShells);
		void LoadGun();
		bool Fire();
		double LiveRoundProbability();
		bool isEmpty();
		bool isNextRoundLive();

		// If the next round should do double damage.
		bool nextRoundDoubleDamage = false;

	private:
		deque<bool> clip;
};

#endif
