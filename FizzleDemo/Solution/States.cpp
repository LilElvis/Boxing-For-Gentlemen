#include "States.h"

void spriteLoading()
{
	MAINMENU = FzlLoadSprite("../../../Assets/Main_Menu.png", 1920, 1080);
	LOREMENU = FzlLoadSprite("../../../Assets/Lore_Menu.png", 1920, 1080);
	healthBar = FzlLoadSprite("../../../Assets/healthpoints.png", 404, 64);
	maxGentlemanBar = FzlLoadSprite("../../../Assets/maxgentleman.png", 320, 128);
	boundaryBox = FzlLoadSprite("../../../Assets/BoundingBox.png", 1920, 0);
	mentlegen = FzlLoadSprite("../../../Assets/mentlegen.png", 160, 160);
	gulagGuard = FzlLoadSprite("../../../Assets/gulagguard.png", 128, 108);
	kKicker = FzlLoadSprite("../../../Assets/Kazotsky_Kicker.png", 144, 144);
	bSoldier = FzlLoadSprite("../../../Assets/broviet.png", 128, 144);
	gotBeef = FzlLoadSprite("../../../Assets/gotbeef.png", 60, 30);
	vodka = FzlLoadSprite("../../../Assets/vodkapickup.png", 32, 60);
	eGuard = FzlLoadSprite("../../../Assets/embassy.png", 128, 144);
	pilotGuy = FzlLoadSprite("../../../Assets/pilot.png", 128, 144);
	boss = FzlLoadSprite("../../../Assets/broseff_ballin.png", 160, 160);
}

void soundLoading()
{
	heavyPunch = FzlLoadSound("../../../Assets/Sounds/heavy_punch.wav", 0);
	punch = FzlLoadSound("../../../Assets/Sounds/punch.wav", 0);
	bellRing = FzlLoadSound("../../../Assets/Sounds/bell_ring.wav", 0);
	death = FzlLoadSound("../../../Assets/Sounds/PossibleDeathSound.wav", 0);
	crate = FzlLoadSound("../../../Assets/Sounds/CrateSound3.wav", 0);
	kicker = FzlLoadSound("../../../Assets/Sounds/KazotskyKicker.wav", 0);
	broviet = FzlLoadSound("../../../Assets/Sounds/BrovietUnionGrunt.wav", 0);
	embassy = FzlLoadSound("../../../Assets/Sounds/EmbassyGuardGrunt.wav", 0);
	gulp = FzlLoadSound("../../../Assets/Sounds/VodkaGulpingSound.wav", 0);
	gulag = FzlLoadSound("../../../Assets/Sounds/GulagGuardSound.wav", 0);
	pilot = FzlLoadSound("../../../Assets/Sounds/PilotGrunt.wav", 0);
	ballin = FzlLoadSound("../../../Assets/Sounds/BroseffBallin.wav", 0);
	//mainMenuSong = FzlLoadSound("../../../Assets/Sounds/mainMenuSong.wav", 0);
	//gulagSong = FzlLoadSound("../../../Assets/Sounds/GulagSong.wav", 0);
	//sewerSong = FzlLoadSound("../../../Assets/Sounds/SewerSong.wav", 0);
	//streetSong = FzlLoadSound("../../../Assets/Sounds/StreetSong.wav", 0);
	//embassySong = FzlLoadSound("../../../Assets/Sounds/EmbassySong.wav", 0);
	//planeSong = FzlLoadSound("../../../Assets/Sounds/PlaneSong.wav", 0);
	//ballinSong = FzlLoadSound("../../../Assets/Sounds/BallinSong.wav", 0);
	creditsSong = FzlLoadSound("../../../Assets/Sounds/CreditsSong.wav", 1);
}

//global variables
int maxGentleman = 5000;
int currentHealth = 2;
int beefRand;
int vodkaRand;

//LEVELS-------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GULAG CELL - INTRO SCENE

void Intro::Update()
{
	std::cout << "Before drawing\t";
	std::cout << maxGentlemanBar << " " << healthBar << " " << mentlegen << " " << boundaryBox << std::endl;
	if (hasBeenInitialized == false)
	{
     	enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift))
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&guy2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	tutorial.draw();
	tutorial2.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//std::cout << "HELLO \t";
	//std::cout << maxGentlemanBar << " " << healthBar << " " << mentlegen << " " << boundaryBox << std::endl;

	//Enemy Moving and attacking------------------------------
	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);
	
	guy2.Move(&Mentlegen);
	guy2.Attack(&Mentlegen);
	guy2.Hurt(&Mentlegen);
	guy2.setGrunt(false);

	cage.Break(&Mentlegen);
	if ((cPressed && (Mentlegen.getPosition().distance(cage.getBoundingBoxTopCorner()) < 150.0f)) || 
		(cPressed && (Mentlegen.getPosition().distance(cage2.getBoundingBoxTopCorner()) < 150.0f)) || 
		(cPressed && (Mentlegen.getPosition().distance(cage3.getBoundingBoxTopCorner()) < 150.0f)))
	{
		cage.decrementHealth();
		cage.setPosition(-1000.0f, -1000.0f);
		cage2.setPosition(-1000.0f, -1000.0f);
		cage3.setPosition(-1000.0f, -1000.0f);
		cage.updateBoundingBox();
		cage2.updateBoundingBox();
		cage3.updateBoundingBox();
		FzlPlaySound(crate);
	}

	//Animations--------------------------------------------

	guy.Idle();
	guy2.Idle();

	guy.animation(frameCounter, &Mentlegen);
	guy2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Intro::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}
	
	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		//FzlPlaySound(gulag);
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		//FzlPlaySound(gulag);
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		guy2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		//FzlPlaySound(gulag);
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		//FzlPlaySound(gulag);
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() > 1900)
	{
		Intro::exit();
		m_parent->GetGameState("PrisonWalkway1")->SetPaused(false);

	}

	currentHealth = Mentlegen.getHealth();
	//FzlPlaySound(song);
}

Intro::Intro() :
	Mentlegen(mentlegen, 300.0f, 250.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	//beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	guy(gulagGuard, 1600.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	guy2(gulagGuard, 1675.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	cage("../../../Assets/gulagGate.png", 422, 1198, 755.0f, 62.0f, 72.0f, 88.0f, 0.0f, 0.0f, 0),
	cage2("../../../Assets/gulagGate.png", 422, 1198, 755.0f, 62.0f, 135.0f, 174.0f, 72.0f, 88.0f, 0),
	cage3("../../../Assets/gulagGate.png", 422, 1198, 755.0f, 62.0f, 209.0f, 254.0f, 135.0f, 174.0f, 0),
	wall("../../../Assets/startingcell_frontwall.png", 322, 2160, 612.0f, 0.0f, 160.0f, 70.0f, 0.0f, 0.0f, 2),
	tutorial("../../../Assets/walktutorial.png", 300, 300, 1200.0f, 730.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	tutorial2("../../../Assets/heavypunchtutorial2.png", 300, 300, 1200.0f, 470.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	boundary1(boundaryBox, 960.0f, 302.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),	
	boundary3(boundaryBox, 410.0f, 303.0f, 150.0f, 48.0f, -173.0f, -48.0f, 0),
	boundary4(boundaryBox, 50.0f, 281.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary5(boundaryBox, 0.0f, 224.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary6(boundaryBox, 0.0f, 174.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary7(boundaryBox, -10.0f, 122.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary8(boundaryBox, 14.0f, 44.0f, 23.0f, 49.0f, 0.0f, 0.0f, 0),
	boundary9(boundaryBox, 0.0f, 0.0f, 14.0f, 44.0f, 0.0f, 0.0f, 0)
{
	std::cout << "Constructor\t";
	std::cout << maxGentlemanBar << " " << healthBar << " " << mentlegen << " " << boundaryBox << std::endl;
}

void Intro::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Intro::SetPaused(m_paused);
	}
	
	
	background = FzlLoadSprite("../../../Assets/starting_cell.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&guy2);
	CharacterCollisionList.push_back(&cage);
	CharacterCollisionList.push_back(&cage2);
	CharacterCollisionList.push_back(&cage3);
	CharacterCollisionList.push_back(&wall);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);
	CharacterCollisionList.push_back(&boundary4);
	CharacterCollisionList.push_back(&boundary5);
	CharacterCollisionList.push_back(&boundary6);
	CharacterCollisionList.push_back(&boundary7);
	CharacterCollisionList.push_back(&boundary8);
	CharacterCollisionList.push_back(&boundary9);
						   
	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&guy2);
	CharacterSortVector.push_back(&cage);
	CharacterSortVector.push_back(&wall);
	//CharacterSortVector.push_back(&beef);
}

void Intro::exit()
{
	hasBeenInitialized = false;
	if (m_paused == false)
	{
		m_paused = true;
		Intro::SetPaused(m_paused);
		PrisonWalkway1(hasBeenInintialized);

		FzlDeleteSprite(background);

		FzlDeleteSprite(cage.getSpriteHandle());
		FzlDeleteSprite(cage2.getSpriteHandle());
		FzlDeleteSprite(cage3.getSpriteHandle());
		FzlDeleteSprite(wall.getSpriteHandle());
		FzlDeleteSprite(tutorial2.getSpriteHandle());
		
	}
}





















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GULAG PRISON 1





























void PrisonWalkway1::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&guy2);
	Mentlegen.Hurt(&guy3);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&kazotsky2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}/*
	 for (auto itr = CharacterCollisionList.begin(), itrEnd = CharacterCollisionList.end(); itr != itrEnd; itr++)
	 {
	 (itr->updateBoundingBox());
	 }*/

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}
	
	//Beef

	if (guy2.getAlive() == false)
	{
		beef.setPosition(guy2.getDeathPosition().getX(), guy2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);
	
	guy2.Move(&Mentlegen);
	guy2.Attack(&Mentlegen);
	guy2.Hurt(&Mentlegen);
	guy2.setGrunt(false);

	guy3.Move(&Mentlegen);
	guy3.Attack(&Mentlegen);
	guy3.Hurt(&Mentlegen);
	guy3.setGrunt(false);

	kazotsky.Move(&Mentlegen);
	kazotsky.Attack(&Mentlegen);
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	kazotsky2.Move(&Mentlegen);
	kazotsky2.Attack(&Mentlegen);
	kazotsky2.Hurt(&Mentlegen);
	kazotsky2.setGrunt(false);


	//Animations--------------------------------------------

	guy.Idle();
	guy2.Idle();
	guy3.Idle();

	guy.animation(frameCounter, &Mentlegen);
	guy2.animation(frameCounter, &Mentlegen);
	guy3.animation(frameCounter, &Mentlegen);
	kazotsky.animation(frameCounter, &Mentlegen);
	kazotsky2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy3.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		PrisonWalkway1::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		guy2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy3.getPosition()) < 100.0f))
	{
		guy3.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy3.setGrunt(true);
		if (guy3.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy3.getPosition()) < 100.0f))
	{
		guy3.decrementHealth();
		guy3.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy3.setGrunt(true);
		if (guy3.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy3.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy3.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy3.setGrunt(true);
		if (guy3.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		kazotsky2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() > 1900)
	{
		PrisonWalkway1::exit();
		m_parent->GetGameState("PrisonWalkway2")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

PrisonWalkway1::PrisonWalkway1() :
	Mentlegen(mentlegen, 313.0f, 250.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	guy(gulagGuard, 1100.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	guy2(gulagGuard, 1200.0f, 280.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	guy3(gulagGuard, 1320.0f, 215.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	kazotsky(kKicker, 1800.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	kazotsky2(kKicker, 1700.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	boundary1(boundaryBox, 960.0f, 320.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary3(boundaryBox, 310.0f, 263.0f, 100.0f, 48.0f, -173.0f, -48.0f, 0),
	boundary4(boundaryBox, 380.0f, 330.0f, 120.0f, 48.0f, -173.0f, -48.0f, 0),
	boundary5(boundaryBox, 220.0f, 263.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary6(boundaryBox, 220.0f, 224.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary7(boundaryBox, 210.0f, 174.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary8(boundaryBox, 160.0f, 122.0f, 52.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary9(boundaryBox, 65.0f, 54.0f, 38.0f, 49.0f, 0.0f, -10.0f, 0),
	boundary10(boundaryBox, 0.0f, 0.0f, 14.0f, 64.0f, 20.0f, -10.0f, 0)
{
}

void PrisonWalkway1::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		PrisonWalkway1::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/gulagpart1.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&guy2);
	CharacterCollisionList.push_back(&guy3);
	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&kazotsky2);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);
	CharacterCollisionList.push_back(&boundary4);
	CharacterCollisionList.push_back(&boundary5);
	CharacterCollisionList.push_back(&boundary6);
	CharacterCollisionList.push_back(&boundary7);
	CharacterCollisionList.push_back(&boundary8);
	CharacterCollisionList.push_back(&boundary9);

	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&guy2);
	CharacterSortVector.push_back(&guy3);
	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&kazotsky2);
	CharacterSortVector.push_back(&vodkaBottle);
	CharacterSortVector.push_back(&beef);
}

void PrisonWalkway1::exit()
{
	if (m_paused == false)
	{
		m_paused = true;
		PrisonWalkway1::SetPaused(m_paused);
		PrisonWalkway2(hasBeenInintialized);

		FzlDeleteSprite(background);

	}
}





















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GULAG PRISON 2




























void PrisonWalkway2::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&guy2);
	Mentlegen.Hurt(&guy3);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&kazotsky2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}/*
	 for (auto itr = CharacterCollisionList.begin(), itrEnd = CharacterCollisionList.end(); itr != itrEnd; itr++)
	 {
	 (itr->updateBoundingBox());
	 }*/

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guy2.getAlive() == false)
	{
		beef.setPosition(guy2.getDeathPosition().getX(), guy2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);

	guy2.Move(&Mentlegen);
	guy2.Attack(&Mentlegen);
	guy2.Hurt(&Mentlegen);
	guy2.setGrunt(false);

	guy3.Move(&Mentlegen);
	guy3.Attack(&Mentlegen);
	guy3.Hurt(&Mentlegen);
	guy3.setGrunt(false);

	kazotsky.Move(&Mentlegen);
	kazotsky.Attack(&Mentlegen);
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	kazotsky2.Move(&Mentlegen);
	kazotsky2.Attack(&Mentlegen);
	kazotsky2.Hurt(&Mentlegen);
	kazotsky2.setGrunt(false);

	grate.Break(&Mentlegen);
	if (cPressed && (Mentlegen.getPosition().distance(grate.getPosition()) < 200.0f))
	{
		grate.decrementHealth();
		grate.decrementHealth();
		grate.decrementHealth();
		FzlPlaySound(crate);
	}

	//Animations--------------------------------------------

	guy.Idle();
	guy2.Idle();
	guy3.Idle();

	guy.animation(frameCounter, &Mentlegen);
	guy2.animation(frameCounter, &Mentlegen);
	guy3.animation(frameCounter, &Mentlegen);
	kazotsky.animation(frameCounter, &Mentlegen);
	kazotsky2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy3.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		PrisonWalkway2::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		guy2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	
	if (spacePressed && (Mentlegen.getPosition().distance(guy3.getPosition()) < 100.0f))
	{
		guy3.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy3.setGrunt(true);
		if (guy3.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy3.getPosition()) < 100.0f))
	{
		guy3.decrementHealth();
		guy3.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy3.setGrunt(true);
		if (guy3.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy3.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy3.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy3.setGrunt(true);
		if (guy3.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		kazotsky2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if ((Mentlegen.getPosition().getX() > 1610) &&
		(Mentlegen.getPosition().getX() < 1680) &&
		((Mentlegen.getPosition().getY() > 230) &&
		(Mentlegen.getPosition().getY() < 300)))
	{
		PrisonWalkway2::exit();
		m_parent->GetGameState("Sewer")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

PrisonWalkway2::PrisonWalkway2() :
	Mentlegen(mentlegen, 100.0f, 250.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	grate("../../../Assets/sewergrate.png", 193, 369, 1645.0f, 350.0f, 55.0f, -43.0f, -52.0f, -182.0f, 2),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	guy(gulagGuard, 1250.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	guy2(gulagGuard, 1650.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	guy3(gulagGuard, 1475.0f, 260.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	kazotsky(kKicker, 1075.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	kazotsky2(kKicker, 1150.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	boundary1(boundaryBox, 960.0f, 320.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary3(boundaryBox, 1570.0f, 330.0f, 800.0f, 48.0f, -173.0f, -48.0f, 0),
	boundary4(boundaryBox, 1610.0f, 280.0f, 120.0f, 48.0f, -143.0f, -48.0f, 0),
	boundary5(boundaryBox, 1670.0f, 245.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary6(boundaryBox, 1680.0f, 244.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary7(boundaryBox, 1705.0f, 174.0f, 42.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary8(boundaryBox, 1760.0f, 112.0f, 52.0f, 26.0f, -42.0f, -26.0f, 0),
	boundary9(boundaryBox, 1820.0f, 30.0f, 38.0f, 49.0f, -10.0f, -10.0f, 0),
	boundary10(boundaryBox, 1910.0f, 0.0f, 14.0f, 64.0f, 20.0f, -10.0f, 0)
{

}

void PrisonWalkway2::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		PrisonWalkway2::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/gulagpart2.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&guy2);
	CharacterCollisionList.push_back(&guy3);
	CharacterCollisionList.push_back(&grate);
	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&kazotsky2);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);
	CharacterCollisionList.push_back(&boundary4);
	CharacterCollisionList.push_back(&boundary5);
	CharacterCollisionList.push_back(&boundary6);
	CharacterCollisionList.push_back(&boundary7);
	CharacterCollisionList.push_back(&boundary8);
	CharacterCollisionList.push_back(&boundary9);
	CharacterCollisionList.push_back(&boundary10);

	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&guy2);
	CharacterSortVector.push_back(&guy3);
	CharacterSortVector.push_back(&grate);
	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&kazotsky2);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void PrisonWalkway2::exit()
{

	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		PrisonWalkway2::SetPaused(m_paused);
		Sewer(hasBeenInitialized);
		//Street(hasBeenInintialized);

		
		
		
		FzlDeleteSprite(background);

		FzlDeleteSprite(grate.getSpriteHandle());
	
	}
}
















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SEWER LEVEL 1































void Sewer::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;
	
	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&guy2);
	Mentlegen.Hurt(&unit1);
	Mentlegen.Hurt(&kazotsky);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}/*
	 for (auto itr = CharacterCollisionList.begin(), itrEnd = CharacterCollisionList.end(); itr != itrEnd; itr++)
	 {
	 (itr->updateBoundingBox());
	 }*/

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guy2.getAlive() == false)
	{
		beef.setPosition(guy2.getDeathPosition().getX(), guy2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);

	guy2.Move(&Mentlegen);
	guy2.Attack(&Mentlegen);
	guy2.Hurt(&Mentlegen);
	guy2.setGrunt(false);

	kazotsky.Move(&Mentlegen);
	kazotsky.Attack(&Mentlegen);
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	unit1.Move(&Mentlegen);
	unit1.Attack(&Mentlegen);
	unit1.Hurt(&Mentlegen);
	unit1.setGrunt(false);


	//Animations--------------------------------------------

	guy.Idle();
	guy2.Idle();
	unit1.Idle();

	guy.animation(frameCounter, &Mentlegen);
	guy2.animation(frameCounter, &Mentlegen);
	kazotsky.animation(frameCounter, &Mentlegen);
	unit1.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f) || 
				(Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) || 
				(Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Sewer::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		//FzlPlaySound(gulag);
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		//FzlPlaySound(gulag);
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		guy2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		//FzlPlaySound(gulag);
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		//FzlPlaySound(gulag);
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		unit1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() > 1900)
	{
		Sewer::exit();
		m_parent->GetGameState("Sewer2")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Sewer::Sewer() :
	Mentlegen(mentlegen, 100.0f, 250.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	box("../../../Assets/crate2.png", 300, 300, 500.0f, 75.0f, 52.0f, -1.0f, -52.0f, -68.0f, 2),
	vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	guy(gulagGuard, 1300.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	guy2(gulagGuard, 1200.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	kazotsky(kKicker, 1800.0f, 225.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	unit1(bSoldier, 1600.0f, 275.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
	boundary1(boundaryBox, 960.0f, 310.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary3(boundaryBox, 0.0f, 0.0f, 0.0f, 1080.0f, 0.0f, 0.0f, 0)
{

}

void Sewer::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Sewer::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/sewerlevelopening.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&guy2);
	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&unit1);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);

	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&guy2);
	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&unit1);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Sewer::exit()
{
	if (m_paused == false)
	{
		m_paused = true;
		Sewer::SetPaused(m_paused);
		Sewer2(hasBeenInintialized);

		
		
		
		FzlDeleteSprite(background);

		FzlDeleteSprite(box.getSpriteHandle());
		
	}
}























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SEWER LEVEL 2




























void Sewer2::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&unit1);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&kazotsky2);
	Mentlegen.Hurt(&kazotsky3);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}/*
	 for (auto itr = CharacterCollisionList.begin(), itrEnd = CharacterCollisionList.end(); itr != itrEnd; itr++)
	 {
	 (itr->updateBoundingBox());
	 }*/

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guy.getAlive() == false)
	{
		beef.setPosition(guy.getDeathPosition().getX(), guy.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);

	kazotsky.Move(&Mentlegen);
	kazotsky.Attack(&Mentlegen);
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	kazotsky2.Move(&Mentlegen);
	kazotsky2.Attack(&Mentlegen);
	kazotsky2.Hurt(&Mentlegen);
	kazotsky2.setGrunt(false);

	kazotsky3.Move(&Mentlegen);
	kazotsky3.Attack(&Mentlegen);
	kazotsky3.Hurt(&Mentlegen);
	kazotsky3.setGrunt(false);

	unit1.Move(&Mentlegen);
	unit1.Attack(&Mentlegen);
	unit1.Hurt(&Mentlegen);
	unit1.setGrunt(false);


	//Animations--------------------------------------------

	guy.Idle();
	unit1.Idle();

	guy.animation(frameCounter, &Mentlegen);
	kazotsky.animation(frameCounter, &Mentlegen);
	kazotsky2.animation(frameCounter, &Mentlegen);
	kazotsky3.animation(frameCounter, &Mentlegen);
	unit1.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky3.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Sewer2::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		//FzlPlaySound(gulag);
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		//FzlPlaySound(gulag);
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		kazotsky2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky3.getPosition()) < 100.0f))
	{
		kazotsky3.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky3.setGrunt(true);
		if (kazotsky3.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky3.getPosition()) < 100.0f))
	{
		kazotsky3.decrementHealth();
		kazotsky3.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky3.setGrunt(true);
		if (kazotsky3.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky3.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky3.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky3.setGrunt(true);
		if (kazotsky3.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		unit1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() > 1900)
	{
		Sewer2::exit();
		m_parent->GetGameState("Sewer3")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Sewer2::Sewer2() :
	Mentlegen(mentlegen, 100.0f, 250.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	box("../../../Assets/crate2.png", 300, 300, 500.0f, 100.0f, 52.0f, -1.0f, -52.0f, -68.0f, 2),
	guy(gulagGuard, 1600.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	kazotsky(kKicker, 1300.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	kazotsky2(kKicker, 1300.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	kazotsky3(kKicker, 1600.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	unit1(bSoldier, 1400.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
	vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	boundary1(boundaryBox, 960.0f, 310.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary3(boundaryBox, 0.0f, 0.0f, 0.0f, 1080.0f, 0.0f, 0.0f, 0)
{

}

void Sewer2::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Sewer2::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/sewerlevel.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&kazotsky2);
	CharacterCollisionList.push_back(&kazotsky3);
	CharacterCollisionList.push_back(&unit1);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);

	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&kazotsky2);
	CharacterSortVector.push_back(&kazotsky3);
	CharacterSortVector.push_back(&unit1);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Sewer2::exit()
{

	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		Sewer2::SetPaused(m_paused);
		Sewer3(hasBeenInintialized);

		
		
		
		FzlDeleteSprite(background);

		FzlDeleteSprite(box.getSpriteHandle());
		
	}
}
























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SEWER LEVEL 3




























void Sewer3::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&guy2);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&unit1);
	Mentlegen.Hurt(&unit2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}/*
	 for (auto itr = CharacterCollisionList.begin(), itrEnd = CharacterCollisionList.end(); itr != itrEnd; itr++)
	 {
	 (itr->updateBoundingBox());
	 }*/

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	MaxGentleman.draw();

	HealthBar.draw();

	//Beef

	if (guy2.getAlive() == false)
	{
		beef.setPosition(guy2.getDeathPosition().getX(), guy2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);

	guy2.Move(&Mentlegen);
	guy2.Attack(&Mentlegen);
	guy2.Hurt(&Mentlegen);
	guy2.setGrunt(false);

	kazotsky.Move(&Mentlegen);
	kazotsky.Attack(&Mentlegen);
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	unit1.Move(&Mentlegen);
	unit1.Attack(&Mentlegen);
	unit1.Hurt(&Mentlegen);
	unit1.setGrunt(false);

	unit2.Move(&Mentlegen);
	unit2.Attack(&Mentlegen);
	unit2.Hurt(&Mentlegen);
	unit2.setGrunt(false);

	//Animations--------------------------------------------

	guy.Idle();
	guy2.Idle();
	unit1.Idle();
	unit2.Idle();

	guy.animation(frameCounter, &Mentlegen);
	guy2.animation(frameCounter, &Mentlegen);
	kazotsky.animation(frameCounter, &Mentlegen);
	unit1.animation(frameCounter, &Mentlegen);
	unit2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Sewer3::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f))
	{
		guy2.decrementHealth();
		guy2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy2.setGrunt(true);
		if (guy2.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		unit1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f))
	{
		unit2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f))
	{
		unit2.decrementHealth();
		unit2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if ((Mentlegen.getPosition().getX() > 1600) &&
		(Mentlegen.getPosition().getX() < 1680) &&
		((Mentlegen.getPosition().getY() > 320) &&
		(Mentlegen.getPosition().getY() < 380)))
	{
		Sewer3::exit();
		m_parent->GetGameState("Street")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Sewer3::Sewer3() :
Mentlegen(mentlegen, 100.0f, 200.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
box("../../../Assets/crate2.png", 300, 300, 500.0f, 100.0f, 52.0f, -1.0f, -52.0f, -68.0f, 2),
ladder("../../../Assets/ladder.png", 178, 833, 1640.0f, 650.0f, 52.0f, -1.0f, -52.0f, -68.0f, 2),
guy(gulagGuard, 1400.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
guy2(gulagGuard, 1300.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
kazotsky(kKicker, 1550.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
unit1(bSoldier, 1700.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
unit2(bSoldier, 1600.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
boundary1(boundaryBox, 960.0f, 310.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary3(boundaryBox, 1560.0f, 260.0f, 0.0f, 42.0f, -10.0f, -42.0f, 0),
boundary4(boundaryBox, 1710.0f, 260.0f, 5.0f, 42.0f, -20.0f, -42.0f, 0),
boundary5(boundaryBox, 0.0f, 0.0f, 0.0f, 1080.0f, 0.0f, 0.0f, 0),
boundary6(boundaryBox, 1920.0f, 0.0f, 0.0f, 1080.0f, 0.0f, 0.0f, 0)
{
}

void Sewer3::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Sewer3::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/sewerlevelclosing.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&guy2);
	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&unit1);
	CharacterCollisionList.push_back(&unit2);
	CharacterCollisionList.push_back(&ladder);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);
	CharacterCollisionList.push_back(&boundary4);
	CharacterCollisionList.push_back(&boundary5);
	CharacterCollisionList.push_back(&boundary6);

	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&guy2);
	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&unit1);
	CharacterSortVector.push_back(&unit2);
	CharacterSortVector.push_back(&ladder);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Sewer3::exit()
{

	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		Sewer3::SetPaused(m_paused);
		Street(hasBeenInintialized);

		
		
		
		FzlDeleteSprite(background);

		FzlDeleteSprite(box.getSpriteHandle());
		FzlDeleteSprite(ladder.getSpriteHandle());
		
	}
}





















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//STREET STAGE 1



























void Street::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;
	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&unit1);
	Mentlegen.Hurt(&unit2);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&guard1);
	Mentlegen.Hurt(&guard2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	sewerHole.draw();

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guard2.getAlive() == false)
	{
		beef.setPosition(guard2.getDeathPosition().getX(), guard2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	kazotsky.Move(&Mentlegen);
	kazotsky.Attack(&Mentlegen);
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	unit1.Move(&Mentlegen);
	unit1.Attack(&Mentlegen);
	unit1.Hurt(&Mentlegen);
	unit1.setGrunt(false);

	unit2.Move(&Mentlegen);
	unit2.Attack(&Mentlegen);
	unit2.Hurt(&Mentlegen);
	unit2.setGrunt(false);

	guard1.Move(&Mentlegen);
	guard1.Attack(&Mentlegen);
	guard1.Hurt(&Mentlegen);
	guard1.setGrunt(false);

	guard2.Move(&Mentlegen);
	guard2.Attack(&Mentlegen);
	guard2.Hurt(&Mentlegen);
	guard2.setGrunt(false);

	box.Break(&Mentlegen);
	if (spacePressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	{
		box.decrementHealth();
		box.decrementHealth();
		box.decrementHealth();
		FzlPlaySound(crate);
	}
	if (cPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	{
		box.decrementHealth();
		box.decrementHealth();
		box.decrementHealth();
		FzlPlaySound(crate);
	}
	if (vPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			box.decrementHealth();
		}
		maxGentleman = 0;
		FzlPlaySound(crate);
	}

	//Animations--------------------------------------------

	unit1.Idle();
	unit2.Idle();
	guard1.Idle();
	guard2.Idle();

	kazotsky.animation(frameCounter, &Mentlegen);
	unit1.animation(frameCounter, &Mentlegen);
	unit2.animation(frameCounter, &Mentlegen);
	guard1.animation(frameCounter, &Mentlegen);
	guard2.animation(frameCounter, &Mentlegen);
	
	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) || 
				(Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Street::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		guard1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		guard2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		unit1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		FzlPlaySound(broviet);
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		FzlPlaySound(broviet);
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f))
	{
		unit2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f))
	{
		unit2.decrementHealth();
		unit2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		FzlPlaySound(broviet);
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		FzlPlaySound(broviet);
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() > 1900)
	{
		Street::exit();
		m_parent->GetGameState("Street2")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Street::Street() :
	Mentlegen(mentlegen, 220.0f, 370.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	sewerHole("../../../Assets/sewerthing.png", 218, 60, 240.0f, 250.0f, 55.0f, 25.0f, -85.0f, -25.0f, 0),
	box("../../../Assets/crate2.png", 300, 300, 500.0f, 100.0f, 52.0f, -1.0f, -52.0f, -68.0f, 2),
	LampPost("../../../Assets/lamppost.png", 45, 351, 100.0f, 500.0f, 5.0f, -130.0f, -5.0f, -160.0f, 0),
	Garbage("../../../Assets/dumpster.png", 180, 150, 1500.0f, 440.0f, 72.0f, -54.0f, -82.0f, -78.0f, 0),
	Barrel("../../../Assets/Barrel.png", 150, 150, 600.0f, 395.0f, 52.0f, -24.0f, -52.0f, -68.0f, 0),
	Barrel2("../../../Assets/Barrel.png", 150, 150, 830.0f, 395.0f, 52.0f, -24.0f, -52.0f, -68.0f, 0),
	Trash("../../../Assets/Trashcanclosed.png", 55, 75, 1700.0f, 390.0f, 19.0f, 5.0f, -19.0f, -70.0f, 0),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	guard1(eGuard, 1600.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
	guard2(eGuard, 1700.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
	unit1(bSoldier, 1200.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
	unit2(bSoldier, 1300.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
	kazotsky(kKicker, 1400.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	boundary1(boundaryBox, 960.0f, 410.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary3(boundaryBox, 0.0f, 0.0f, 0.0f, 1080.0f, 0.0f, 0.0f, 0)
{

}

void Street::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Street::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/streets_final.png", 1920, 1080);

	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&unit1);
	CharacterCollisionList.push_back(&unit2);
	CharacterCollisionList.push_back(&guard1);
	CharacterCollisionList.push_back(&guard2);
	CharacterCollisionList.push_back(&sewerHole);
	CharacterCollisionList.push_back(&box);
	CharacterCollisionList.push_back(&LampPost);
	CharacterCollisionList.push_back(&Garbage);
	CharacterCollisionList.push_back(&Barrel);
	CharacterCollisionList.push_back(&Barrel2);
	CharacterCollisionList.push_back(&Trash);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);

	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&unit1);
	CharacterSortVector.push_back(&unit2);
	CharacterSortVector.push_back(&guard1);
	CharacterSortVector.push_back(&guard2);
	CharacterSortVector.push_back(&box);
	CharacterSortVector.push_back(&LampPost);
	CharacterSortVector.push_back(&Garbage);
	CharacterSortVector.push_back(&Barrel);
	CharacterSortVector.push_back(&Barrel2);
	CharacterSortVector.push_back(&Trash);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Street::exit()
{
	if (m_paused == false)
	{
		m_paused = true;
		Street::SetPaused(m_paused);
		Street2(hasBeenInintialized);

		
		
		
		FzlDeleteSprite(background);

		FzlDeleteSprite(sewerHole.getSpriteHandle());
		FzlDeleteSprite(box.getSpriteHandle());
		FzlDeleteSprite(LampPost.getSpriteHandle());
		FzlDeleteSprite(Garbage.getSpriteHandle());
		FzlDeleteSprite(Barrel.getSpriteHandle());
		FzlDeleteSprite(Trash.getSpriteHandle());
		FzlDeleteSprite(Barrel2.getSpriteHandle());
		
	}
}





















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//STREET STAGE 2





























void Street2::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&kazotsky2);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&unit);
	Mentlegen.Hurt(&guard1);
	Mentlegen.Hurt(&guard2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guard2.getAlive() == false)
	{
		beef.setPosition(guard2.getDeathPosition().getX(), guard2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);

	kazotsky.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	kazotsky2.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky2.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky2.Hurt(&Mentlegen);
	kazotsky2.setGrunt(false);

	unit.Move(&Mentlegen);
	unit.Attack(&Mentlegen);
	unit.Hurt(&Mentlegen);
	unit.setGrunt(false);

	guard1.Move(&Mentlegen);
	guard1.Attack(&Mentlegen);
	guard1.Hurt(&Mentlegen);
	guard1.setGrunt(false);

	guard2.Move(&Mentlegen);
	guard2.Attack(&Mentlegen);
	guard2.Hurt(&Mentlegen);
	guard2.setGrunt(false);

	box.Break(&Mentlegen);
	box2.Break(&Mentlegen);
	box3.Break(&Mentlegen);
	box4.Break(&Mentlegen);
	if (spacePressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	{
		box.decrementHealth();
		box.decrementHealth();
		box.decrementHealth();
		FzlPlaySound(crate);
	}
	if (cPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	{
		box.decrementHealth();
		box.decrementHealth();
		box.decrementHealth();
		FzlPlaySound(crate);
	}
	if (vPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			box.decrementHealth();
		}
		maxGentleman = 0;
		FzlPlaySound(crate);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(box2.getPosition()) < 100.0f))
	{
		box2.decrementHealth();
		box2.decrementHealth();
		box2.decrementHealth();
		FzlPlaySound(crate);
	}
	if (cPressed && (Mentlegen.getPosition().distance(box2.getPosition()) < 100.0f))
	{
		box2.decrementHealth();
		box2.decrementHealth();
		box2.decrementHealth();
		FzlPlaySound(crate);
	}
	if (vPressed && (Mentlegen.getPosition().distance(box2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			box2.decrementHealth();
		}
		maxGentleman = 0;
		FzlPlaySound(crate);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(box3.getPosition()) < 100.0f))
	{
		box3.decrementHealth();
		box3.decrementHealth();
		box3.decrementHealth();
		FzlPlaySound(crate);
	}
	if (cPressed && (Mentlegen.getPosition().distance(box3.getPosition()) < 100.0f))
	{
		box3.decrementHealth();
		box3.decrementHealth();
		box3.decrementHealth();
		FzlPlaySound(crate);
	}
	if (vPressed && (Mentlegen.getPosition().distance(box3.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			box3.decrementHealth();
		}
		maxGentleman = 0;
		FzlPlaySound(crate);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(box4.getPosition()) < 100.0f))
	{
		box4.decrementHealth();
		box4.decrementHealth();
		box4.decrementHealth();
		FzlPlaySound(crate);
	}
	if (cPressed && (Mentlegen.getPosition().distance(box4.getPosition()) < 100.0f))
	{
		box4.decrementHealth();
		box4.decrementHealth();
		box4.decrementHealth();
		FzlPlaySound(crate);
	}
	if (vPressed && (Mentlegen.getPosition().distance(box4.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			box4.decrementHealth();
		}
		maxGentleman = 0;
		FzlPlaySound(crate);
	}

	//Animations--------------------------------------------

	guy.Idle();
	unit.Idle();
	guard1.Idle();
	guard2.Idle();

	guy.animation(frameCounter, &Mentlegen);
	kazotsky.animation(frameCounter, &Mentlegen);
	kazotsky2.animation(frameCounter, &Mentlegen);
	unit.animation(frameCounter, &Mentlegen);
	guard1.animation(frameCounter, &Mentlegen);
	guard2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Street2::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		guard1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	
	if (spacePressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		guard2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		unit.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		kazotsky2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() == 1900)
	{
		Street2::exit();
		//stage 3 here
		m_parent->GetGameState("Street3")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Street2::Street2() :
	Mentlegen(mentlegen, 100.0f, 200.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	box("../../../Assets/crate2.png", 300, 300, 800.0f, 400.0f, 52.0f, -1.0f, -52.0f, -68.0f, 2),
	box2("../../../Assets/crate2.png", 300, 300, 1000.0f, 400.0f, 52.0f, -1.0f, -52.0f, -68.0f, 2),
	box3("../../../Assets/crate2.png", 300, 300, 1200.0f, 400.0f, 52.0f, -1.0f, -52.0f, -68.0f, 2),
	box4("../../../Assets/crate2.png", 300, 300, 1400.0f, 400.0f, 52.0f, -1.0f, -52.0f, -68.0f, 2),
	LampPost("../../../Assets/lamppost.png", 45, 351, 1700.0f, 500.0f, 5.0f, -130.0f, -5.0f, -160.0f, 0),
	Barrel("../../../Assets/Barrel.png", 150, 150, 180.0f, 395.0f, 52.0f, -24.0f, -52.0f, -68.0f, 0),
	Barrel2("../../../Assets/Barrel.png", 150, 150, 280.0f, 395.0f, 52.0f, -24.0f, -52.0f, -68.0f, 0),
	Barrel3("../../../Assets/Barrel.png", 150, 150, 1770.0f, 110.0f, 52.0f, -24.0f, -52.0f, -68.0f, 0),
	Barrel4("../../../Assets/Barrel.png", 150, 150, 1670.0f, 250.0f, 52.0f, -24.0f, -52.0f, -68.0f, 0),
	Trash("../../../Assets/Trashcanclosed.png", 55, 75, 1750.0f, 370.0f, 19.0f, 5.0f, -19.0f, -70.0f, 0),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	unit(bSoldier, 1200.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
	guard1(eGuard, 1700.0f, 110.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
	guard2(eGuard, 1600.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
	kazotsky(kKicker, 1500.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	kazotsky2(kKicker, 1600.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	guy(gulagGuard, 1400.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	boundary1(boundaryBox, 960.0f, 410.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary3(boundaryBox, 0.0f, 0.0f, 0.0f, 1080.0f, 0.0f, 0.0f, 0)
{

}

void Street2::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Street2::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/streets_final.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&kazotsky2);
	CharacterCollisionList.push_back(&unit);
	CharacterCollisionList.push_back(&guard1);
	CharacterCollisionList.push_back(&guard2);
	CharacterCollisionList.push_back(&box);
	CharacterCollisionList.push_back(&box2);
	CharacterCollisionList.push_back(&box3);
	CharacterCollisionList.push_back(&box4);
	CharacterCollisionList.push_back(&LampPost);
	CharacterCollisionList.push_back(&Barrel);
	CharacterCollisionList.push_back(&Barrel2);
	CharacterCollisionList.push_back(&Barrel3);
	CharacterCollisionList.push_back(&Barrel4);
	CharacterCollisionList.push_back(&Trash);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);


	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&kazotsky2);
	CharacterSortVector.push_back(&unit);
	CharacterSortVector.push_back(&guard1);
	CharacterSortVector.push_back(&guard2);
	CharacterSortVector.push_back(&box);
	CharacterSortVector.push_back(&box2);
	CharacterSortVector.push_back(&box3);
	CharacterSortVector.push_back(&box4);
	CharacterSortVector.push_back(&LampPost);
	CharacterSortVector.push_back(&Barrel);
	CharacterSortVector.push_back(&Barrel2);
	CharacterSortVector.push_back(&Barrel3);
	CharacterSortVector.push_back(&Barrel4);
	CharacterSortVector.push_back(&Trash);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Street2::exit()
{

	hasBeenInitialized = false;

	m_paused = true;
	Street2::SetPaused(m_paused);
	Street3(hasBeenInitialized);

	FzlDeleteSprite(background);

	FzlDeleteSprite(box.getSpriteHandle());
	FzlDeleteSprite(box2.getSpriteHandle());
	FzlDeleteSprite(box3.getSpriteHandle());
	FzlDeleteSprite(box4.getSpriteHandle());
	FzlDeleteSprite(LampPost.getSpriteHandle());
	FzlDeleteSprite(Trash.getSpriteHandle());
	FzlDeleteSprite(Barrel.getSpriteHandle());
	FzlDeleteSprite(Barrel2.getSpriteHandle());
	FzlDeleteSprite(Barrel3.getSpriteHandle());
	FzlDeleteSprite(Barrel4.getSpriteHandle());
	
}






















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//STREET STAGE 3
































void Street3::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&kazotsky2);
	Mentlegen.Hurt(&unit);
	Mentlegen.Hurt(&guard1);
	Mentlegen.Hurt(&guard2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guard2.getAlive() == false)
	{
		beef.setPosition(guard2.getDeathPosition().getX(), guard2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	kazotsky.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	kazotsky2.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky2.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky2.Hurt(&Mentlegen);
	kazotsky2.setGrunt(false);

	unit.Move(&Mentlegen);
	unit.Attack(&Mentlegen);
	unit.Hurt(&Mentlegen);
	unit.setGrunt(false);

	guard1.Move(&Mentlegen);
	guard1.Attack(&Mentlegen);
	guard1.Hurt(&Mentlegen);
	guard1.setGrunt(false);

	guard2.Move(&Mentlegen);
	guard2.Attack(&Mentlegen);
	guard2.Hurt(&Mentlegen);
	guard2.setGrunt(false);

	//Animations--------------------------------------------

	unit.Idle();
	guard1.Idle();
	guard2.Idle();

	kazotsky.animation(frameCounter, &Mentlegen);
	kazotsky2.animation(frameCounter, &Mentlegen);
	unit.animation(frameCounter, &Mentlegen);
	guard1.animation(frameCounter, &Mentlegen);
	guard2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Street3::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		guard1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		guard2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		unit.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		kazotsky2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if ((Mentlegen.getPosition().getX() == 1660) &&
		(Mentlegen.getPosition().getY() > 20) &&
		(Mentlegen.getPosition().getY() < 200))
	{
		Street3::exit();
		m_parent->GetGameState("Embassy")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Street3::Street3() :
	Mentlegen(mentlegen, 200.0f, 150.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	entrance("../../../Assets/embassyentrance.png", 618, 1082, 1630.0f, -10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	LampPost("../../../Assets/lamppost.png", 45, 351, 100.0f, 500.0f, 5.0f, -130.0f, -5.0f, -160.0f, 0),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	guard1(eGuard, 1570.0f, 75.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
	guard2(eGuard, 1650.0f, 280.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
	unit(bSoldier, 1200.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
	kazotsky(kKicker, 1500.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	kazotsky2(kKicker, 1600.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	boundary1(boundaryBox, 960.0f, 360.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary3(boundaryBox, 960.0f, 300.0f, 550.0f, 50.0f, -500.0f, 0.0f, 0),
	boundary4(boundaryBox, 0.0f, 0.0f, 0.0f, 1080.0f, 0.0f, 0.0f, 0),
	boundary5(boundaryBox, 1900.0f, 0.0f, 0.0f, 1080.0f, 0.0f, 0.0f, 0),
	boundary6(boundaryBox, 1700.0f, 250.0f, 100.0f, 10.0f, -30.0f, -10.0f, 0)
{

}

void Street3::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Street3::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/street3.png", 1920, 1080);

	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&kazotsky2);
	CharacterCollisionList.push_back(&unit);
	CharacterCollisionList.push_back(&guard1);
	CharacterCollisionList.push_back(&guard2);
	CharacterCollisionList.push_back(&entrance);
	CharacterCollisionList.push_back(&LampPost);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);
	CharacterCollisionList.push_back(&boundary4);
	CharacterCollisionList.push_back(&boundary5);
	CharacterCollisionList.push_back(&boundary6);

	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&kazotsky2);
	CharacterSortVector.push_back(&unit);
	CharacterSortVector.push_back(&guard1);
	CharacterSortVector.push_back(&guard2);
	CharacterSortVector.push_back(&entrance);
	CharacterSortVector.push_back(&LampPost);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Street3::exit()
{

	hasBeenInitialized = false;

	if (m_paused == false)
	{

		m_paused = true;
		Street3::SetPaused(m_paused);
		EmbassyLevel(hasBeenInitialized);

		FzlDeleteSprite(background);

		FzlDeleteSprite(entrance.getSpriteHandle());
		FzlDeleteSprite(LampPost.getSpriteHandle());

	}
}























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EMBASSY STAGE 1






























void EmbassyLevel::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&kazotsky2);
	Mentlegen.Hurt(&unit);
	Mentlegen.Hurt(&guard1);
	Mentlegen.Hurt(&guard2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guard2.getAlive() == false)
	{
		beef.setPosition(guard2.getDeathPosition().getX(), guard2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	kazotsky.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	kazotsky2.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky2.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky2.Hurt(&Mentlegen);
	kazotsky2.setGrunt(false);

	unit.Move(&Mentlegen);
	unit.Attack(&Mentlegen);
	unit.Hurt(&Mentlegen);
	unit.setGrunt(false);

	guard1.Move(&Mentlegen);
	guard1.Attack(&Mentlegen);
	guard1.Hurt(&Mentlegen);
	guard1.setGrunt(false);

	guard2.Move(&Mentlegen);
	guard2.Attack(&Mentlegen);
	guard2.Hurt(&Mentlegen);
	guard2.setGrunt(false);

	//box.Break(&Mentlegen);
	//if (spacePressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	//{
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	FzlPlaySound(crate);
	//}
	//if (cPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	//{
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	FzlPlaySound(crate);
	//}
	//if (vPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f) && superPunch == true)
	//{
	//	for (int i = 0; i < 99; i++)
	//	{
	//		box.decrementHealth();
	//	}
	//	maxGentleman = 0;
	//	FzlPlaySound(crate);
	//}

	//Animations--------------------------------------------

	unit.Idle();
	guard1.Idle();
	guard2.Idle();

	kazotsky.animation(frameCounter, &Mentlegen);
	kazotsky2.animation(frameCounter, &Mentlegen);
	unit.animation(frameCounter, &Mentlegen);
	guard1.animation(frameCounter, &Mentlegen);
	guard2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		EmbassyLevel::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		guard1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		guard2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		unit.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		kazotsky2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() == 1900)
	{
		EmbassyLevel::exit();
		m_parent->GetGameState("Embassy2")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

EmbassyLevel::EmbassyLevel() :
	Mentlegen(mentlegen, 150.0f, 200.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	//box(),
	kazotsky(kKicker, 1400.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	kazotsky2(kKicker, 1500.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	guard1(eGuard, 1600.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
	guard2(eGuard, 1800.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
	unit(bSoldier, 1300.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
	vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	boundary1(boundaryBox, 960.0f, 290.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary3(boundaryBox, 115.0f, 263.0f, 100.0f, 88.0f, -173.0f, -48.0f, 0),
	boundary4(boundaryBox, 140.0f, 280.0f, 100.0f, 88.0f, -173.0f, -48.0f, 0),
	boundary5(boundaryBox, 180.0f, 300.0f, 100.0f, 88.0f, -173.0f, -48.0f, 0),
	boundary6(boundaryBox, 20.0f, 80.0f, 42.0f, 136.0f, -32.0f, -46.0f, 0),
	boundary7(boundaryBox, 0.0f, 20.0f, 32.0f, 46.0f, -32.0f, -46.0f, 0)
{

}

void EmbassyLevel::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		EmbassyLevel::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/landingPad.png", 1920, 1080);

	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&kazotsky2);
	CharacterCollisionList.push_back(&unit);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);
	CharacterCollisionList.push_back(&boundary4);
	CharacterCollisionList.push_back(&boundary5);
	CharacterCollisionList.push_back(&boundary6);
	CharacterCollisionList.push_back(&boundary7);
	CharacterCollisionList.push_back(&guard1);
	CharacterCollisionList.push_back(&guard2);
	//CharacterCollisionList.push_back(&box);

	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&kazotsky2);
	CharacterSortVector.push_back(&unit);
	CharacterSortVector.push_back(&guard1);
	CharacterSortVector.push_back(&guard2);
	//CharacterSortVector.push_back(&box);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void EmbassyLevel::exit()
{
	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		EmbassyLevel::SetPaused(m_paused);

		FzlDeleteSprite(background);

	}
}





























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EMBASSY STAGE 2
































void Embassy2::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&kazotsky2);
	Mentlegen.Hurt(&unit);
	Mentlegen.Hurt(&guard1);
	Mentlegen.Hurt(&pilot1);
	Mentlegen.Hurt(&pilot2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guard1.getAlive() == false)
	{
		beef.setPosition(guard1.getDeathPosition().getX(), guard1.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (pilot2.getAlive() == false)
	{
		vodkaBottle.setPosition(pilot2.getDeathPosition().getX(), pilot2.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	kazotsky.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	kazotsky2.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky2.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky2.Hurt(&Mentlegen);
	kazotsky2.setGrunt(false);

	unit.Move(&Mentlegen);
	unit.Attack(&Mentlegen);
	unit.Hurt(&Mentlegen);
	unit.setGrunt(false);

	guard1.Move(&Mentlegen);
	guard1.Attack(&Mentlegen);
	guard1.Hurt(&Mentlegen);
	guard1.setGrunt(false);

	pilot1.Move(&Mentlegen);
	pilot1.Attack(&Mentlegen);
	pilot1.Hurt(&Mentlegen);
	pilot1.setGrunt(false);

	pilot2.Move(&Mentlegen);
	pilot2.Attack(&Mentlegen);
	pilot2.Hurt(&Mentlegen);
	pilot2.setGrunt(false);

	//box.Break(&Mentlegen);
	//if (spacePressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	//{
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	FzlPlaySound(crate);
	//}
	//if (cPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	//{
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	FzlPlaySound(crate);
	//}
	//if (vPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f) && superPunch == true)
	//{
	//	for (int i = 0; i < 99; i++)
	//	{
	//		box.decrementHealth();
	//	}
	//	maxGentleman = 0;
	//	FzlPlaySound(crate);
	//}

	//Animations--------------------------------------------

	unit.Idle();
	guard1.Idle();
	pilot1.Idle();
	pilot2.Idle();

	kazotsky.animation(frameCounter, &Mentlegen);
	kazotsky2.animation(frameCounter, &Mentlegen);
	unit.animation(frameCounter, &Mentlegen);
	guard1.animation(frameCounter, &Mentlegen);
	pilot1.animation(frameCounter, &Mentlegen);
	pilot2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Embassy2::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f))
	{
		pilot1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f))
	{
		pilot1.decrementHealth();
		pilot1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			pilot1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f))
	{
		pilot2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f))
	{
		pilot2.decrementHealth();
		pilot2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			pilot2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		guard1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		unit.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		kazotsky2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() == 1900)
	{
		Embassy2::exit();
		m_parent->GetGameState("Embassy3")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Embassy2::Embassy2() :
Mentlegen(mentlegen, 200.0f, 150.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
//box(),
kazotsky(kKicker, 1400.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
kazotsky2(kKicker, 1500.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
guard1(eGuard, 1200.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
pilot1(pilotGuy, 1700.0f, 100.0f, 26.0f, -64.0f, -24.0f, -72.0f, 10),
pilot2(pilotGuy, 1800.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 10),
unit(bSoldier, 1200.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
boundary1(boundaryBox, 960.0f, 300.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary3(boundaryBox, 5.0f, 300.0f, 20.0f, 88.0f, -173.0f, -48.0f, 0),
boundary4(boundaryBox, 1915.0f, 300.0f, 100.0f, 88.0f, -100.0f, -48.0f, 0),
boundary5(boundaryBox, 960.0f, 300.0f, 100.0f, 88.0f, -155.0f, -48.0f, 0)
{

}

void Embassy2::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Embassy2::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/embassy1.png", 1920, 1080);

	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&kazotsky2);
	CharacterCollisionList.push_back(&unit);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);
	CharacterCollisionList.push_back(&boundary4);
	CharacterCollisionList.push_back(&boundary5);
	CharacterCollisionList.push_back(&guard1);
	CharacterCollisionList.push_back(&pilot1);
	CharacterCollisionList.push_back(&pilot2);
	//CharacterCollisionList.push_back(&box);

	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&kazotsky2);
	CharacterSortVector.push_back(&unit);
	CharacterSortVector.push_back(&guard1);
	CharacterSortVector.push_back(&pilot1);
	CharacterSortVector.push_back(&pilot2);
	//CharacterSortVector.push_back(&box);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Embassy2::exit()
{
	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		Embassy2::SetPaused(m_paused);

		FzlDeleteSprite(background);

	}
}

























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EMBASSY STAGE 3































void Embassy3::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&kazotsky2);
	Mentlegen.Hurt(&unit);
	Mentlegen.Hurt(&guard1);
	Mentlegen.Hurt(&guard2);
	Mentlegen.Hurt(&pilot1);
	Mentlegen.Hurt(&pilot2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	HealthBar.draw();

	ramp.draw();

	MaxGentleman.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guard2.getAlive() == false)
	{
		beef.setPosition(guard2.getDeathPosition().getX(), guard2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (pilot2.getAlive() == false)
	{
		vodkaBottle.setPosition(pilot2.getDeathPosition().getX(), pilot2.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	kazotsky.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	kazotsky2.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky2.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky2.Hurt(&Mentlegen);
	kazotsky2.setGrunt(false);

	unit.Move(&Mentlegen);
	unit.Attack(&Mentlegen);
	unit.Hurt(&Mentlegen);
	unit.setGrunt(false);

	guard1.Move(&Mentlegen);
	guard1.Attack(&Mentlegen);
	guard1.Hurt(&Mentlegen);
	guard1.setGrunt(false);

	guard2.Move(&Mentlegen);
	guard2.Attack(&Mentlegen);
	guard2.Hurt(&Mentlegen);
	guard2.setGrunt(false);

	pilot1.Move(&Mentlegen);
	pilot1.Attack(&Mentlegen);
	pilot1.Hurt(&Mentlegen);
	pilot1.setGrunt(false);
	  
	pilot2.Move(&Mentlegen);
	pilot2.Attack(&Mentlegen);
	pilot2.Hurt(&Mentlegen);
	pilot2.setGrunt(false);

	//box.Break(&Mentlegen);
	//if (spacePressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	//{
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	FzlPlaySound(crate);
	//}
	//if (cPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	//{
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	FzlPlaySound(crate);
	//}
	//if (vPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f) && superPunch == true)
	//{
	//	for (int i = 0; i < 99; i++)
	//	{
	//		box.decrementHealth();
	//	}
	//	maxGentleman = 0;
	//	FzlPlaySound(crate);
	//}

	//Animations--------------------------------------------

	unit.Idle();
	guard1.Idle();
	guard2.Idle();
	pilot1.Idle();
	pilot2.Idle();

	kazotsky.animation(frameCounter, &Mentlegen);
	kazotsky2.animation(frameCounter, &Mentlegen);
	unit.animation(frameCounter, &Mentlegen);
	guard1.animation(frameCounter, &Mentlegen);
	guard2.animation(frameCounter, &Mentlegen);
	pilot1.animation(frameCounter, &Mentlegen);
	pilot2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Embassy3::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f))
	{
		pilot1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f))
	{
		pilot1.decrementHealth();
		pilot1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			pilot1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f))
	{
		pilot2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f))
	{
		pilot2.decrementHealth();
		pilot2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			pilot2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		guard1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		guard2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		unit.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		kazotsky2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if ((Mentlegen.getPosition().getX() == 1250) &&
		(Mentlegen.getPosition().getY() < 210) &&
		(Mentlegen.getPosition().getY() > 100))
	{
		Embassy3::exit();
		m_parent->GetGameState("Plane")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Embassy3::Embassy3() :
Mentlegen(mentlegen, 100.0f, 200.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
ramp("../../../Assets/ship.png", 864, 1003, 1550.0f, 450.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
kazotsky(kKicker, 1100.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
kazotsky2(kKicker, 1200.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
guard1(eGuard, 1100.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
guard2(eGuard, 1200.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
pilot1(pilotGuy, 1500.0f, 320.0f, 26.0f, -64.0f, -24.0f, -72.0f, 10),
pilot2(pilotGuy, 1500.0f, 70.0f, 26.0f, -64.0f, -24.0f, -72.0f, 10),
unit(bSoldier, 900.0f, 150.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
boundary1(boundaryBox, 960.0f, 320.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary2(boundaryBox, 960.0f, 0.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary3(boundaryBox, 1600.0f, 100.0f, 200.0f, 2000.0f, -300.0f, -200.0f, 0)
{

}

void Embassy3::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Embassy3::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/embassy1.png", 1920, 1080);

	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&kazotsky2);
	CharacterCollisionList.push_back(&unit);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);
	CharacterCollisionList.push_back(&guard1);
	CharacterCollisionList.push_back(&guard2);
	CharacterCollisionList.push_back(&pilot1);
	CharacterCollisionList.push_back(&pilot2);
	//CharacterCollisionList.push_back(&ramp);

	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&kazotsky2);
	CharacterSortVector.push_back(&unit);
	CharacterSortVector.push_back(&guard1);
	CharacterSortVector.push_back(&guard2);
	CharacterSortVector.push_back(&pilot1);
	CharacterSortVector.push_back(&pilot2);
	//CharacterSortVector.push_back(&ramp);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Embassy3::exit()
{
	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		Embassy3::SetPaused(m_paused);

		FzlDeleteSprite(background);

	}
}























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PLANE STAGE 1




























void Plane::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&unit1);
	Mentlegen.Hurt(&unit2);
	Mentlegen.Hurt(&guard1);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guy.getAlive() == false)
	{
		beef.setPosition(guy.getDeathPosition().getX(), guy.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (kazotsky.getAlive() == false)
	{
		vodkaBottle.setPosition(kazotsky.getDeathPosition().getX(), kazotsky.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	kazotsky.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);

	unit1.Move(&Mentlegen);
	unit1.Attack(&Mentlegen);
	unit1.Hurt(&Mentlegen);
	unit1.setGrunt(false);

	unit2.Move(&Mentlegen);
	unit2.Attack(&Mentlegen);
	unit2.Hurt(&Mentlegen);
	unit2.setGrunt(false);

	guard1.Move(&Mentlegen);
	guard1.Attack(&Mentlegen);
	guard1.Hurt(&Mentlegen);
	guard1.setGrunt(false);

	//box.Break(&Mentlegen);
	//if (spacePressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	//{
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	FzlPlaySound(crate);
	//}
	//if (cPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f))
	//{
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	box.decrementHealth();
	//	FzlPlaySound(crate);
	//}
	//if (vPressed && (Mentlegen.getPosition().distance(box.getPosition()) < 100.0f) && superPunch == true)
	//{
	//	for (int i = 0; i < 99; i++)
	//	{
	//		box.decrementHealth();
	//	}
	//	maxGentleman = 0;
	//	FzlPlaySound(crate);
	//}

	//Animations--------------------------------------------

	guy.Idle();
	unit1.Idle();
	unit2.Idle();
	guard1.Idle();

	guy.animation(frameCounter, &Mentlegen);
	kazotsky.animation(frameCounter, &Mentlegen);
	unit1.animation(frameCounter, &Mentlegen);
	unit2.animation(frameCounter, &Mentlegen);
	guard1.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Plane::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		guard1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		unit1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f))
	{
		unit2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f))
	{
		unit2.decrementHealth();
		unit2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() == 1900)
	{
		Plane::exit();
		m_parent->GetGameState("Plane2")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Plane::Plane() :
	Mentlegen(mentlegen, 100.0f, 300.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
	MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	//box(),
	guy(gulagGuard, 1200.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
	kazotsky(kKicker, 1500.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
	guard1(eGuard, 1750.0f, 350.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
	unit1(bSoldier, 1550.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
	unit2(bSoldier, 1650.0f, 250.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
	vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
	boundary1(boundaryBox, 960.0f, 380.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
	boundary2(boundaryBox, 960.0f, 120.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0)
{

}

void Plane::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Plane::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/plane.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&unit1);
	CharacterCollisionList.push_back(&unit2);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&guard1);
	//CharacterCollisionList.push_back(&box);

	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&unit1);
	CharacterSortVector.push_back(&unit2);
	CharacterSortVector.push_back(&guard1);
	//CharacterSortVector.push_back(&box);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Plane::exit()
{
	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		Plane::SetPaused(m_paused);

		FzlDeleteSprite(background);

	}
}
























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PLANE STAGE 2




























void Plane2::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&kazotsky2);
	Mentlegen.Hurt(&kazotsky3);
	Mentlegen.Hurt(&unit);
	Mentlegen.Hurt(&guard1);
	Mentlegen.Hurt(&guard2);
	Mentlegen.Hurt(&pilot1);
	Mentlegen.Hurt(&pilot2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guard2.getAlive() == false)
	{
		beef.setPosition(guard2.getDeathPosition().getX(), guard2.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (pilot1.getAlive() == false)
	{
		vodkaBottle.setPosition(pilot1.getDeathPosition().getX(), pilot1.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	kazotsky.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	kazotsky2.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky2.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky2.Hurt(&Mentlegen);
	kazotsky2.setGrunt(false);

	kazotsky3.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky3.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky3.Hurt(&Mentlegen);
	kazotsky3.setGrunt(false);

	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);

	unit.Move(&Mentlegen);
	unit.Attack(&Mentlegen);
	unit.Hurt(&Mentlegen);
	unit.setGrunt(false);

	guard1.Move(&Mentlegen);
	guard1.Attack(&Mentlegen);
	guard1.Hurt(&Mentlegen);
	guard1.setGrunt(false);

	guard2.Move(&Mentlegen);
	guard2.Attack(&Mentlegen);
	guard2.Hurt(&Mentlegen);
	guard2.setGrunt(false);

	pilot1.Move(&Mentlegen);
	pilot1.Attack(&Mentlegen);
	pilot1.Hurt(&Mentlegen);
	pilot1.setGrunt(false);

	pilot2.Move(&Mentlegen);
	pilot2.Attack(&Mentlegen);
	pilot2.Hurt(&Mentlegen);
	pilot2.setGrunt(false);

	//Animations--------------------------------------------

	guy.Idle();
	unit.Idle();
	guard1.Idle();
	guard2.Idle();
	pilot1.Idle();
	pilot2.Idle();

	guy.animation(frameCounter, &Mentlegen);
	kazotsky.animation(frameCounter, &Mentlegen);
	kazotsky2.animation(frameCounter, &Mentlegen);
	kazotsky3.animation(frameCounter, &Mentlegen);
	unit.animation(frameCounter, &Mentlegen);
	guard1.animation(frameCounter, &Mentlegen);
	guard2.animation(frameCounter, &Mentlegen);
	pilot1.animation(frameCounter, &Mentlegen);
	pilot2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(kazotsky3.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) || 
				(Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f) || 
				(Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f) || 
				(Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Plane2::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		guard1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		guard2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f))
	{
		pilot1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f))
	{
		pilot1.decrementHealth();
		pilot1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			pilot1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f))
	{
		pilot2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f))
	{
		pilot2.decrementHealth();
		pilot2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			pilot2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f))
	{
		unit.decrementHealth();
		unit.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit.setGrunt(true);
		if (unit.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f))
	{
		kazotsky2.decrementHealth();
		kazotsky2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky2.setGrunt(true);
		if (kazotsky2.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky3.getPosition()) < 100.0f))
	{
		kazotsky3.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky3.setGrunt(true);
		if (kazotsky3.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky3.getPosition()) < 100.0f))
	{
		kazotsky3.decrementHealth();
		kazotsky3.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky3.setGrunt(true);
		if (kazotsky3.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky3.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky3.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky3.setGrunt(true);
		if (kazotsky3.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() == 1900)
	{
		Plane2::exit();
		m_parent->GetGameState("Plane3")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Plane2::Plane2() :
Mentlegen(mentlegen, 100.0f, 290.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
//box(),
guy(gulagGuard, 1130.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
kazotsky(kKicker, 1500.0f, 350.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
kazotsky2(kKicker, 1650.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
kazotsky3(kKicker, 1700.0f, 325.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
guard1(eGuard, 1600.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
guard2(eGuard, 1700.0f, 380.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
pilot1(pilotGuy, 1850.0f, 380.0f, 26.0f, -64.0f, -24.0f, -72.0f, 10),
pilot2(pilotGuy, 1750.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 10),
unit(bSoldier, 1280.0f, 380.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
boundary1(boundaryBox, 960.0f, 380.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary2(boundaryBox, 960.0f, 120.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0)
{

}

void Plane2::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Plane2::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/plane.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&kazotsky2);
	CharacterCollisionList.push_back(&kazotsky3);
	CharacterCollisionList.push_back(&unit);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&guard1);
	CharacterCollisionList.push_back(&guard2);
	CharacterCollisionList.push_back(&pilot1);
	CharacterCollisionList.push_back(&pilot2);
	//CharacterCollisionList.push_back(&box);

	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&kazotsky2);
	CharacterSortVector.push_back(&kazotsky3);
	CharacterSortVector.push_back(&unit);
	CharacterSortVector.push_back(&guard1);
	CharacterSortVector.push_back(&guard2);
	CharacterSortVector.push_back(&pilot1);
	CharacterSortVector.push_back(&pilot2);
	//CharacterSortVector.push_back(&box);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Plane2::exit()
{
	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		Plane2::SetPaused(m_paused);

		FzlDeleteSprite(background);

	}
}

























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PLANE STAGE 3
































void Plane3::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);
	Mentlegen.Hurt(&kazotsky);
	Mentlegen.Hurt(&guy);
	Mentlegen.Hurt(&unit1);
	Mentlegen.Hurt(&unit2);
	Mentlegen.Hurt(&guard1);
	Mentlegen.Hurt(&guard2);
	Mentlegen.Hurt(&pilot1);
	Mentlegen.Hurt(&pilot2);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Beef

	if (guard1.getAlive() == false)
	{
		beef.setPosition(guard1.getDeathPosition().getX(), guard1.getDeathPosition().getY());
	}
	if (beef.getPosition().distance(Mentlegen.getPosition()) < 40.0f)
	{
		beef.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
		}
	}

	//Vodka

	if (pilot1.getAlive() == false)
	{
		vodkaBottle.setPosition(pilot1.getDeathPosition().getX(), pilot1.getDeathPosition().getY());
	}
	if (vodkaBottle.getPosition().distance(Mentlegen.getPosition()) < 30.0f)
	{
		vodkaBottle.kill();
		FzlPlaySound(gulp);
		if (Mentlegen.getHealth() == 1)
		{
			Mentlegen.incrementHealth();
		}
		else if (Mentlegen.getHealth() == 0)
		{
			Mentlegen.incrementHealth();
			Mentlegen.incrementHealth();
		}
	}

	//Enemy Moving and attacking------------------------------
	kazotsky.Move(&Mentlegen);   //Moves AND Attacks simulteanousely
	kazotsky.Attack(&Mentlegen); //Moves AND Attacks simultaneousely
	kazotsky.Hurt(&Mentlegen);
	kazotsky.setGrunt(false);

	guy.Move(&Mentlegen);
	guy.Attack(&Mentlegen);
	guy.Hurt(&Mentlegen);
	guy.setGrunt(false);

	unit1.Move(&Mentlegen);
	unit1.Attack(&Mentlegen);
	unit1.Hurt(&Mentlegen);
	unit1.setGrunt(false);

	unit2.Move(&Mentlegen);
	unit2.Attack(&Mentlegen);
	unit2.Hurt(&Mentlegen);
	unit2.setGrunt(false);

	pilot1.Move(&Mentlegen);
	pilot1.Attack(&Mentlegen);
	pilot1.Hurt(&Mentlegen);
	pilot1.setGrunt(false);

	pilot2.Move(&Mentlegen);
	pilot2.Attack(&Mentlegen);
	pilot2.Hurt(&Mentlegen);
	pilot2.setGrunt(false);

	guard1.Move(&Mentlegen);
	guard1.Attack(&Mentlegen);
	guard1.Hurt(&Mentlegen);
	guard1.setGrunt(false);

	guard2.Move(&Mentlegen);
	guard2.Attack(&Mentlegen);
	guard2.Hurt(&Mentlegen);
	guard2.setGrunt(false);

	//Animations--------------------------------------------

	guy.Idle();
	unit1.Idle();
	unit2.Idle();
	guard1.Idle();
	guard2.Idle();
	pilot1.Idle();
	pilot2.Idle();

	guy.animation(frameCounter, &Mentlegen);
	kazotsky.animation(frameCounter, &Mentlegen);
	unit1.animation(frameCounter, &Mentlegen);
	guard1.animation(frameCounter, &Mentlegen);
	guard2.animation(frameCounter, &Mentlegen);
	unit2.animation(frameCounter, &Mentlegen);
	pilot1.animation(frameCounter, &Mentlegen);
	pilot2.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) ||
				(Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Plane3::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f))
	{
		pilot1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f))
	{
		pilot1.decrementHealth();
		pilot1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(pilot1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			pilot1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		pilot1.setGrunt(true);
		if (pilot1.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f))
	{
		pilot2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f))
	{
		pilot2.decrementHealth();
		pilot2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(pilot2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			pilot2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		pilot2.setGrunt(true);
		if (pilot2.getGrunt() == true)
		{
			FzlPlaySound(pilot);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f))
	{
		guard1.decrementHealth();
		guard1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard1.setGrunt(true);
		if (guard1.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f))
	{
		guard2.decrementHealth();
		guard2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guard2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guard2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guard2.setGrunt(true);
		if (guard2.getGrunt() == true)
		{
			FzlPlaySound(embassy);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f))
	{
		guy.decrementHealth();
		guy.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(guy.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			guy.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		guy.setGrunt(true);
		if (guy.getGrunt() == true)
		{
			FzlPlaySound(gulag);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f))
	{
		unit1.decrementHealth();
		unit1.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit1.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit1.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit1.setGrunt(true);
		if (unit1.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f))
	{
		unit2.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f))
	{
		unit2.decrementHealth();
		unit2.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(unit2.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			unit2.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		unit2.setGrunt(true);
		if (unit2.getGrunt() == true)
		{
			FzlPlaySound(broviet);
		}
	}

	if (spacePressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f))
	{
		kazotsky.decrementHealth();
		kazotsky.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(kazotsky.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 99; i++)
		{
			kazotsky.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		kazotsky.setGrunt(true);
		if (kazotsky.getGrunt() == true)
		{
			FzlPlaySound(kicker);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}

	if (Mentlegen.getPosition().getX() == 1900)
	{
		Plane3::exit();
		m_parent->GetGameState("Final")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Plane3::Plane3() :
Mentlegen(mentlegen, 100.0f, 290.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
//box(),
guy(gulagGuard, 1130.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 2),
kazotsky(kKicker, 1500.0f, 350.0f, 26.0f, -64.0f, -24.0f, -72.0f, 4),
guard1(eGuard, 1700.0f, 350.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
guard2(eGuard, 1600.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 8),
pilot1(pilotGuy, 1800.0f, 350.0f, 26.0f, -64.0f, -24.0f, -72.0f, 10),
pilot2(pilotGuy, 1700.0f, 200.0f, 26.0f, -64.0f, -24.0f, -72.0f, 10),
unit1(bSoldier, 1280.0f, 400.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
unit2(bSoldier, 1440.0f, 400.0f, 26.0f, -64.0f, -24.0f, -72.0f, 6),
vodkaBottle(vodka, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
beef(gotBeef, 2000.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
boundary1(boundaryBox, 960.0f, 380.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary2(boundaryBox, 960.0f, 120.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0)
{

}

void Plane3::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Plane3::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/plane.png", 1920, 1080);

	CharacterCollisionList.push_back(&guy);
	CharacterCollisionList.push_back(&kazotsky);
	CharacterCollisionList.push_back(&unit1);
	CharacterCollisionList.push_back(&unit2);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&guard1);
	CharacterCollisionList.push_back(&guard2);
	CharacterCollisionList.push_back(&pilot1);
	CharacterCollisionList.push_back(&pilot2);
	//CharacterCollisionList.push_back(&box);

	CharacterSortVector.push_back(&guy);
	CharacterSortVector.push_back(&kazotsky);
	CharacterSortVector.push_back(&unit1);
	CharacterSortVector.push_back(&unit2);
	CharacterSortVector.push_back(&guard1);
	CharacterSortVector.push_back(&guard2);
	CharacterSortVector.push_back(&pilot1);
	CharacterSortVector.push_back(&pilot2);
	CharacterSortVector.push_back(&beef);
	CharacterSortVector.push_back(&vodkaBottle);
}

void Plane3::exit()
{
	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		Plane3::SetPaused(m_paused);

		FzlDeleteSprite(background);

	}
}


























//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FINAL STAGE: BROSEFF BALLIN
































void Final::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}
	Mentlegen.setHealth(currentHealth);
	frameCounter++;

	sort(CharacterMap, CharacterSortVector, &Mentlegen);

	bool spacePressed = FzlGetKey(FzlKeySpace) && !spaceWasPressed;

	if (FzlGetKey(FzlKeySpace))
		spaceWasPressed = true;
	else
		spaceWasPressed = false;

	bool cPressed = FzlGetKey(FzlKeyC) && !cWasPressed;

	if (FzlGetKey(FzlKeyC))
		cWasPressed = true;
	else
		cWasPressed = false;

	bool vPressed = FzlGetKey(FzlKeyV) && !vWasPressed;

	if (FzlGetKey(FzlKeyV)) //&&superPunch=true;
		vWasPressed = true;
	else
		vWasPressed = false;

	bool shiftPressed = FzlGetKey(FzlKeyLeftShift) && !shiftWasPressed;

	if (FzlGetKey(FzlKeyLeftShift)) //&&superPunch=true;
		shiftWasPressed = true;
	else
		shiftWasPressed = false;

	frameCounter++;

	FzlSetFrameRate(30);

	Mentlegen.Move(shiftPressed);

	for (int i = 0; i < CharacterCollisionList.size(); i++)
	{
		Mentlegen.Colliding(*(CharacterCollisionList[i]));
	}

	//Sprite Drawing-----------------------------------------
	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	MaxGentleman.draw();

	HealthBar.draw();

	for (auto itr = CharacterMap.begin(), itrEnd = CharacterMap.end(); itr != itrEnd; itr++)
	{
		CharacterMap[itr->first]->draw();
	}

	//Enemy Moving and attacking------------------------------

	broseff.Move(&Mentlegen);
	broseff.Attack(&Mentlegen);
	broseff.Hurt(&Mentlegen);
	broseff.setGrunt(false);

	//Animations--------------------------------------------

	broseff.Idle();

	broseff.animation(frameCounter, &Mentlegen);

	Mentlegen.animation(frameCounter, shiftPressed);
	if (Mentlegen.getFrame() == 15)
	{
		FzlPlaySound(punch); //PUNCH
	}
	if (Mentlegen.getFrame() == 22)
	{
		FzlPlaySound(heavyPunch); //HEAVY PUNCH
	}

	if (maxGentleman == 10000)
	{
		if ((vPressed) && (Mentlegen.getFrame() == 30) && (superPunch = true))
		{
			if ((Mentlegen.getPosition().distance(broseff.getPosition()) < 100.0f))
			{
				FzlPlaySound(bellRing);
			}
		}
		if (MaxGentleman.getFrame() < 10)
			MaxGentleman.setFrame(10);
		if ((MaxGentleman.getFrame() >= 10))
		{
			MaxGentleman.setFrame(MaxGentleman.getFrame() + 1);
		}
		if (MaxGentleman.getFrame() > 13)
		{
			MaxGentleman.setFrame(10);
		}
	}
	if (maxGentleman < 10000)
	{
		MaxGentleman.setFrame(9);
	}
	if (maxGentleman < 9000)
	{
		MaxGentleman.setFrame(8);
	}
	if (maxGentleman < 8000)
	{
		MaxGentleman.setFrame(7);
	}
	if (maxGentleman < 7000)
	{
		MaxGentleman.setFrame(6);
	}
	if (maxGentleman < 6000)
	{
		MaxGentleman.setFrame(5);
	}
	if (maxGentleman < 5000)
	{
		MaxGentleman.setFrame(4);
	}
	if (maxGentleman < 4000)
	{
		MaxGentleman.setFrame(3);
	}
	if (maxGentleman < 3000)
	{
		MaxGentleman.setFrame(2);
	}
	if (maxGentleman < 2000)
	{
		MaxGentleman.setFrame(1);
	}
	if (maxGentleman == 0)
	{
		MaxGentleman.setFrame(0);
	}

	if ((Mentlegen.getHealth() == 2) && (frameCounter % 4))
	{
		HealthBar.setFrame(3);
	}
	if ((Mentlegen.getHealth() == 1) && (frameCounter % 4))
	{
		HealthBar.setFrame(2);
	}
	if ((Mentlegen.getHealth() == 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(1);
	}
	if ((Mentlegen.getHealth() < 0) && (frameCounter % 4))
	{
		HealthBar.setFrame(0);
		Mentlegen.kill();
		FzlPlaySound(death);
		Final::exit();
		m_parent->GetGameState("GameOver")->SetPaused(false);
	}

	if (spacePressed && (Mentlegen.getPosition().distance(broseff.getPosition()) < 100.0f))
	{
		broseff.decrementHealth();
		std::cout << "HIT\n";
		maxGentleman = maxGentleman + 1000;
		broseff.setGrunt(true);
		if (broseff.getGrunt() == true)
		{
			FzlPlaySound(ballin);
		}
	}
	if (cPressed && (Mentlegen.getPosition().distance(broseff.getPosition()) < 100.0f))
	{
		broseff.decrementHealth();
		broseff.decrementHealth();
		std::cout << "HEAVYHIT\n";
		maxGentleman = maxGentleman + 1000;
		broseff.setGrunt(true);
		if (broseff.getGrunt() == true)
		{
			FzlPlaySound(ballin);
		}
	}
	if (vPressed && (Mentlegen.getPosition().distance(broseff.getPosition()) < 100.0f) && superPunch == true)
	{
		for (int i = 0; i < 10; i++)
		{
			broseff.decrementHealth();
		}
		std::cout << "SUPERHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
		maxGentleman = 0;
		broseff.setGrunt(true);
		if (broseff.getGrunt() == true)
		{
			FzlPlaySound(ballin);
		}
	}

	if (maxGentleman >= 10000)
	{
		maxGentleman = 10000;
		superPunch = true;
	}
	if (maxGentleman > 0 && maxGentleman < 10000)
	{
		maxGentleman = maxGentleman - 7;
	}
	if (maxGentleman <= 0)
	{
		maxGentleman = 0;
	}


	//END GAME

	if (broseff.getAlive() == false)
	{
		Final::exit();
		m_parent->GetGameState("CreditScreen")->SetPaused(false);
	}

	currentHealth = Mentlegen.getHealth();
}

Final::Final() :
Mentlegen(mentlegen, 100.0f, 290.0f, 37.5f, -67.0f, -37.5f, -73.0f, 2),
MaxGentleman(maxGentlemanBar, 1620.0f, 890.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
HealthBar(healthBar, 350.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0),
broseff(boss, 1220.0f, 300.0f, 26.0f, -64.0f, -24.0f, -72.0f, 12),
boundary1(boundaryBox, 960.0f, 380.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary2(boundaryBox, 960.0f, 120.0f, 960.0f, 0.0f, -960.0f, 0.0f, 0),
boundary3(boundaryBox, 1380.0f, 320.0f, 5.0f, 42.0f, -20.0f, -42.0f, 0),
boundary4(boundaryBox, 1280.0f, 200.0f, 5.0f, 42.0f, -20.0f, -42.0f, 0),
boundary5(boundaryBox, 1380.0f, 260.0f, 5.0f, 42.0f, -20.0f, -42.0f, 0)
{

}

void Final::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		Final::SetPaused(m_paused);
	}

	background = FzlLoadSprite("../../../Assets/plane_cockpit.png", 1920, 1080);

	CharacterCollisionList.push_back(&broseff);
	CharacterCollisionList.push_back(&boundary1);
	CharacterCollisionList.push_back(&boundary2);
	CharacterCollisionList.push_back(&boundary3);
	CharacterCollisionList.push_back(&boundary4);
	CharacterCollisionList.push_back(&boundary5);

	CharacterSortVector.push_back(&broseff);
}

void Final::exit()
{
	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		Final::SetPaused(m_paused);
		CreditScreen(hasBeenInitialized);

		FzlDeleteSprite(background);

	}
}



GameOver::GameOver()
{

}


void GameOver::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}

	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	if ((FzlGetKey(FzlKeyLeftShift)) ||
		(FzlGetKey(FzlKeyC)) || 
		(FzlGetKey(FzlKeySpace)) || 
		(FzlGetKey(FzlKeyV)))
	{
		GameOver::exit();
	}
	
}

void GameOver::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		GameOver::SetPaused(m_paused);
	}

	endCondition = false;

	background = FzlLoadSprite("../../../Assets/gameover.png", 1920, 1080);
}

void GameOver::exit()
{
	hasBeenInitialized = false;
	endCondition = true;
	maxGentleman = 5000;
	currentHealth = 2;

	if (m_paused == false)
	{
		m_paused = true;
		GameOver::SetPaused(m_paused);
		Intro(hasBeenInitialized);
	}

	FzlDeleteSprite(background);
}

bool GameOver::shouldEnd()
{
	return endCondition;
}


MainMenu::MainMenu()
{

}


void MainMenu::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;
	}

	if (FzlGetKey(FzlKeyLeftShift))
	{
		MainMenu::exit();
		m_parent->GetGameState("Intro")->SetPaused(false);
	}

	if (FzlGetKey(FzlKeySpace))
	{
		MainMenu::exit();
		m_parent->GetGameState("LoreMenu")->SetPaused(false);
	}

	FzlDrawSprite(MAINMENU, 960.0f, 540.0f, 0.0f);
}

void MainMenu::enter()
{
	FzlPlaySound(creditsSong);
	if (m_paused == true)
	{
		m_paused = false;
		MainMenu::SetPaused(m_paused);
	}

	//(song) = FzlLoadSound("../../../Assets/Sounds/mainmenusong.wav", 0);

}

void MainMenu::exit()
{
	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		MainMenu::SetPaused(m_paused);
		Intro(hasBeenInitialized);
	}

	//FzlDeleteSound(song);

}

///////////////////////////////////////////MAIN MENU////////////////////////////////////////////////////////////////////////////////////////////////////




LoreMenu::LoreMenu()
{

}


void LoreMenu::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;
	}

	if (FzlGetKey(FzlKeyV))
	{
		LoreMenu::exit();
		m_parent->GetGameState("MainMenu")->SetPaused(false);
	}

	FzlDrawSprite(LOREMENU, 960.0f, 540.0f, 0.0f);
}

void LoreMenu::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		LoreMenu::SetPaused(m_paused);
	}
}

void LoreMenu::exit()
{
	hasBeenInitialized = false;

	if (m_paused == false)
	{
		m_paused = true;
		LoreMenu::SetPaused(m_paused);
		MainMenu(hasBeenInitialized);
	}
}

CreditScreen::CreditScreen()
{

}


void CreditScreen::Update()
{
	if (hasBeenInitialized == false)
	{
		enter();
		hasBeenInitialized = true;

	}

	FzlDrawSprite(background, 960.0f, 540.0f, 0.0f);

	if (FzlGetKey(FzlKeyEscape))
	{
		CreditScreen::exit();
	}

}

void CreditScreen::enter()
{
	if (m_paused == true)
	{
		m_paused = false;
		CreditScreen::SetPaused(m_paused);
	}

	endCondition = false;

	background = FzlLoadSprite("../../../Assets/credits.png", 1920, 1080);
}

void CreditScreen::exit()
{
	hasBeenInitialized = false;
	endCondition = true;
	maxGentleman = 5000;
	currentHealth = 2;

	if (m_paused == false)
	{
		m_paused = true;
		CreditScreen::SetPaused(m_paused);
		Intro(hasBeenInitialized);
	}

	FzlDeleteSprite(background);
}

bool CreditScreen::shouldEnd()
{
	return endCondition;
}