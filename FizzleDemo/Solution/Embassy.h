#pragma once
#include "Broviet.h"

class Embassy : public Character
{
public:
	void Idle();
	void Move(PlayerCharacter* Target);
	void Attack(PlayerCharacter* Target);
	void Hurt(PlayerCharacter* Taraget);
	void animation(int, PlayerCharacter* Target);
	Embassy(const char*, int, int, float, float, float, float, float, float, int);
	Embassy(FzlSpriteHandle, float, float, float, float, float, float, int);
private:
	int dodge;
	bool isDodging;
	bool isIdle;
	bool isMoving;
	bool isAttacking;
	bool isHit;
};