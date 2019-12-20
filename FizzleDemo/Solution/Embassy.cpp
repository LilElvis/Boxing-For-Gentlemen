#include "Embassy.h"

#include "Broviet.h"

//BROVIET UNION SOLDIER
Embassy::Embassy(const char* filePath, int frameWidthIn, int frameHeightIn, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(filePath, frameWidthIn, frameHeightIn, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

Embassy::Embassy(FzlSpriteHandle spriteHandle, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(spriteHandle, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

//Broviet Soldier States
void Embassy::Idle()
{
	isIdle = true;
}

void Embassy::Move(PlayerCharacter* Target)
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

void Embassy::Attack(PlayerCharacter* Target)
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
			Position.setX((Position.getX() + 40));
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
			Position.setX((Position.getX() - 40));
		}
		else
		{
			isDodging = false;
		}

		Anim = 1;
		updateBoundingBox();
	}
}

void Embassy::Hurt(PlayerCharacter* Target)
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

void Embassy::animation(int frameCounter, PlayerCharacter* Target)
{
	//Walking animation
	if ((isMoving == true) && (frameCounter % 4))
	{
		if (getFrame() < 17)
		{
			setFrame(17);
		}
		else if (getFrame() >= 21)
		{
			setFrame(17);
		}
		setFrame(getFrame() + 1);
	}
	else if ((isAttacking == true) && (frameCounter % 4))
	{
		if (getFrame() < 7)
		{
			setFrame(7);
		}
		else if (getFrame() >= 14)
		{
			setFrame(7);
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
	//Hit animation
	else if ((isHit == true))
	{
		if (getFrame() < 21)
		{
			setFrame(21);
		}
		else if (getFrame() > 23)
		{
			setFrame(21);
		}
		setFrame(getFrame() + 1);
	}
	//Idle animation
	else if ((isIdle == true) && (frameCounter % 4))
	{
		if (getFrame() >= 6)
		{
			setFrame(0);
		}
		setFrame(getFrame() + 1);
	}
}