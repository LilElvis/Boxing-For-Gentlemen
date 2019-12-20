#pragma once
#include "Embassy.h"

class Pilot : public Character
{
public:
	void Idle();
	void Move(PlayerCharacter* Target);
	void Attack(PlayerCharacter* Target);
	void Hurt(PlayerCharacter* Target);
	void animation(int, PlayerCharacter* Target);
	Pilot(const char*, int, int, float, float, float, float, float, float, int);
	Pilot(FzlSpriteHandle, float, float, float, float, float, float, int);
private:
	int dodge;
	bool isDodging;
	bool isIdle;
	bool isMoving;
	bool isAttacking;
	bool isHit;
};