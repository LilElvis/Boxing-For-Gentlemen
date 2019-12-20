#include "States.h"
#include <Windows.h>

int main()
{
	SetWindowText(GetConsoleWindow(), "BOXING FOR GENTLEMEN");

	const int windowWidth = 1920;
	const int windowHeight = 1080;
	
	GameStateManager Manager;

	FzlInit("Boxing For Gentlemen", 1920, 1080, 1);

	spriteLoading();

	soundLoading();
	
	std::cout << "FIRST HEELO \t";
	std::cout << heavyPunch << " " << punch << " " << std::endl;


	int shouldEnd = 0;
	int shouldEnd2 = 0;

	//MainMenu here
	MainMenu* mainMenu = new MainMenu();
	LoreMenu* loreMenu = new LoreMenu();

	//Game Over Screen
	GameOver* gameOver = new GameOver();
	CreditScreen* creditScreen = new CreditScreen();
	
	Intro* intro = new Intro();
	PrisonWalkway1* PW1 = new PrisonWalkway1();
	PrisonWalkway2* PW2 = new PrisonWalkway2();
	Sewer* sewer = new Sewer();
	Sewer2* sewer2 = new Sewer2();
	Sewer3* sewer3 = new Sewer3();
	Street* street = new Street();
	Street2* street2 = new Street2();
	Street3* street3 = new Street3();
	EmbassyLevel*  embassyLevel = new EmbassyLevel();
	Embassy2* embassy2 = new Embassy2();
	Embassy3* embassy3 = new Embassy3();
	Plane* plane = new Plane();
	Plane2* plane2 = new Plane2();
	Plane3* plane3 = new Plane3();
	Final* final = new Final();



	Manager.AddGameState("MainMenu", mainMenu);
	Manager.AddGameState("LoreMenu", loreMenu);

	Manager.AddGameState("GameOver", gameOver);
	Manager.AddGameState("CreditScreen", creditScreen);

	Manager.AddGameState("Intro", intro);
	Manager.AddGameState("PrisonWalkway1", PW1);
	Manager.AddGameState("PrisonWalkway2", PW2);
	Manager.AddGameState("Sewer", sewer);
	Manager.AddGameState("Sewer2", sewer2);
	Manager.AddGameState("Sewer3", sewer3);
	Manager.AddGameState("Street", street);
	Manager.AddGameState("Street2", street2);
	Manager.AddGameState("Street3", street3);
	Manager.AddGameState("Embassy", embassyLevel);
	Manager.AddGameState("Embassy2", embassy2);
	Manager.AddGameState("Embassy3", embassy3);
	Manager.AddGameState("Plane", plane);
	Manager.AddGameState("Plane2", plane2);
	Manager.AddGameState("Plane3", plane3);
	Manager.AddGameState("Final", final);


	mainMenu->SetPaused(false);
	loreMenu->SetPaused(true);

	gameOver->SetPaused(true);
	creditScreen->SetPaused(true);

	intro->SetPaused(true); //ALL other levels will be paused unless told otherwise.
	PW1->SetPaused(true);
	PW2->SetPaused(true);
	sewer->SetPaused(true);
	sewer2->SetPaused(true);
	sewer3->SetPaused(true);
	street->SetPaused(true);
	street2->SetPaused(true);
	street3->SetPaused(true);
	embassyLevel->SetPaused(true);
	embassy2->SetPaused(true);
	embassy3->SetPaused(true);
	plane->SetPaused(true);
	plane2->SetPaused(true);
	plane3->SetPaused(true);
	final->SetPaused(true);
	
	std::cout << "Before loop\t";
	std::cout << heavyPunch << " " << punch << " " << std::endl;


	while (!shouldEnd && !shouldEnd2)
	{
		Manager.Update();
		
		shouldEnd = gameOver->shouldEnd();

		shouldEnd2 = creditScreen->shouldEnd();

		FzlSwapBuffers();
	}
	FzlDestroy();
}