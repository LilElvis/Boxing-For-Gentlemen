#include "Ballin.h"

//BROSEFF BALLIN'
Ballin::Ballin(const char* filePath, int frameWidthIn, int frameHeightIn, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(filePath, frameWidthIn, frameHeightIn, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

Ballin::Ballin(FzlSpriteHandle spriteHandle, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(spriteHandle, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

//Broseff Ballin' States
void Ballin::Idle()
{
	isIdle = true;
}

void Ballin::Move(PlayerCharacter* Target)
{
	if (getPosition().getX() > Target->getPosition().getX() && 
		(getPosition().distance(Target->getPosition())) < 800.0f && 
		(getPosition().distance(Target->getPosition())) > 299.0f)
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
		(getPosition().distance(Target->getPosition())) < 800.0f &&
		(getPosition().distance(Target->getPosition())) > 299.0f)
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
	if ((getPosition().getY() < Target->getPosition().getY() && 
		(getPosition().distance(Target->getPosition())) < 600.0f))
	{
		isIdle = false;
		isMoving = true;
		isAttacking = false;
		specialAttack = false;
		isHit = false;

		std::cout << "I SEE YOU\n";
		Position.setY((Position.getY() + 5));
		updateBoundingBox();
	}
	else if (getPosition().getX() == Target->getPosition().getX() &&
		(getPosition().getY() < Target->getPosition().getY() &&
		(getPosition().distance(Target->getPosition())) > 80.0f))
	{
		specialAttack = false;
		isMoving = true;
		Position.setY((Position.getY() + 5));
		updateBoundingBox();
	}

	if ((getPosition().getY() > Target->getPosition().getY() &&
		(getPosition().distance(Target->getPosition())) < 600.0f))
	{
		isIdle = false;
		isMoving = true;
		isAttacking = false;
		specialAttack = false;
		isHit = false;

		std::cout << "I SEE YOU\n";
		Position.setY((Position.getY() - 5));
		updateBoundingBox();
	}
	else if (getPosition().getX() == Target->getPosition().getX() && 
		(getPosition().getY() > Target->getPosition().getY() && 
		(getPosition().distance(Target->getPosition())) > 80.0f))
	{
		specialAttack = false;
		isMoving = true;
		Position.setY((Position.getY() - 5));
		updateBoundingBox();
	}

	//Left Dive
	if (getPosition().getX() > Target->getPosition().getX() &&
		(getPosition().getY() == Target->getPosition().getY()) &&
		(getPosition().distance(Target->getPosition())) < 200.0f &&
		(getPosition().distance(Target->getPosition())) > 79.0f)
	{
		specialAttack = true;
		isIdle = false;
		isMoving = false;
		isAttacking = false;
		isHit = false;

		Position.setX((Position.getX() - 10));
		updateBoundingBox();
		Anim = 0;
	}

	//Right Dive
	if (getPosition().getX() < Target->getPosition().getX() &&
		(getPosition().getY() == Target->getPosition().getY()) &&
		(getPosition().distance(Target->getPosition())) < 200.0f &&
		(getPosition().distance(Target->getPosition())) > 79.0f)
	{
		specialAttack = true;
		isIdle = false;
		isMoving = false;
		isAttacking = false;
		isHit = false;

		Position.setX((Position.getX() + 10));
		updateBoundingBox();
		Anim = 1;
	}

	if (getPosition().distance(Target->getPosition()) > 800.0f)
	{
		isIdle = true;
		isMoving = false;
		isAttacking = false;
		isHit = false;
	}
}

void Ballin::Attack(PlayerCharacter* Target)
{
	//Attack Left
	if (getPosition().getX() > Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 80.0f)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = true;
		isHit = false;
		specialAttack = false;

		dodge = rand() % 20 + 1;
		if (dodge == 3)
		{
			//Dodge Right (when facing left)
			isDodging = true;
			isAttacking = false;
			Position.setX((Position.getX() + 80));
		}
		else
		{
			isDodging = false;
		}

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
		specialAttack = false;

		dodge = rand() % 30 + 1;
		if (dodge == 3)
		{
			//Dodge Right (when facing left)
			isDodging = true;
			Position.setX((Position.getX() - 80));
		}
		else
		{
			isDodging = false;
		}

		Anim = 1;
		updateBoundingBox();
	}
}

void Ballin::Hurt(PlayerCharacter* Target)
{
	if (grunt == true)
	{
		isIdle = false;
		isMoving = false;
		isAttacking = false;
		specialAttack = false;
		isHit = true;
		isDodging = false;
	}
}

void Ballin::animation(int frameCounter, PlayerCharacter* Target)
{
	//Walking animation
	if ((isMoving == true) && (frameCounter % 4))
	{
		if (getFrame() < 26)
		{
			setFrame(26);
		}
		else if (getFrame() >= 29)
		{
			setFrame(26);
		}
		setFrame(getFrame() + 1);
	}
	else if ((specialAttack == true) && (frameCounter % 4))
	{
		//Diving special attack
		//if (getFrame() < 17)
		//{
		//	setFrame(17);
		//}
		if (getFrame() > 22)
		{
			setFrame(17);
		}
		else if (((getFrame() == 21) || (getFrame() == 20) && (frameCounter % 4) && 
			(getPosition().distance(Target->getPosition())) < 125.0f))
		{
			std::cout << "OUCH\n";
			Target->decrementHealth();
			//Target->decrementHealth();
		}
		setFrame(getFrame() + 1);
		//isMoving = true;
	}
	else if ((isAttacking == true) && (frameCounter % 4))
	{
		//Light Attack + Heavy Attack combo
		if (getFrame() < 5)
		{
			setFrame(5);
		}
		else if (getFrame() > 13)
		{
			setFrame(5);
		}
		//Combo Attacks Detected Here
		else if ((getFrame() == 7) && (frameCounter % 4))
		{
			std::cout << "OUCH\n";
			Target->decrementHealth();
		}
		else if ((getFrame() == 13) && (frameCounter % 4))
		{
			std::cout << "OUCH\n";
			Target->decrementHealth();
			Target->decrementHealth();
		}
		setFrame(getFrame() + 1);
	}
	//Hit animation
	else if ((isHit == true))
	{
		if (getFrame() < 23)
		{
			setFrame(23);
		}
		else if (getFrame() > 25)
		{
			setFrame(23);
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