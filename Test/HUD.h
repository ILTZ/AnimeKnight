#ifndef HUD_H
#define HUD_H

#include "Drawable.h"
#include "CharTemplate.h"


enum class SocketFunc
{
	WEAPON_SOCKET,
	MAGIC_SOCKET,
	POUTION_SOCKET,
	EMPTY_SOCKET
};



class HUDSocket 
{
private:

	sf::Sprite* iconToDraw = nullptr;

	sf::Texture* socketText = nullptr;

	sf::Sprite* socketToDraw = nullptr;

	SocketFunc socketClass;

	

public:

	HUDSocket(SocketFunc wcClass = SocketFunc::EMPTY_SOCKET, DrawableObject* object = nullptr);

	virtual ~HUDSocket();


	void setSize(sf::Vector2i &newSize);

	void setPosition(sf::Vector2i &newPos);

	void setPosition(float x, float y);

	void drawSocket(sf::RenderWindow* w);
	// Take some <DrawableObject*> and get from it sprite to draw by "getDrawableSprite()".
	void setIconToDraw(DrawableObject* object);



	SocketFunc getSocketClass() const { return socketClass; }

	void setSocketClass(SocketFunc nClass) { socketClass = nClass; }

private:


};


enum class GameMode
{
	MAIN_MENU,
	PAUSE,
	DEATH,
	INVENTORY,
	DIALOG
};

class HUD : public DrawableObject
{
private:



	CharTemplate* character = nullptr;

	sf::Sprite* botPanel = nullptr;

	std::vector<sf::Texture*> allTextures;

	std::vector<HUDSocket*> allSockets;


	sf::Sprite* hpBarSprite = nullptr;

	sf::Sprite* mpBarSprite = nullptr;

	std::vector<sf::Sprite*> barsSprites;

	sf::RectangleShape* rectForHPMPBars = nullptr;

public:

	HUD();

	virtual ~HUD();

	void drawSockets(sf::RenderWindow* w);

	// Add new socket(default is <EMPTY>)
	void addSocket(SocketFunc sFunc = SocketFunc::EMPTY_SOCKET, DrawableObject* obj = nullptr);
	// Add in existence socket icon to draw
	void addInSocket(SocketFunc sClass, DrawableObject* obj);

	void setCharacter(CharTemplate* aChar) { character = aChar; }

	void drawHpMpBars(sf::RenderWindow* w, int const &hp, int const &mp);

// DrawableObject base func {

	virtual void drawOnWindow(sf::RenderWindow* w) override;

	// Empty for this
	virtual void setCurrentXYLocation(int xLoc, int yLoc) override {};
	// Empty for this
	virtual void setCurrentRotation(int rotation) override {};
	// Empty for this
	virtual void setCurrentScale(float const& scaleX, float const& scaleY) override {};

	// Return <nullptr> always
	virtual sf::Sprite* getDrawableSprite() override { return nullptr; }

// DrawableObject base func }




private:




};

#endif