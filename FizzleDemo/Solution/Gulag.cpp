#include "Gulag.h"

//GULAG GUARD
Gulag::Gulag(const char* filePath, int frameWidthIn, int frameHeightIn, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(filePath, frameWidthIn, frameHeightIn, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

Gulag::Gulag(FzlSpriteHandle spriteHandle, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(spriteHandle, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

//Gulag States
void Gulag::Idle()
{
	isIdle = true;
}

void Gulag::Move(PlayerCharacter* Target)
{
	if (getPosition().getX() > Target->getPosition().getX() &&
		(getPosition().distance(Target->getPosition())) < 700.0f &&
		(getPosition().distance(Target->getPosition())) > 79.0f)
	{
		isIdle = false;
		isMoving = true;
		isAttacking = false;
		isHit = false;

		std::cout << "I SEE YOU\n";
		Position.setX((Position.getX() - 5));
		updateBoundingBox();
		Anim = 0;
	}
	if (getPosition().getX() < Target->getPosition().getX() &&
		(getPosition().distance(Target->getPosition())) < 700.0f &&
	(getPosition().distance(Target->getPosition())) > 79.0f)
	{
		isIdle = false;
		isMoving = true;
		isAttacking = false;
		isHit = false;

		std::cout << "I SEE YOU\n";
		Position.setX((Position.getX() + 5));
		updateBoundingBox();
		Anim = 1;
	}
	if (getPosition().getY() < Target->getPosition().getY() &&
		(getPosition().distance(Target->getPosition())) < 300.0f &&
		(getPosition().distance(Target->getPosition())) > 79.0f)
	{
		isIdle = false;
		isMoving = true;
		isAttacking = false;
		isHit = false;

		std::cout << "I SEE YOU\n";
		Position.setY((Position.getY() + 5));
		updateBoundingBox();
	}
	if (getPosition().getY() > Target->getPosition().getY() &&
		(getPosition().distance(Target->getPosition())) < 300.0f &&
		(getPosition().distance(Target->getPosition())) > 79.0f)
	{
		isIdle = false;
		isMoving = true;
		isAttacking = false;
		isHit = false;
		std::cout << "I SEE YOU\n";
		Position.setY((Position.getY() - 5));
		updateBoundingBox();
	}
	if (getPosition().distance(Target->getPosition()) > 700.0f)
	{
		isIdle = true;
		isMoving = false;
		isAttacking = false;
		isHit = false;
	}
}

void Gulag::Attack(PlayerCharacter* Target)
{
	//Attack Left
	if (getPosition().getX() > Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 80.0f)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = true;
		isHit = false;

		Anim = 0;
		updateBoundingBox();
	}

	//Attack Right
	if (getPosition().getX() < Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 80.0f)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = true;
		isHit = false;

		Anim = 1;
		updateBoundingBox();
	}
}

void Gulag::Hurt(PlayerCharacter* Target)
{
	if (grunt == true)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = false;
		isHit = true;
	}
}

void Gulag::animation(int frameCounter, PlayerCharacter* Target)
{
	//Walk animation
	if ((isMoving == true) && (frameCounter % 4))
	{
		if (getFrame() < 7)
		{
			setFrame(7);
		}
		else if (getFrame() == 10)
		{
			setFrame(7);
		}
		setFrame(getFrame() + 1);
	}
	//Attack animation
	else if ((isAttacking == true) && (frameCounter % 4))
	{
		if (getFrame() < 4)
		{
			setFrame(4);
		}
		else if (getFrame() > 8)
		{
			setFrame(4);
		}
		else if ((getFrame() == 7) && (frameCounter % 4))
		{
			std::cout << "OUCH\n";
			Target->decrementHealth();
			Target->setGrunt(true);
			Target->setFrame(40);
			if (Target->getFrame() < 40)
			{
				Target->setFrame(40);
			}
			else if (Target->getFrame() > 41)
			{
				Target->setFrame(40);
			}
			Target->setFrame(getFrame() + 1);
		}
		else if (Target->getGrunt() == true)
		{
			Target->setGrunt(false);
		}
		setFrame(getFrame() + 1);
	}
	//Hit animation
	else if ((isHit == true) && (frameCounter % 30))
	{
		if (getFrame() < 10)
		{
			setFrame(10);
		}
		else if (getFrame() > 13)
		{
			setFrame(10);
		}
		setFrame(getFrame() + 1);
	}
	//Idle animation
	else if ((isIdle == true) && (frameCounter % 4))
	{
		if (getFrame() >= 4)
		{
			setFrame(0);
		}
		setFrame(getFrame() + 1);
	}
}