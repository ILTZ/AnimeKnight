#include "RenderController.h"

#define LOG(str) printf("RenderController::LOG::%s\n", str)


RenderController::RenderController()
{
	int windowWidth{ 0 };

	int windowHeight{ 0 };
}

RenderController::RenderController(int const& wWidth, int const& wHeight) 
	: windowWidth{wWidth},windowHeight{wHeight}
{
	mainWindow = new sf::RenderWindow(sf::VideoMode(wWidth, wHeight), "AnimeKnight", sf::Style::Titlebar | sf::Style::Close);
	


	addDrawableToAnimationsObject(hud);


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
			if (hud)
				hud->drawGameHud(mainWindow);
			drawAnimationObjects();
			break;

		case GameMode::PAUSE:
			allLevels[currentLvlCount]->drawLevel(mainWindow);
			if (hud)
				hud->drawPauseMenu(mainWindow);
			drawAnimationObjects();
			break;

		case GameMode::MAIN_MENU:
			if (hud)
				hud->drawMainMenu(mainWindow);

		case GameMode::INVENTORY:

			break;

		case GameMode::DEATH:

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

		if (eventHandler)
			eventHandler->doHandlerWork();

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
	if ((colHendler && allLevels[0]) && (!(prepWasDone)))
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