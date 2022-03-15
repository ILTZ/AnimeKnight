#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "CharTemplate.h"
#include <SFML/Graphics.hpp>
#include "HUD.h"
#include "Level.h"

class RenderController;


class CollisionHendler
{
private:

	std::vector<CollisionObject*> collisionObjectsOnScene;

	std::vector<CollisionObject*> enemyOnScene;

	CollisionObject* controlPawn = nullptr;

	bool isEnable = false;

	bool gameContinue = true;

	GameMode gameStatus = GameMode::PAUSE;

	bool sceneWasCrete = false;

	sf::Mutex* collisionMutex = nullptr;

	RenderController* renderController = nullptr;

public:

	CollisionHendler();

	~CollisionHendler();

	void checkAllObjectsCollision();



	void setControlPawn(CollisionObject* nControlPawn) { controlPawn = nControlPawn; }
	CollisionObject* getControlPawn() const { return controlPawn; }

	void addCollisionObject(CollisionObject* newCollisionObject);
	CollisionObject* getCollisionObjectPtr(int& index) const;

	void clearCollisionObjectsArray();
	void getCollisionObjectFromlvl(Level* currentLevel);

	void setCollisionHandlerEnabled(bool const& value) { isEnable = value; }
	void setGameStatus(bool const& gameStat) { gameContinue = gameStat; }

	void setSceneCreateStatus(bool const& vakue) { sceneWasCrete = true; }
	bool getSceneCreateStatus() const { sceneWasCrete; }

	void setRenderController(RenderController* _rc) { renderController = _rc; }


	void collisionMainProcess();

private:



};


class EventHandler
{
private:

	sf::RenderWindow* mainWindow = nullptr;

	CharTemplate* currentPawn = nullptr;

	HUD* hud = nullptr;

	GameMode curGameMode = GameMode::NONE;

	RenderController* renderController = nullptr;

public:
	EventHandler();
	
	~EventHandler();

	void doHandlerWork();

	void setControlPawn(CharTemplate* character);

	void setMainWindow(sf::RenderWindow* window);

	void setHUD(HUD* h) { hud = h; }

	void setGameMode(GameMode const& _gm) { curGameMode = _gm; }
	GameMode getGameMode() const { return curGameMode; }

private:

	void setRenderController(RenderController* _rc) { renderController = _rc; }

	void clickOnButtonCommandHandler(BtnFunc::BtnFunc const& _func);
};


#endif