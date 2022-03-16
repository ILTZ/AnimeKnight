#include "EventHandler.h"
#define LOG(whichHandler, message) printf("Handler::%s::%s\n", whichHandler, message)
#include <iostream>

#include "RenderController.h"

EventHandler::EventHandler()
{
	curGameMode = GameMode::MAIN_MENU;
}
EventHandler::~EventHandler()
{
	currentPawn = nullptr;
	mainWindow = nullptr;
}


void EventHandler::setControlPawn(CharTemplate* character)
{
	if (!character)
	{
		return;
	}

	currentPawn = character;
}
void EventHandler::setMainWindow(sf::RenderWindow* window)
{
	if (!window)
	{
		return;
	}

	mainWindow = window;
}


// Handler things {

void printCoords(int x, int y)
{
	std::cout << "Current coords mouse:";
	std::cout << x << ":" << y << std::endl;
}

void EventHandler::doHandlerWork()
{
	if (curGameMode == GameMode::GAME_PROCESS)
	{
		if (!mainWindow || !currentPawn)
			return;
		if (!(mainWindow->isOpen()))
			return;

		sf::Event event;

		while (mainWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mainWindow->close();
			}

			// Key handler {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				currentPawn->moveToSomeSide(CurrentDirection::LEFT);
				//return;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				currentPawn->moveToSomeSide(CurrentDirection::RIGHT);
				//return;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				currentPawn->jump(CurrentDirection::UP, 1);
				//return;
			}



			if (event.type == sf::Event::KeyPressed)
			{

				switch (event.key.code)
				{
					/*case sf::Keyboard::A:
					case sf::Keyboard::Left:
						currentPawn->moveToSomeSide(CurrentDirection::LEFT);
						break;

					case sf::Keyboard::D:
					case sf::Keyboard::Right:
						currentPawn->moveToSomeSide(CurrentDirection::RIGHT);
						break;

					case sf::Keyboard::W:
					case sf::Keyboard::Up:
						currentPawn->jump(CurrentDirection::UP, 1);
						break;

					case sf::Keyboard::S:
					case sf::Keyboard::Down:
						currentPawn->moveToSomeSide(CurrentDirection::BOT);
						break;*/

				case sf::Keyboard::Escape:
					if (hud)
						hud->prepareBtnsForMenu("pa");
					curGameMode = GameMode::PAUSE;
					break;



				case sf::Keyboard::Q:
					currentPawn->useAbility(1);
					break;
				case sf::Keyboard::E:
					currentPawn->useAbility(2);
					break;



				case sf::Keyboard::R:
					currentPawn->usePoushen(1);
					break;

				case sf::Keyboard::F:
					currentPawn->interactiveAction();
					break;

					// Weapon switch {

				case sf::Keyboard::Num1:
					currentPawn->changeWeapon(1);
					hud->addInSocket(SocketFunc::WEAPON_SOCKET, currentPawn->getCurrentWeapon());
					break;

				case sf::Keyboard::Num2:
					currentPawn->changeWeapon(3);
					hud->addInSocket(SocketFunc::WEAPON_SOCKET, currentPawn->getCurrentWeapon());
					break;

				case sf::Keyboard::Num3:
					currentPawn->changeWeapon(2);
					hud->addInSocket(SocketFunc::WEAPON_SOCKET, currentPawn->getCurrentWeapon());
					break;

				case sf::Keyboard::Num4:
					currentPawn->changeWeapon(4);
					hud->addInSocket(SocketFunc::WEAPON_SOCKET, currentPawn->getCurrentWeapon());
					break;

				}

			}
			else if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					currentPawn->jump(CurrentDirection::BOT, 0);
					break;

				default:
					currentPawn->moveToSomeSide(CurrentDirection::STAY);
					break;
				}


			}

			// Key handler }


			// Mouse Handler {

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					currentPawn->dropTimer();
					currentPawn->attack();
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{

			}

			// Mouse Handler }

		}
	}

	if (curGameMode == GameMode::MAIN_MENU || curGameMode == GameMode::PAUSE)
	{
		if (!mainWindow || !currentPawn)
			return;
		if (!(mainWindow->isOpen()))
			return;
		if (!hud)
			return;

		sf::Event event;

		while (mainWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mainWindow->close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape &&
					curGameMode == GameMode::PAUSE)
					curGameMode = GameMode::GAME_PROCESS;
					
				
				
			}


			if (event.type == sf::Event::MouseButtonPressed)
			{
				hud->checkMouseClickOnButton(sf::Mouse::getPosition(*mainWindow));
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				bool result;
				BtnFunc::BtnFunc temp;

				std::tie(result, temp) = hud->dropIsClickedButoonStatus();

				if (result)
				{
					clickOnButtonCommandHandler(temp);
				}
				
			}
		}
	}
}


void EventHandler::clickOnButtonCommandHandler(BtnFunc::BtnFunc const& _func)
{
	if (curGameMode == GameMode::MAIN_MENU)
	{
		switch (_func)
		{
		case BtnFunc::BtnFunc::MM_NEW_GAME:
			curGameMode = GameMode::GAME_PROCESS;
			break;

		case BtnFunc::BtnFunc::MM_CONTINUE:

			break;

		case BtnFunc::BtnFunc::MM_SETTING:

			break;

		case BtnFunc::BtnFunc::MM_EXIT:
			mainWindow->close();
			break;

		default:

			break;
		}
	}	// Main menu }	
	else if (curGameMode == GameMode::PAUSE)
	{
		switch (_func)
		{
		case BtnFunc::BtnFunc::PA_BACK_TO_MAIN_MENU:
			if (hud)
				hud->prepareBtnsForMenu("mm");
			curGameMode = GameMode::MAIN_MENU;
			break;

		case BtnFunc::BtnFunc::PA_CONTINUE:
			curGameMode = GameMode::GAME_PROCESS;
			break;

		case BtnFunc::BtnFunc::PA_SAVE:

			break;

		case BtnFunc::BtnFunc::PA_EXIT:
			mainWindow->close();
			break;
		}
	}	// Pause }
	else if (curGameMode == GameMode::DEATH)
	{

	}
}

// Handler things }



// CollisionHendler {

CollisionHendler::CollisionHendler()
{
	collisionMutex = new sf::Mutex();
}

CollisionHendler::~CollisionHendler()
{
	if (collisionMutex)
	{
		delete collisionMutex;
	}
}


void CollisionHendler::checkAllObjectsCollision()
{
	CharTemplate* temp = static_cast<CharTemplate*>(controlPawn);
	if (!temp)
		return;


	for (int i = 0; i < collisionObjectsOnScene.size(); ++i)
	{
		bool result;
		CurrentDirection pos;

		std::tie(result, pos) = controlPawn->checkCollisionObject(collisionObjectsOnScene[i]);

		if (result)
		{

			

			if (collisionObjectsOnScene[i] && (collisionObjectsOnScene[i]->getCollisionPurpose() == CollisionPurpose::FLOOR))
			{
				//LOG("CollisionHandler", "GetEvent::LockMovement_cause_FLOOR");
				temp->lockMovement(CurrentDirection::BOT);

			}
			else if (collisionObjectsOnScene[i] && (collisionObjectsOnScene[i]->getCollisionPurpose() == CollisionPurpose::MOVE_BLOCK))
			{
				//LOG("CollisionHandler", "GetEvent::LockMovement_cause_MOVE_BLOCK");
				temp->lockMovement(pos);
			}
		
			

			return;
		}
	}

	temp->unlockMovement();

}

void CollisionHendler::addCollisionObject(CollisionObject* newCollisionObject)
{
	collisionObjectsOnScene.push_back(newCollisionObject);
}

CollisionObject* CollisionHendler::getCollisionObjectPtr(int &index) const
{
	if (index > (collisionObjectsOnScene.size() - 1) || index < (collisionObjectsOnScene.size()))
		return nullptr;

	return collisionObjectsOnScene[index];
}

void CollisionHendler::clearCollisionObjectsArray()
{
	collisionObjectsOnScene.clear();
}


void CollisionHendler::getCollisionObjectFromlvl(Level* currentLevel)
{
	if (currentLevel)
	{
		std::vector<LevelTile*> temp = currentLevel->getAllLevelTilesArray();
		for (auto el : temp)
		{
			collisionObjectsOnScene.push_back(el);
		}
	}
}

void CollisionHendler::collisionMainProcess()
{
	while (gameContinue)
	{
		if (cureGameMode == GameMode::GAME_PROCESS)
		{
			
			checkAllObjectsCollision();

		}
	}
}

// CollisionHendler }