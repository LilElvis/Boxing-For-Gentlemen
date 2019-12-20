#include "Pilot.h"

//PILOT
Pilot::Pilot(const char* filePath, int frameWidthIn, int frameHeightIn, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(filePath, frameWidthIn, frameHeightIn, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

Pilot::Pilot(FzlSpriteHandle spriteHandle, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(spriteHandle, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

//Pilot States
void Pilot::Idle()
{
	isIdle = true;
}

void Pilot::Move(PlayerCharacter* Target)
{
	if (getPosition().getX() > Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 700.0f && (getPosition().distance(Target->getPosition())) > 99.0f)
	{
		isIdle = false;
		isMoving = true;
		isAttacking = false;
		isHit = false;
		isDodging = false;

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
		isDodging = false;

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
		isDodging = false;

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
		isDodging = false;

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
		isDodging = false;
	}
}

void Pilot::Attack(PlayerCharacter* Target)
{
	//Attack Left
	if (getPosition().getX() > Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 100.0f)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = true;
		isHit = false;
		isDodging = false;

		dodge = rand() % 30 + 1;
		if (dodge == 3)
		{
			//Dodge Right (when facing left)
			isDodging = true;
			isAttacking = false;
			Position.setX((Position.getX() + 60));
		}
		else
		{
			isDodging = false;
		}

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
		isDodging = false;

		dodge = rand() % 30 + 1;
		if (dodge == 3)
		{
			//Dodge Right (when facing left)
			isDodging = true;
			Position.setX((Position.getX() - 60));
		}
		else
		{
			isDodging = false;
		}

		Anim = 1;
		updateBoundingBox();
	}
}


void Pilot::Hurt(PlayerCharacter* Target)
{
	if (grunt == true)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = false;
		isHit = true;
		isDodging = false;
	}
}

void Pilot::animation(int frameCounter, PlayerCharacter* Target)
{
	//Walking animation
	if ((isMoving == true) && (frameCounter % 4))
	{
		if (getFrame() < 18)
		{
			setFrame(18);
		}
		else if (getFrame() >= 25)
		{
			setFrame(18);
		}
		setFrame(getFrame() + 1);
	}
	else if ((isAttacking == true) && (frameCounter % 4))
	{
		if (getFrame() < 5)
		{
			setFrame(5);
		}
		else if (getFrame() >= 13)
		{
			setFrame(5);
		}
		else if ((getFrame() == 8) && (frameCounter % 4))
		{
			Target->decrementHealth();
		}
		else if ((getFrame() == 12) && (frameCounter % 4))
		{
			Target->decrementHealth();
			Target->decrementHealth();
		}
		setFrame(getFrame() + 1);
	}
	//Dodge animation (random)
	else if ((isDodging == true))
	{
		if (getFrame() < 14)
		{
			setFrame(14);
		}
		else if (getFrame() > 15)
		{
			setFrame(14);
		}
		setFrame(getFrame() + 1);
	}
	//Hit animation
	else if ((isHit == true))
	{
		if (getFrame() < 15)
		{
			setFrame(15);
		}
		else if (getFrame() > 16)
		{
			setFrame(15);
		}
		setFrame(getFrame() + 1);
	}
	//Idle animation
	else if ((isIdle == true) && (frameCounter % 4))
	{
		if (getFrame() >= 5)
		{
			setFrame(0);
		}
		setFrame(getFrame() + 1);
	}
}