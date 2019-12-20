#include "Broviet.h"

//BROVIET UNION SOLDIER
Soldier::Soldier(const char* filePath, int frameWidthIn, int frameHeightIn, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(filePath, frameWidthIn, frameHeightIn, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

Soldier::Soldier(FzlSpriteHandle spriteHandle, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(spriteHandle, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

//Broviet Soldier States
void Soldier::Idle()
{
	isIdle = true;
}

void Soldier::Move(PlayerCharacter* Target)
{
	if (getPosition().getX() > Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 700.0f && (getPosition().distance(Target->getPosition())) > 99.0f)
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
	if (getPosition().getX() < Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 700.0f && (getPosition().distance(Target->getPosition())) > 99.0f)
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
	if (getPosition().getY() < Target->getPosition().getY() && (getPosition().distance(Target->getPosition())) < 300.0f && (getPosition().distance(Target->getPosition())) > 99.0f)
	{
		isIdle = false;
		isMoving = true;
		isAttacking = false;
		isHit = false;

		std::cout << "I SEE YOU\n";
		Position.setY((Position.getY() + 5));
		updateBoundingBox();
	}
	if (getPosition().getY() > Target->getPosition().getY() && (getPosition().distance(Target->getPosition())) < 300.0f && (getPosition().distance(Target->getPosition())) > 99.0f)
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

void Soldier::Attack(PlayerCharacter* Target)
{
	//Attack Left
	if (getPosition().getX() > Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 100.0f)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = true;
		isHit = false;

		Anim = 0;
		updateBoundingBox();
	}

	//Attack Right
	if (getPosition().getX() < Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 100.0f)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = true;
		isHit = false;

		Anim = 1;
		updateBoundingBox();
	}
}

void Soldier::Hurt(PlayerCharacter* Target)
{
	if (grunt == true)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = false;
		isHit = true;
	}
}

void Soldier::animation(int frameCounter, PlayerCharacter* Target)
{
	//Walking animation
	if ((isMoving == true) && (frameCounter % 4))
	{
		if (getFrame() < 5)
		{
			setFrame(5);
		}
		else if (getFrame() >= 10)
		{
			setFrame(5);
		}
		setFrame(getFrame() + 1);
	}
	else if ((isAttacking == true) && (frameCounter % 4))
	{
		if (getFrame() < 11)
		{
			setFrame(11);
		}
		else if (getFrame() > 17)
		{
			setFrame(11);
		}
		else if ((getFrame() == 17) && (frameCounter % 4))
		{
			std::cout << "OUCH\n";
			Target->decrementHealth();
		}
		setFrame(getFrame() + 1);
	}
	//Hit animation
	else if ((isHit == true))
	{
		if (getFrame() < 18)
		{
			setFrame(18);
		}
		else if (getFrame() > 20)
		{
			setFrame(18);
		}
		setFrame(getFrame() + 1);
	}
	//Idle animation
	else if ((frameCounter % 4) && (isIdle == true))
	{
		if (getFrame() >= 4)
		{
			setFrame(0);
		}
		setFrame(getFrame() + 1);
	}
}