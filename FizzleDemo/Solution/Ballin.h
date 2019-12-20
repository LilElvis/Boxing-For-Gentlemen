#pragma once
#include "Pilot.h"

class Ballin : public Character
{
public:
	void Idle();
	void Move(PlayerCharacter* Target);
	void Attack(PlayerCharacter* Target);
	void Hurt(PlayerCharacter* Target);
	void animation(int, PlayerCharacter* Target);
	Ballin(const char*, int, int, float, float, float, float, float, float, int);
	Ballin(FzlSpriteHandle, float, float, float, float, float, float, int);
private:
	int dodge;
	bool isDodging;
	bool isIdle;
	bool isMoving;
	bool specialAttack;
	bool isAttacking;
	bool isHit;
};