#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "CharTemplate.h"
#include <SFML/Graphics.hpp>
#include "HUD.h"
#include "Level.h"

#include "ModifyClasses.h"

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

	bool isWork = false;

	GameMode cureGameMode = GameMode::NONE;

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

	void setWorkState(bool const& _workState) { isWork = _workState; }

	void setGameMode(GameMode const& _gameMode) { cureGameMode = _gameMode; }
private:



};



// Events things {
struct KeyEvent
{
	sf::Event event;

	KeyEvent(sf::Event const& _event)
	{
		event = _event;
	}
};

struct MouseEvent
{
	sf::Event event;
	sf::Vector2i mousePos;


	MouseEvent(sf::Event const& _event, sf::Vector2i const& _mousePos)
	{
		event = _event;
		mousePos = _mousePos;
	}

};



class EventHandler
{
private:

	ModifyClasses::MainWindow* mainWindow = nullptr;

	CharTemplate* currentPawn = nullptr;

	HUD* hud = nullptr;

	GameMode curGameMode = GameMode::NONE;

	RenderController* renderController = nullptr;

	//std::vector<sf::Event> events;
	//std::vector<sf::Event> mouseEvents;


	std::vector<KeyEvent> keyEvents;
	std::vector<MouseEvent> mouseEvents;

public:
	EventHandler();
	
	~EventHandler();

	void doHandlerWork();
	
	void doHandlerWorkLoop();

	void setControlPawn(CharTemplate* character);

	void setMainWindow(ModifyClasses::MainWindow* _mw) { mainWindow = _mw; }

	void setHUD(HUD* h) { hud = h; }

	void setGameMode(GameMode const& _gm) { curGameMode = _gm; }
	GameMode getGameMode() const { return curGameMode; }

	//void addEvent(sf::Event& _event) { events.push_back(_event); }

	
	void addKeyEvent(sf::Event const& _event);
	void addMouseEvent(sf::Event const& _event, sf::Vector2i const& _mousePos);



private:

	bool deleteEvent(int const& _index);

	void setRenderController(RenderController* _rc) { renderController = _rc; }

	void clickOnButtonCommandHandler(BtnFunc::BtnFunc const& _func);

	void doHandlerWorkB(sf::Event const& event);

	void mouseEventHandler(sf::Vector2i const &_mousePos, sf::Event const& _event);


};


#endif