#include <iostream>
#include <SFML/Graphics.hpp>

#include "MainCharacter.h"
#include "RenderController.h"
#include "EventHandler.h"
#include "HUD.h";
#include <thread>

using namespace sf;

#include <filesystem>

const int wWidth = 1200;
const int wHeight = 900;
const float curGS = .15f;
const int frameRate = 60;

#include <functional>

template <typename T>
void jopa(const T& f)
{
	std::thread* t = new std::thread([&] {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		f();
		});
	
}



int main()
{
	
	
	jopa([]{
		std::cout << "Fak of";
		});





	

	Texture* t = new sf::Texture();
	t->loadFromFile("K:\\PixelSheat\\Knight\\Sprites\\Backgrounds\\Dung.png");
	Sprite* s = new Sprite(*t);
	


	Clock timer;
	timer.restart();

	MainCharacter* cahr = new MainCharacter();
	cahr->setCurrentGameSpeed(curGS);
	cahr->setGameStatus(true);

	HUD* hud = new HUD();
	hud->setCharacter(cahr);
	hud->addInSocket(SocketFunc::WEAPON_SOCKET, cahr->getCurrentWeapon());

	CollisionHendler* colHendler = new CollisionHendler();
	colHendler->setControlPawn(cahr);

// RenderProcessThread {


	// Problem with first check collision..

	sf::Thread renderThread([&]
		{
			RenderController* rc = new RenderController(wWidth, wHeight);
			rc->addDrawableToAnimationsObject(cahr);
			rc->setHUD(hud);
			//rc->addDrawableToAnimationsObject(hud);
			rc->addSpriteToBackgroundLayout(s);
			//rc->setCurrentFrameRate(frameRate);

			EventHandler* handler = new EventHandler();
			handler->setControlPawn(cahr);
			handler->setHUD(hud);

			rc->setEventHandler(handler);
			rc->setCollisionHendler(colHendler);
			rc->debugMode = true;

			rc->mainRenderProcess();
		});
	

	sf::Thread collisionProcessThread([&]
		{
			colHendler->collisionMainProcess();
			
		});

	renderThread.launch();
	collisionProcessThread.launch();

// RenderProcessThread }





	

	

	return 0;
}


