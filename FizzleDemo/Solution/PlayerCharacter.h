#pragma once
#include "Character.h"

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(const char*, int, int, float, float, float, float, float, float, int);
	PlayerCharacter(FzlSpriteHandle, float, float, float, float, float, float, int);
	void Move(bool);
	bool Colliding(Character &);
	int getObjectsToCompare();
	void setLastPosition();
	Vector getLastPosition();
	void Hurt(Character* Target);
	void animation(int, bool);
	friend void sort(std::map<int, Character*> &a_map, std::vector<Character*> a_vector, PlayerCharacter* a_main_character);
private:
	Vector lastPosition;
	int objectsToCompare;
	bool isHit;
	bool collision;
	bool punching;
	bool moving;
	bool dodging;
	/*enum animationNum
	{
		Idle,
		Walking,
		Punching,
		Heavy,
		Super,
		Dodging,
		Flinch
	};*/
};