#pragma once
#include "PlayerCharacter.h"

class Crate : public Character
{
public:
	void Idle();
	void Break(PlayerCharacter* Target);
	void animations();
	Crate(const char*, int, int, float, float, float, float, float, float, int);
	void Update();
	void ChangeState(bool);
};