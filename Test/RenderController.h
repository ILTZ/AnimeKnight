#ifndef RENDERC_H
#define RENDERC_H

#define LOG(str) printf("RenderController::LOG::%s\n", str)

#include <SFML\Graphics.hpp>
#include <vector>
#include "Drawable.h"
#include "EventHandler.h"
#include "HUD.h"
#include "Level.h"

class RenderController
{
private:

	EventHandler* eventHandler = nullptr;

	sf::RenderWindow* mainWindow = nullptr;

	HUD* hud = nullptr;

	CollisionHendler* colHendler = nullptr;

	int windowWidth{ 0 };

	int windowHeight{ 0 };

	int frameRate{ 60 };

	sf::Mutex renderMutex;

	std::vector<Level*> allLevels;

// DrawLayers {

	// For some static objets (like backGround, ground (for walk))
	std::vector<sf::Sprite*> backGroundRenderArray;

	// For characters and another objets with animations
	std::vector<DrawableObject*> haveAnimationObjetsArray;

	void collisionPreparation();

	bool prepWasDone = false;

// DrawLayers }

// Render things {

	void drawBackground();

	void drawAnimationObjects();

// Render things }


// 4 Collision handler {

	int currentLvlCount = 0;

	bool lwlWasSwitch = false;

	bool sceneWasSwitch = false;

	void setPropertiesForCollisionHandler();

// 4 Collision handler }



public:




// Constructors {

	RenderController();

	RenderController(int const& wWidth, int const& wHeight);

// Constructors }




// Render things {

	void mainRenderProcess();

	void addSpriteToBackgroundLayout(sf::Sprite* something);

	void addDrawableToAnimationsObject(DrawableObject* object);

	sf::RenderWindow* getRenderWindow() const { return mainWindow; }

	

	int getCurrentFrameRate() const { return frameRate; }

	void setCurrentFrameRate(int const& nFrameRate);

// Render things }


// Handlers {

	void setEventHandler(EventHandler* handler);

	void setCollisionHendler(CollisionHendler* nHendler) { colHendler = nHendler; }
	// 4 CollisionHandler {



	// 4 CollisionHandler }


// Handlers }






	bool debugMode = false;

	void debugMsg(const char* mesage) { if (debugMode) LOG(mesage); }
};


#endif