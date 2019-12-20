#pragma once
#include "GameStates.h"
#include "PlayerCharacter.h"
#include "Crate.h"
#include "Ballin.h"
#include "Pilot.h"
#include "Embassy.h"
#include "Broviet.h"
#include "Kicker.h"
#include "Gulag.h"

static FzlSpriteHandle mentlegen;
static FzlSpriteHandle maxGentlemanBar;
static FzlSpriteHandle healthBar;
static FzlSpriteHandle boundaryBox;
static FzlSpriteHandle gulagGuard;
static FzlSpriteHandle kKicker;
static FzlSpriteHandle bSoldier;
static FzlSpriteHandle eGuard;
static FzlSpriteHandle pilotGuy;
static FzlSpriteHandle boss;
static FzlSpriteHandle vodka;
static FzlSpriteHandle gotBeef;
static FzlSpriteHandle MAINMENU;
static FzlSpriteHandle LOREMENU;

static FzlSoundHandle punch;
static FzlSoundHandle heavyPunch;
static FzlSoundHandle bellRing;
static FzlSoundHandle death;
static FzlSoundHandle crate;
static FzlSoundHandle kicker;
static FzlSoundHandle broviet;
static FzlSoundHandle embassy;
static FzlSoundHandle gulp;
static FzlSoundHandle gulag;
static FzlSoundHandle pilot;
static FzlSoundHandle ballin;
//static FzlSoundHandle mainMenuSong;
//static FzlSoundHandle gulagSong;
//static FzlSoundHandle sewerSong;
//static FzlSoundHandle streetSong;
//static FzlSoundHandle embassySong;
//static FzlSoundHandle planeSong;
//static FzlSoundHandle ballinSong;
static FzlSoundHandle creditsSong;


class Intro : public GameState
{
public:
	Intro();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	Crate cage, cage2, cage3;
	Character wall, tutorial, tutorial2, MaxGentleman, HealthBar, boundary1, boundary2, boundary3, boundary4, boundary5, boundary6, boundary7, boundary8, boundary9;

	FzlSpriteHandle background;
	Gulag guy, guy2;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class PrisonWalkway1 : public GameState
{
public:
	PrisonWalkway1();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2, boundary3, boundary4, boundary5, boundary6, boundary7, boundary8, boundary9, boundary10;
	FzlSpriteHandle background;
	Gulag guy, guy2, guy3;
	Kicker kazotsky, kazotsky2;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class PrisonWalkway2 : public GameState
{
public:
	PrisonWalkway2();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	Crate grate;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2, boundary3, boundary4, boundary5, boundary6, boundary7, boundary8, boundary9, boundary10;
	FzlSpriteHandle background;
	Gulag guy, guy2, guy3;
	Kicker kazotsky, kazotsky2;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Sewer : public GameState
{
public:
	Sewer();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	Crate box;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2, boundary3;
	FzlSpriteHandle background;
	Soldier unit1;
	Kicker kazotsky;
	Gulag guy, guy2;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Sewer2 : public GameState
{
public:
	Sewer2();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	Crate box;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2, boundary3;
	FzlSpriteHandle background;
	Soldier unit1;
	Kicker kazotsky, kazotsky2, kazotsky3;
	Gulag guy;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Sewer3 : public GameState
{
public:
	Sewer3();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	Crate box, ladder;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2, boundary3, boundary4, boundary5, boundary6;
	FzlSpriteHandle background;
	Soldier unit1, unit2;
	Kicker kazotsky;
	Gulag guy, guy2;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Street : public GameState
{
public:
	Street();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	Crate box;
	Character LampPost, Garbage, Barrel, Trash, Barrel2, sewerHole, MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2, boundary3;
	FzlSpriteHandle background;
	Embassy guard1, guard2;
	Soldier unit1, unit2;
	Kicker kazotsky;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Street2 : public GameState
{
public:
	Street2();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	Crate box, box2, box3, box4;
	Character LampPost, Barrel, Barrel2, Barrel3, Barrel4, Trash, MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2, boundary3;
	FzlSpriteHandle background;
	Embassy guard1, guard2;
	Soldier unit;
	Kicker kazotsky, kazotsky2;
	Gulag guy;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Street3 : public GameState
{
public:
	Street3();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	//Crate box;
	Character LampPost, MaxGentleman, HealthBar, beef, vodkaBottle, entrance, boundary1, boundary2, boundary3, boundary4, boundary5, boundary6;
	FzlSpriteHandle background;
	Embassy guard1, guard2;
	Soldier unit;
	Kicker kazotsky, kazotsky2;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class EmbassyLevel : public GameState
{
public:
	EmbassyLevel();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	//Crate box;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2, boundary3, boundary4, boundary5, boundary6, boundary7;
	FzlSpriteHandle background;
	Embassy guard1, guard2;
	Soldier unit;
	Kicker kazotsky, kazotsky2;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
  bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Embassy2 : public GameState
{
public:
	Embassy2();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	//Crate box;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2, boundary3, boundary4, boundary5;
	FzlSpriteHandle background;
	Pilot pilot1, pilot2;
	Embassy guard1;
	Soldier unit;
	Kicker kazotsky, kazotsky2;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
  bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Embassy3 : public GameState
{
public:
	Embassy3();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	//Crate box;
	Character MaxGentleman, HealthBar, ramp, beef, vodkaBottle, boundary1, boundary2, boundary3;
	FzlSpriteHandle background;
	Pilot pilot1, pilot2;
	Embassy guard1, guard2;
	Soldier unit;
	Kicker kazotsky, kazotsky2;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Plane : public GameState
{
public:
	Plane();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	//Crate box;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2;
	FzlSpriteHandle background;
	Embassy guard1;
	Soldier unit1, unit2;
	Kicker kazotsky;
	Gulag guy; 
	//FzlSoundHandle crate;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Plane2 : public GameState
{
public:
	Plane2();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	//Crate box;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2;
	FzlSpriteHandle background;
	Pilot pilot1, pilot2;
	Embassy guard1, guard2;
	Soldier unit;
	Kicker kazotsky, kazotsky2, kazotsky3;
	Gulag guy;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};


class Plane3 : public GameState
{
public:
	Plane3();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	//Crate box;
	Character MaxGentleman, HealthBar, beef, vodkaBottle, boundary1, boundary2;
	FzlSpriteHandle background;
	Pilot pilot1, pilot2;
	Embassy guard1, guard2;
	Soldier unit1, unit2;
	Kicker kazotsky;
	Gulag guy;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;

	
	bool superPunch = false;
};

class Final : public GameState
{
public:
	Final();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
	PlayerCharacter Mentlegen;
	//Crate box;
	Character MaxGentleman, HealthBar, boundary1, boundary2, boundary3, boundary4, boundary5;
	FzlSpriteHandle background;
	Ballin broseff;

	std::vector<Character *> CharacterCollisionList;

	std::vector<Character *> CharacterSortVector;

	std::map<int, Character*> CharacterMap;

	int frameCounter = 0;

	bool spaceWasPressed = false;
	bool cWasPressed = false;
	bool vWasPressed = false;
	bool shiftWasPressed = false;


	bool superPunch = false;
};

class GameOver : public GameState
{
public:
	GameOver();
	void enter();
	void exit();
	void Update();
	bool shouldEnd();
private:
	bool hasBeenInitialized;
	FzlSpriteHandle background;
	bool endCondition;

	int frameCounter = 0;

};

class MainMenu : public GameState
{
public:
	MainMenu();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
};

class LoreMenu : public GameState
{
public:
	LoreMenu();
	void enter();
	void exit();
	void Update();
private:
	bool hasBeenInitialized;
};

class CreditScreen : public GameState
{
public:
	CreditScreen();
	void enter();
	void exit();
	void Update();
	bool shouldEnd();
private:
	bool hasBeenInitialized;
	FzlSpriteHandle background;
	bool endCondition;
};

void spriteLoading();

void soundLoading();