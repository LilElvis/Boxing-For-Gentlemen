#include "Crate.h"

//Crates and props to break

Crate::Crate(const char* filePath, int frameWidthIn, int frameHeightIn, float characterPosXIn, float characterPosYIn, float topCornerXIn, float topCornerYIn, float bottomCornerXIn, float bottomCornerYIn, int healthIn) :
Character(filePath, frameWidthIn, frameHeightIn, characterPosXIn, characterPosYIn, topCornerXIn, topCornerYIn, bottomCornerXIn, bottomCornerYIn, healthIn)
{

}

void Crate::Idle()
{

}

void Crate::Break(PlayerCharacter* Target)
{
	if (Health < 0)
	{
		kill();
	}
}