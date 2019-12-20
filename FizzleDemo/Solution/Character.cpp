#include "Character.h"

Character::Character(const char* filePath, int frameWidthIn, int frameHeightIn, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Position(0.0f, 0.0f, "Position"), boundingBoxTopCorner(0.0f, 0.0f, "Top Corner"), boundingBoxBottomCorner(0.0f, 0.0f, "Bottom Corner"), deathPosition(0.0f, 0.0f, "Death Position")
{
	SpriteHandle = FzlLoadSprite(filePath, frameWidthIn, frameHeightIn);
	setPosition(characterPosXIn, characterPosYIn);
	setBoundingBox(topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn);
	topCornerXOffset = topCornerXIn;
	topCornerYOffset = topCornerYIn;
	bottomCornerXOffset = bottomCornerXIn;
	bottomCornerYOffset = bottomCornerYIn;
	setHealth(healthIn);
	Rotation = 0.0f;
	Anim = 0;
	Frame = 0;
	alive = true;
}

Character::Character(FzlSpriteHandle spriteHandle, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Position(0.0f, 0.0f, "Position"), boundingBoxTopCorner(0.0f, 0.0f, "Top Corner"), boundingBoxBottomCorner(0.0f, 0.0f, "Bottom Corner"), deathPosition(0.0f, 0.0f, "Death Position")
{
	SpriteHandle = spriteHandle;
	setPosition(characterPosXIn, characterPosYIn);
	setBoundingBox(topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn);
	topCornerXOffset = topCornerXIn;
	topCornerYOffset = topCornerYIn;
	bottomCornerXOffset = bottomCornerXIn;
	bottomCornerYOffset = bottomCornerYIn;
	setHealth(healthIn);
	Rotation = 0.0f;
	Anim = 0;
	Frame = 0;
	alive = true;
}

void Character::setPosition(float xIn, float yIn)
{
	Position.setX(xIn);
	Position.setY(yIn);
}

Vector Character::getPosition()
{
	return Position;
}

void Character::setBoundingBox(float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn)
{
	boundingBoxTopCorner.setX((Position.getX() + topCornerXIn));
	boundingBoxTopCorner.setY((Position.getY() + topCornerYIn));
	boundingBoxBottomCorner.setX((Position.getX() + bottomCornerXIn));
	boundingBoxBottomCorner.setY((Position.getY() + bottomCornerYIn));
}

void Character::updateBoundingBox()
{
	boundingBoxTopCorner.setX((Position.getX() + topCornerXOffset));
	boundingBoxTopCorner.setY((Position.getY() + topCornerYOffset));
	boundingBoxBottomCorner.setX((Position.getX() + bottomCornerXOffset));
	boundingBoxBottomCorner.setY((Position.getY() + bottomCornerYOffset));
}

Vector Character::getBoundingBoxTopCorner()
{
	return boundingBoxTopCorner;
}

Vector Character::getBoundingBoxBottomCorner()
{
	return boundingBoxBottomCorner;
}

void Character::setAnim(int animIn)
{
	Anim = animIn;
}

int Character::getAnim()
{
	return Anim;
}

void Character::setFrame(int frameIn)
{
	Frame = frameIn;
}

int Character::getFrame()
{
	return Frame;
}

void Character::draw()
{
	if (alive == true)
	FzlDrawAnimatedSprite(SpriteHandle, Anim, Frame, Position.getX(), Position.getY(), Rotation);
}

bool Character::getAlive()
{
	return alive;
}

void Character::setGrunt(bool gruntIn)
{
	grunt = gruntIn;
}

bool Character::getGrunt()
{
	return grunt;
}

void Character::kill()
{
	setDeathPosition(getPosition());
	setPosition(-5000.0f, -5000.0f);
	updateBoundingBox();
	alive = false;
}

void Character::setHealth(int healthIn)
{
	Health = healthIn;
}

int Character::getHealth()
{
	return Health;
}

FzlSpriteHandle Character::getSpriteHandle()
{
	return SpriteHandle;
}

void Character::incrementHealth()
{
	Health++;
}

void Character::decrementHealth()
{
	if (Health < 0)
	{
		kill();
	}
	else
	{	
		//losingHP = true;
		Health--;
	}
}

void Character::setDeathPosition(Vector deathPosIn)
{
	deathPosition = deathPosIn;
}

Vector Character::getDeathPosition()
{
	return deathPosition;
}