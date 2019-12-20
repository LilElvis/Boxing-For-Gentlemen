#pragma once
#include "Kicker.h"

class Soldier : public Character
{
public:
	void Idle();
	void Move(PlayerCharacter* Target);
	void Attack(PlayerCharacter* Target);
	void Hurt(PlayerCharacter* Target);
	void animation(int, PlayerCharacter* Target);
	Soldier(const char*, int, int, float, float, float, float, float, float, int);
	Soldier(FzlSpriteHandle, float, float, float, float, float, float, int);
private:
	bool isIdle;
	bool isMoving;
	bool isAttacking;
	bool isHit;
};