#pragma once
#include "Gulag.h"

class Kicker : public Character
{
public:
	void Move(PlayerCharacter* Target);
	void Attack(PlayerCharacter* Target);
	void Hurt(PlayerCharacter* Target);
	void animation(int, PlayerCharacter* Target);
	Kicker(const char*, int, int, float, float, float, float, float, float, int);
	Kicker(FzlSpriteHandle, float, float, float, float, float, float, int);
private:
	bool movingLeft;
	bool movingRight;
	bool isMoving;
	bool isAttacking;
	bool isHit;
};