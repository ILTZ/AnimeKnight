#include "RenderController.h"
#include "MainCharacter.h"
#include "Tasks.h"

#define LOG(str) printf("RenderController::LOG::%s\n", str)






namespace PathToLvlResources
{
	namespace LVL_1
	{

	}
	namespace LVL_2
	{

	}
	namespace LVL_3
	{

	}
}


RenderController::RenderController()
{
	int windowWidth{ 0 };

	int windowHeight{ 0 };
}

RenderController::RenderController(int const& wWidth, int const& wHeight) 
	: windowWidth{wWidth},windowHeight{wHeight}
{
	mainWindow = new sf::RenderWindow(sf::VideoMode(wWidth, wHeight), "AnimeKnight", sf::Style::Titlebar | sf::Style::Close);

	debugMsg("MainWindow is created.");
	Level* nl = new Level();
	nl->setBackgroundSprite("K:\\PixelSheat\\Knight\\Sprites\\Backgrounds\\Dung.png");

	allLevels.push_back(nl);


	

	

}

void RenderController::drawProcess()
{
	if (eventHandler)
	{
		switch (eventHandler->getGameMode())
		{
		case GameMode::GAME_PROCESS:
			allLevels[currentLvlCount]->drawLevel(mainWindow);

			drawAnimationObjects();

			if (hud)
				hud->drawGameHud(mainWindow);

			if (colHendler)
				colHendler->setGameMode(GameMode::GAME_PROCESS);
			break;

		case GameMode::PAUSE:
			allLevels[currentLvlCount]->drawLevel(mainWindow);
			
			drawAnimationObjects();

			if (hud)
				hud->drawPauseMenu(mainWindow);
			break;

		case GameMode::MAIN_MENU:
			if (hud)
				hud->drawMainMenu(mainWindow);

		case GameMode::INVENTORY:

			break;

		case GameMode::DEATH:

			break;

		case GameMode::NEW_GAME:

			break;
		}
	}
}



void RenderController::mainRenderProcess()
{
	if (!mainWindow)
	{
		debugMsg("Have no MW to start <MainWindowProcess>.");
		return;
	}

	
	
	
	while (mainWindow->isOpen())
	{
		collisionPreparation();

		
		mainWindow->setActive(true);

		
		mainWindow->clear();

		//if (eventHandler)
		//	eventHandler->doHandlerWork();

		launchHandler();

		sf::Event svent;
		while (mainWindow->pollEvent(svent))
		{
			if (svent.type == sf::Event::Closed)
			{
				mainWindow->close();
			}
		}


		
		renderMutex.lock();

		//allLevels[0]->drawLevel(mainWindow);

		//drawAnimationObjects();

		drawProcess();

		renderMutex.unlock();
	


		mainWindow->display();

	}
	
}

void RenderController::launchHandler()
{
	if (handlerIsWork)
		return;

	if (!eventHandler)
	{
		ThreadTasks::Tasks* t = new ThreadTasks::Tasks();
		t->setFunc([&] {
			while (true)
			{
				eventHandler->doHandlerWork();
			}
			});
		t->startTask();
	}
}

// Render work {

void RenderController::addSpriteToBackgroundLayout(sf::Sprite* something)
{
	if (!something)
	{
		debugMsg("Have no ptr to add in <BackgroundVector>.");
		return;
	}

	backGroundRenderArray.push_back(something);
}

void RenderController::addDrawableToAnimationsObject(DrawableObject* object)
{
	if (!object)
	{
		debugMsg("Have no ptr to add in <HaveAnimationsObjectVector>.");
		return;
	}

	haveAnimationObjetsArray.push_back(object);
}

void RenderController::drawBackground()
{
	for (sf::Sprite* sprite : backGroundRenderArray)
	{
		if (sprite)
		{
			mainWindow->draw(*sprite);
		}
	}
}

void RenderController::drawAnimationObjects()
{
	for (DrawableObject* object : haveAnimationObjetsArray)
	{
		if (object)
		{
			object->drawOnWindow(mainWindow);
		}
	}
}

// Render work }


void RenderController::setCurrentFrameRate(int const& nFrameRate)
{
	frameRate = nFrameRate;
	if (mainWindow)
	{
		mainWindow->setFramerateLimit(frameRate);
	}
}

void RenderController::setEventHandler(EventHandler* handler)
{
	if (!handler)
	{
		debugMsg("EventHandler not connected.");
		return;
	}

	eventHandler = handler;
	eventHandler->setMainWindow(mainWindow);
}

void RenderController::collisionPreparation()
{
	if ((colHendler && allLevels[currentLvlCount]) && (!(prepWasDone)))
	{
		colHendler->getCollisionObjectFromlvl(allLevels[currentLvlCount]);
		colHendler->setCollisionHandlerEnabled(true);
		prepWasDone = true;
	}
}

void RenderController::setPropertiesForCollisionHandler()
{
	if (colHendler)
	{


	}
}

// Preparations after switch game mode {



bool RenderController::prepareForNewGame()
{
	mainCharacter = new MainCharacter();
	if (!mainCharacter)
		throw;

	colHendler = new CollisionHendler();
	if (!colHendler)
		throw;
	

	ThreadTasks::Tasks* t = new ThreadTasks::Tasks();
	t->setFunc(std::function<void(RenderController*, int)>(&RenderController::prepareLVL), this, 0);
	

	//ThreadTasks::Tasks* temp = new ThreadTasks::Tasks();
	//temp->setFunc(prepareLVL, currentLvlCount);



	return false;
}

bool RenderController::prepareForContinueGame()
{

	


	return false;
}

bool RenderController::preapareCollisionObjects()
{
	if ((colHendler && allLevels[currentLvlCount]) && (!(prepWasDone)))
	{
		colHendler->getCollisionObjectFromlvl(allLevels[currentLvlCount]);
		colHendler->setCollisionHandlerEnabled(true);
		prepWasDone = true;
		return true;
	}
	return false;
}

void RenderController::prepareLVL(int const& _lvlCount)
{
	Level* nl = new Level();

	switch (_lvlCount)
	{
	case 1:

		return;
		break;

	case 2:

		return;;
		break;

	case 3:

		
		return;
		break;

	default:


		delete nl;
		return;
		break;
	}
	

	return;
}

// Preparations afterswitch game mode }