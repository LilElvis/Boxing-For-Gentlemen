#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(const char* filePath, int frameWidthIn, int frameHeightIn, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
lastPosition(0.0f, 0.0f, "Last Position"), Character(filePath, frameWidthIn, frameHeightIn, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

PlayerCharacter::PlayerCharacter(FzlSpriteHandle spriteHandle, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
lastPosition(0.0f, 0.0f, "Last Position"), Character(spriteHandle, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

bool PlayerCharacter::Colliding(Character &objectToCollideWith)
{
	if
		(objectToCollideWith.getBoundingBoxBottomCorner().getX() < boundingBoxTopCorner.getX() &&
		objectToCollideWith.getBoundingBoxTopCorner().getX() > boundingBoxBottomCorner.getX() &&
		objectToCollideWith.getBoundingBoxBottomCorner().getY() < boundingBoxTopCorner.getY() &&
		objectToCollideWith.getBoundingBoxTopCorner().getY() > boundingBoxBottomCorner.getY())
	{
		std::cout << "Colliding \n";
		Position = lastPosition;
		return true;
	}
	return false;
}

void PlayerCharacter::Move(bool dodgeButton)
{
	if (FzlGetKey(FzlKeyD))
	{
		moving = true;
		punching = false;
		lastPosition = Position;
		Position.setX((Position.getX() + 10));
		updateBoundingBox();
		Anim = 0;
	}
	else if ((FzlGetKey(FzlKeyD) && 
		(FzlGetKey(FzlKeySpace))) ||
		((FzlGetKey(FzlKeyD) &&
		(FzlGetKey(FzlKeyC))) ||
		((FzlGetKey(FzlKeyD) &&
		(FzlGetKey(FzlKeyV))))))
	{
		moving = true;
		punching = true;
	}
	else if (FzlGetKey(FzlKeySpace) ||
		FzlGetKey(FzlKeyC) ||
		FzlGetKey(FzlKeyV))
	{
		moving = false;
		punching = true;
	}
	else
	{
		moving = false;
		punching = false;
	}
	if (FzlGetKey(FzlKeyA))
	{
		moving = true;
		punching = false;
		lastPosition = Position;
		Position.setX((Position.getX() - 10));
		updateBoundingBox();
		Anim = 1;
	}
	else if (FzlGetKey(FzlKeyA) &&
		(FzlGetKey(FzlKeySpace)) ||
		(FzlGetKey(FzlKeyC) &&
		(FzlGetKey(FzlKeySpace)) ||
		(FzlGetKey(FzlKeyV) &&
		(FzlGetKey(FzlKeySpace)))))
	{
		moving = true;
		punching = true;
	}
	else if (FzlGetKey(FzlKeySpace) ||
		FzlGetKey(FzlKeyC) ||
		FzlGetKey(FzlKeyV))
	{
		moving = false;
		punching = true;
	}
	else
	{
		moving = false;
		punching = false;
	}
	if (FzlGetKey(FzlKeyW))
	{
		moving = true;
		punching = false;
		lastPosition = Position;
		Position.setY((Position.getY() + 10));
		updateBoundingBox();
	}
	else if (FzlGetKey(FzlKeyW) &&
		(FzlGetKey(FzlKeySpace)) ||
		(FzlGetKey(FzlKeyC) &&
		(FzlGetKey(FzlKeySpace)) ||
		(FzlGetKey(FzlKeyV) &&
		(FzlGetKey(FzlKeySpace)))))
	{
		moving = true;
		punching = true;
	}
	else if (FzlGetKey(FzlKeySpace) ||
		FzlGetKey(FzlKeyC) ||
		FzlGetKey(FzlKeyV))
	{
		moving = false;
		punching = true;
	}
	else
	{
		moving = false;
		punching = false;
	}
	if (FzlGetKey(FzlKeyS))
	{
		moving = true;
		punching = false;
		lastPosition = Position;
		Position.setY((Position.getY() - 10));
		updateBoundingBox();
	}
	else if (FzlGetKey(FzlKeyS) &&
		(FzlGetKey(FzlKeySpace)) ||
		(FzlGetKey(FzlKeyC) &&
		(FzlGetKey(FzlKeySpace)) ||
		(FzlGetKey(FzlKeyV) &&
		(FzlGetKey(FzlKeySpace)))))
	{
		moving = true;
		punching = true;
	}
	else if (FzlGetKey(FzlKeySpace) ||
		FzlGetKey(FzlKeyC) ||
		FzlGetKey(FzlKeyV))
	{
		moving = false;
		punching = true;
	}
	else
	{
		moving = false;
		punching = false;
	}
	if (FzlGetKey(FzlKeyD) && dodgeButton)
	{
		dodging = true;
		lastPosition = Position;
		Position.setX((Position.getX() + 40));
		updateBoundingBox();
		Anim = 0;
	}
	else
	{
		dodging = false;
	}
	if (FzlGetKey(FzlKeyA) && dodgeButton)
	{
		dodging = true;
		lastPosition = Position;
		Position.setX((Position.getX() - 40));
		updateBoundingBox();
		Anim = 1;
	}
	else
	{
		dodging = false;
	}
	if (FzlGetKey(FzlKeyW) && dodgeButton)
	{
		dodging = true;
		lastPosition = Position;
		Position.setY((Position.getY() + 40));
		updateBoundingBox();
	}
	else
	{
		dodging = false;
	}
	if (FzlGetKey(FzlKeyS) && dodgeButton)
	{
		dodging = true;
		lastPosition = Position;
		Position.setY((Position.getY() - 40));
		updateBoundingBox();
	}
	else
	{
		dodging = false;
	}
}

int PlayerCharacter::getObjectsToCompare()
{
	return objectsToCompare;
}

void PlayerCharacter::setLastPosition()
{
	lastPosition = Position;
	updateBoundingBox();
}

Vector PlayerCharacter::getLastPosition()
{
	return lastPosition;
}

void PlayerCharacter::Hurt(Character* Target)
{
	if (grunt == true)
	{
		isHit = true;
		punching = false;
		moving = false;
		dodging = false;
	}
}

void PlayerCharacter::animation(int frameCounter, bool dodgeKey)
{
	if (FzlGetKey(FzlKeyD) && frameCounter % 4 ||
		FzlGetKey(FzlKeyA) && frameCounter % 4 ||
		FzlGetKey(FzlKeyW) && frameCounter % 4 ||
		FzlGetKey(FzlKeyS) && frameCounter % 4)
	{
		moving = true;
		punching = false;
		isHit = false;
		if (getFrame() < 7)
		{
			setFrame(7);
		}
		else if (getFrame() == 11)
		{
			setFrame(7);
		}
		setFrame((getFrame() + 1));
	}
	else if (FzlGetKey(FzlKeyD) && moving == true && punching == false && frameCounter % 4 ||
		FzlGetKey(FzlKeyA) && moving == true && punching == false && frameCounter % 4 ||
		FzlGetKey(FzlKeyW) && moving == true && punching == false && frameCounter % 4 ||
		FzlGetKey(FzlKeyS) && moving == true && punching == false && frameCounter % 4)
	{
		moving = true;
		punching = false;
		isHit = false;
		if (getFrame() < 7)
		{
			setFrame(7);
		}
		else if (getFrame() == 11)
		{
			setFrame(7);
		}
		setFrame((getFrame() + 1));
	}
	else if (FzlGetKey(FzlKeySpace) && punching == true && moving == false)
	{
		punching = true;
		moving = false;
		isHit = false;
		if (getFrame() < 14)
		{
			setFrame(14);
		}
		else if (getFrame() == 20)
		{
			setFrame(14);
		}
		setFrame((getFrame() + 1));
	}
	else if (((FzlGetKey(FzlKeyD) && (FzlGetKey(FzlKeySpace)) ||
		(FzlGetKey(FzlKeyA) && (FzlGetKey(FzlKeySpace)) ||
		(FzlGetKey(FzlKeyW) && (FzlGetKey(FzlKeySpace)) ||
		(FzlGetKey(FzlKeyS) && (FzlGetKey(FzlKeySpace))) && 
		(moving == true && punching == true))))))
	{
		moving = true;
		punching = true;
		isHit = false;
		if (getFrame() < 14)
		{
			setFrame(14);
		}
		else if (getFrame() == 20)
		{
			setFrame(14);
		}
		setFrame((getFrame() + 1));
	}
	else if (FzlGetKey(FzlKeyC) && punching == true && moving == false)
	{
		punching = true;
		moving = false;
		isHit = false;
		if (getFrame() < 21)
		{
			setFrame(21);
		}
		else if (getFrame() == 27)
		{
			setFrame(21);
		}
		setFrame((getFrame() + 1));
	}
	else if (((FzlGetKey(FzlKeyD) && (FzlGetKey(FzlKeyC)) ||
		(FzlGetKey(FzlKeyA) && (FzlGetKey(FzlKeyC)) ||
		(FzlGetKey(FzlKeyW) && (FzlGetKey(FzlKeyC)) ||
		(FzlGetKey(FzlKeyS) && (FzlGetKey(FzlKeyC))) ||
		(FzlGetKey(FzlKeyC) && (moving == true && punching == true)))))))
	{
		moving = true;
		punching = true;
		isHit = false;
		if (getFrame() < 21)
		{
			setFrame(21);
		}
		else if (getFrame() == 27)
		{
			setFrame(21);
		}
		setFrame((getFrame() + 1));
	}
	else if (FzlGetKey(FzlKeyV) && punching == true && moving == false) //&&superPunch=true;
	{
		punching = true;
		moving = false;
		isHit = false;
		if (getFrame() < 29)
		{
			setFrame(29);
		}
		else if (getFrame() == 37)
		{
			setFrame(29);
		}
		setFrame((getFrame() + 1));
	}
	else if (((FzlGetKey(FzlKeyD) && (FzlGetKey(FzlKeyV)) ||
		(FzlGetKey(FzlKeyA) && (FzlGetKey(FzlKeyV)) ||
		(FzlGetKey(FzlKeyW) && (FzlGetKey(FzlKeyV)) ||
		(FzlGetKey(FzlKeyS) && (FzlGetKey(FzlKeyV))) ||
		(FzlGetKey(FzlKeyC) && (moving == true && punching == true)))))))
	{
		moving = true;
		punching = true;
		isHit = false;
		if (getFrame() < 29)
		{
			setFrame(29);
		}
		else if (getFrame() == 37)
		{
			setFrame(29);
		}
		setFrame((getFrame() + 1));
	}
	else if (FzlGetKey(FzlKeyLeftShift) && dodging == true)
	{
		if (getFrame() < 37)
		{
			setFrame(37);
		}
		else if (getFrame() == 39)
		{
			setFrame(37);
		}
		setFrame((getFrame() + 1));
	}
	else if (isHit == true)
	{
		if (getFrame() < 39)
		{
			setFrame(39);
		}
		else if (getFrame() > 40)
		{
			setFrame(39);
		}
		setFrame(getFrame() + 1);
	}
	else if (frameCounter % 4)
	{
		isHit = false;
		if (getFrame() >= 3)
		{
			setFrame(0);
		}
		setFrame((getFrame() + 1));
	}

//animationNum state;
//
//if (FzlGetKey(FzlKeyW) || FzlGetKey(FzlKeyS) || FzlGetKey(FzlKeyA) || FzlGetKey(FzlKeyD))
//{
//	state = Walking;
//	moving = true;
//}
//else if (FzlGetKey(FzlKeySpace))
//{
//	state = Punching;
//}
//else if (FzlGetKey(FzlKeyC))
//{
//	state = Heavy;
//}
//else if (FzlGetKey(FzlKeyV))
//{
//	state = Super;
//}
//else if (isHit == true)
//{
//	state = Flinch;
//	isHit = false;
//}
//else
//{
//	state = Idle;
//	moving = false;
//}


//switch (state)
//	{
//case Walking:
//	if (frameCounter % 4)
//	{
//		if (getFrame() < 7)
//		{
//			setFrame(7);
//		}
//		else if (getFrame() == 11)
//		{
//			setFrame(7);
//		}
//		setFrame((getFrame() + 1));
//	}
//				break;
//case Punching:
//				if (getFrame() < 14)
//				{
//					setFrame(14);
//				}
//				else if (getFrame() == 20)
//				{
//					setFrame(14);
//				}
//				setFrame((getFrame() + 1));
//				break;
//case Heavy:
//				if (getFrame() < 21)
//				{
//					setFrame(21);
//				}
//				else if (getFrame() == 27)
//				{
//					setFrame(21);
//				}
//				setFrame((getFrame() + 1));
//				break;
//case Super:
//				if (getFrame() < 29)
//				{
//					setFrame(29);
//				}
//				else if (getFrame() == 37)
//				{
//					setFrame(29);
//				}
//				setFrame((getFrame() + 1));
//				break;
//case Flinch:
//				if (getFrame() < 39)
//				{
//					setFrame(39);
//				}
//				else if (getFrame() > 40)
//				{
//					setFrame(39);
//				}
//				setFrame(getFrame() + 1);
//				break;
//case Idle:
//	if (frameCounter % 4)
//	{
//		if (getFrame() >= 3)
//		{
//			setFrame(0);
//		}
//		setFrame((getFrame() + 1));
//	}
//}	
}

void sort(std::map<int, Character *> &a_map, std::vector<Character *> a_vector, PlayerCharacter *a_main_character)
{
	a_map.clear();

	for (auto itr = a_vector.begin(), itrEnd = a_vector.end(); itr != itrEnd; itr++)
	{
		Character *character = (*itr);

		int depth = ((1080 - character->getPosition().getY()) * 1920) + character->getPosition().getX();
		a_map[depth] = character;
	}

	int depth = ((1080 - a_main_character->Position.getY()) * 1920) + a_main_character->Position.getX();
	a_map[depth] = a_main_character;
}