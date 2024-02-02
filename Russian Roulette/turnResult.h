#ifndef TURNRESULT_H
#define TURNRESULT_H

enum class TurnResult {
	noDamageOpponent,
	noDamageSelf,
	damageOpponent,
	damageSelf,
	turnSkipped,
	closeGame
};

#endif