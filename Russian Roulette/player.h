#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player();
	bool TakeDamage();
	int Health() { return health; }
private:
	int health;
};

Player::Player()
{
	health = 4;
}

// Take damage from a gun shot.
// Return true if player is still alive, false if dead.
bool Player::TakeDamage()
{
	health--;

	if (health > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif