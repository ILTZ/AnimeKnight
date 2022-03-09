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

class Button;

class HUD : public DrawableObject
{
private:

	GameMode currentGameMode = GameMode::MAIN_MENU;


	CharTemplate* character = nullptr;

	sf::Sprite* botPanel = nullptr;

	std::vector<sf::Texture*> allTextures;

	std::vector<HUDSocket*> allSockets;


	sf::Sprite* hpBarSprite = nullptr;

	sf::Sprite* mpBarSprite = nullptr;

	std::vector<sf::Sprite*> barsSprites;

	sf::RectangleShape* rectForHPMPBars = nullptr;


	std::vector<Button*> btnsOnWindow;

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


	void drawMainMenu(sf::RenderWindow* w);

	void drawPauseMenu(sf::RenderWindow* w);

	void drawSettingsMenu(sf::RenderWindow* w);

	void drawGameHud(sf::RenderWindow* w);

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

	// The parameter determines for which game state the buttons will be prepared:
	// "mm" - main menu, "st" - settings, "pa" - pause.
	void prepareBtnsForMenu(std::string &_param);
	

	


private:




};


enum class ButtonFunction
{
	ACCEPT,
	CANCLE,
	BACK,
	SETTINGS,
	NEW_GAME,
	CONTINUE,
	CLOSE,
	NONE
};




class Button : public DrawableObject
{
private:

	sf::Texture* baseText = nullptr;

	sf::RectangleShape* buttonShape = nullptr;

	ButtonFunction bf = ButtonFunction::NONE;

	sf::Text* buttonText = nullptr;

	int Yloc = 0;
	int Xloc = 0;

	int hight = 50;
	int width = 20;

public:

	Button();

	Button(ButtonFunction _bf, const char* _btnText);

	~Button();


// Base Drawable {

	virtual void drawOnWindow(sf::RenderWindow* w) override;

	virtual void setCurrentXYLocation(int xLoc, int yLoc) override;

	virtual void setCurrentRotation(int rotation) override {};

	virtual void setCurrentScale(float const& scaleX, float const& scaleY) override;

	// Return <nullptr> always
	virtual sf::Sprite* getDrawableSprite() override { return nullptr; }

// Base Drawable }



	ButtonFunction getBtnFunction() const { return bf; }

	int getYLoc() const { return Yloc; }
	int getXLoc() const { return Xloc; }

	void setButtonText(std::string const &_text);
	std::string getButtonText() const;

	int getCharacterSize() const;
	void setCharacterSize(int const  &_size);
};



#endif