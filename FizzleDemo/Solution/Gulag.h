#pragma once
#include "PlayerCharacter.h"

class Gulag : public Character
{
public:
	void Idle();
	void Move(PlayerCharacter* Target);
	void Attack(PlayerCharacter* Target);
	void Hurt(PlayerCharacter* Target);
	void animation(int, PlayerCharacter* Target);
	Gulag(const char*, int, int, float, float, float, float, float, float, int);
	Gulag(FzlSpriteHandle, float, float, float, float, float, float, int);
private:
	bool isIdle;
	bool isMoving;
	bool isAttacking;
	bool isHit;
};