#include "Kicker.h"

//KAZOTSKY KICKER
Kicker::Kicker(const char* filePath, int frameWidthIn, int frameHeightIn, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(filePath, frameWidthIn, frameHeightIn, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

Kicker::Kicker(FzlSpriteHandle spriteHandle, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(spriteHandle, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

//Kazotsky Kicker States

void Kicker::Move(PlayerCharacter* Target)
{
	if (getPosition().getX() > Target->getPosition().getX() && getPosition().distance(Target->getPosition()) > 299.0f)
	{
		isMoving = true;
		movingLeft = true;
		movingRight = false;
		isAttacking = false;
		isHit = false;

		std::cout << "I SEE YOU\n";
		
		//Position.setX((Position.getX() - 5));
		if (getPosition().getY() == Target->getPosition().getY() && movingLeft == true)
		{
			Position.setX((Position.getX() - 5));
		}
		updateBoundingBox();
		Anim = 0;
	}
	if (getPosition().getX() < Target->getPosition().getX() && getPosition().distance(Target->getPosition()) > 299.0f)
	{
		isMoving = true;
		movingLeft = false;
		movingRight = true;
		isAttacking = false;
		isHit = false;

		std::cout << "I SEE YOU\n";

		//Position.setX((Position.getX() + 5));
		if (getPosition().getY() == Target->getPosition().getY() && movingRight == true)
		{
			Position.setX((Position.getX() + 5));
		}
		updateBoundingBox();
		Anim = 1;
	}
	if (getPosition().getY() > Target->getPosition().getY() &&
		getPosition().getX() > Target->getPosition().getX() &&
		getPosition().distance(Target->getPosition()) < 1900.0f &&
		getPosition().distance(Target->getPosition()) > 299.0f)
	{
		isMoving = true;
		isAttacking = false;
		isHit = false;
		Anim = 0;

		std::cout << "I SEE YOU\n";
		Position.setY((Position.getY() - 5));
		if (getPosition().getY() == Target->getPosition().getY())
		{
			movingLeft = true;
			movingRight = false;
			Position.setX((Position.getX() - 5));
		}
		updateBoundingBox();
	}
	if (getPosition().getY() < Target->getPosition().getY() &&
		getPosition().getX() > Target->getPosition().getX() &&
		getPosition().distance(Target->getPosition()) < 1900.0f &&
		getPosition().distance(Target->getPosition()) > 299.0f)
	{
		isMoving = true;
		isAttacking = false;
		isHit = false;
		Anim = 0;

		std::cout << "I SEE YOU\n";
		Position.setY((Position.getY() + 5));
		if (getPosition().getY() == Target->getPosition().getY())
		{
			movingLeft = true;
			movingRight = false;
			Position.setX((Position.getX() - 5));
		}
		updateBoundingBox();
	}

	if (getPosition().getY() > Target->getPosition().getY() &&
		getPosition().getX() < Target->getPosition().getX() &&
		getPosition().distance(Target->getPosition()) < 1900.0f &&
		getPosition().distance(Target->getPosition()) > 299.0f)
	{
		isMoving = true;
		isAttacking = false;
		isHit = false;
		Anim = 1;

		std::cout << "I SEE YOU\n";
		Position.setY((Position.getY() - 5));
		if (getPosition().getY() == Target->getPosition().getY())
		{
			movingLeft = false;
			movingRight = true;
			Position.setX((Position.getX() + 5));
		}
		updateBoundingBox();
	}

	if (getPosition().getY() < Target->getPosition().getY() &&
		getPosition().getX() < Target->getPosition().getX() &&
		getPosition().distance(Target->getPosition()) < 1900.0f &&
		getPosition().distance(Target->getPosition()) > 299.0f)
	{
		isMoving = true;
		isAttacking = false;
		isHit = false;
		Anim = 1;

		std::cout << "I SEE YOU\n";
		Position.setY((Position.getY() + 5));
		if (getPosition().getY() == Target->getPosition().getY())
		{
			movingLeft = false;
			movingRight = true;
			Position.setX((Position.getX() + 5));
		}
		updateBoundingBox();
	}

	if (((getPosition().distance(Target->getPosition())) < 300.0f &&
		(getPosition().distance(Target->getPosition())) > 69.0f))
	{
		isMoving = true;
		isAttacking = false;
		isHit = false;

		std::cout << "I SEE YOU\n";

		if ((getPosition().getX() > Target->getPosition().getX() &&
			(getPosition().getX() == Target->getPosition().getX()) ||									//CHECKS IF HE IS MOVING LEFT FIRST
			(getPosition().getY() > Target->getPosition().getY()) ||									//
			(getPosition().getY() == Target->getPosition().getY()) ||
			(getPosition().getY() < Target->getPosition().getY())) && movingLeft == true)
		{
			movingRight = false;
			Position.setX((Position.getX() - 5));
		}
		
		if ((getPosition().getX() < Target->getPosition().getX() ||
			(getPosition().getX() == Target->getPosition().getX()) ||									//CHECKS IF HE IS MOVING RIGHT FIRST
			(getPosition().getY() > Target->getPosition().getY()) ||									//
			(getPosition().getY() == Target->getPosition().getY()) ||
			(getPosition().getY() < Target->getPosition().getY())) && movingRight == true)
		{
			movingLeft = false;
			Position.setX((Position.getX() + 5));
		}
		//else
		//{
		//	movingLeft == true;
		//	movingRight = false;
		//}
		updateBoundingBox();

	}

	//if (((getPosition().distance(Target->getPosition())) < 300.0f &&
	//	(getPosition().distance(Target->getPosition())) > 69.0f) && movingRight == true && Anim == 1)
	//{
	//	isMoving = true;
	//	isAttacking = false;
	//	isHit = false;

	//	std::cout << "I SEE YOU\n";

	//	if ((getPosition().getX() < Target->getPosition().getX() ||
	//		(getPosition().getX() == Target->getPosition().getX()) ||									//CHECKS IF HE IS MOVING RIGHT FIRST
	//		(getPosition().getY() > Target->getPosition().getY()) ||									//
	//		(getPosition().getY() == Target->getPosition().getY()) ||
	//		(getPosition().getY() < Target->getPosition().getY())) ||
	//		(getPosition().distance(Target->getPosition()) > 299.0f))
	//	{
	//		movingLeft = false;
	//		Position.setX((Position.getX() + 5));
	//	}
	//	updateBoundingBox();
	//}
}

void Kicker::Attack(PlayerCharacter* Target)
{
	//Attack Left
	if (getPosition().getX() > Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 70.0f)
	{
		isMoving = false;
		movingLeft = false;
		movingRight = false;
		isAttacking = true;
		isHit = false;

		Anim = 0;
		updateBoundingBox();
	}

	//Attack Right
	if (getPosition().getX() < Target->getPosition().getX() && (getPosition().distance(Target->getPosition())) < 70.0f)
	{
		isMoving = false;
		movingRight = false;
		movingLeft = false;
		isAttacking = true;
		isHit = false;

		Anim = 1;
		updateBoundingBox();
	}
}

void Kicker::Hurt(PlayerCharacter* Target)
{
	if (grunt == true)
	{
		isMoving = false;
		isAttacking = false;
		isHit = true;
	}
}

void Kicker::animation(int frameCounter, PlayerCharacter* Target)
{
	if ((isMoving == true) && (frameCounter % 4))
	{
		if (getFrame() >= 11)
		{
			setFrame(0);
		}
		setFrame(getFrame() + 1);
	}
	else if ((isAttacking == true) && (frameCounter % 4))
	{
		if (getFrame() >= 11)
		{
			setFrame(0);
		}
		else if ((getFrame() == 3) || (getFrame() == 9) && (frameCounter % 4))
		{
			std::cout << "OUCH\n";
			Target->decrementHealth();
			Target->decrementHealth();
		}
		setFrame(getFrame() + 1);
	}
	//Hit animation
	else if ((isHit == true) && (frameCounter % 30))
	{
		if (getFrame() < 11)
		{
			setFrame(11);
		}
		else if (getFrame() > 14)
		{
			setFrame(11);
		}
		setFrame(getFrame() + 1);
		//setFrame(12);
	}
}