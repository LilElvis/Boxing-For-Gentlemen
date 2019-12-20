#pragma once
#include <Fizzle\Fizzle.h>
#include "Vector.h"
#include <map>
#include <vector>

class Character
{
public:
	Character(const char*, int, int, float, float, float, float, float, float, int);
	Character(FzlSpriteHandle, float, float, float, float, float, float, int);
	void setPosition(float, float);
	Vector getPosition();
	void setBoundingBox(float, float, float, float);
	Vector getBoundingBoxTopCorner();
	Vector getBoundingBoxBottomCorner();
	void setAnim(int);
	int getAnim();
	void setFrame(int);
	int getFrame();
	bool getAlive();
	void setGrunt(bool);
	bool getGrunt();
	void draw();
	void kill();
	void setHealth(int);
	int getHealth();
	FzlSpriteHandle getSpriteHandle();
	void incrementHealth();
	void decrementHealth();
	void updateBoundingBox();
	void setDeathPosition(Vector);
	Vector getDeathPosition();
protected:
	FzlSpriteHandle SpriteHandle;
	Vector boundingBoxTopCorner;
	Vector boundingBoxBottomCorner;
	Vector Position;
	float topCornerXOffset;
	float topCornerYOffset;
	float bottomCornerXOffset;
	float bottomCornerYOffset;
	float Rotation;
	int Anim;  //Row
	int Frame; //Column
	bool alive;
	int Health;
	bool grunt;
	Vector deathPosition;
};