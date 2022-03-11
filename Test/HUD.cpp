#include "HUD.h"
#include "Paths.h"

#define LOG(str) printf("HUD::%s\n", str)

// Namespaces paths {

namespace PathHUD
{
	namespace PathToButtonResources
	{
		const std::string pathToBtnUp	= getCurrentAssetsDirectory() + "HUD\\btnUp.png";
		const std::string pathToBtnDown = getCurrentAssetsDirectory() + "HUD\\btnDown.png";
		
		const std::string pathToFont	= getCurrentAssetsDirectory() + "";
	}
	namespace PathToHUDResources
	{
		const std::string pathToBotPanel	= getCurrentAssetsDirectory() + "HUD\\HUD_bot_panel.png";
		const std::string pathToHpMpBar		= getCurrentAssetsDirectory() + "HUD\\hud_bar2.png";

		const std::string pathToHUDSocket	= getCurrentAssetsDirectory() + "HUD\\bot_panel_socket.png";
	}
	
}

// Namespaces paths }





// HUD {

HUD::HUD()
{
	using namespace PathHUD;


	sf::Texture* t = new sf::Texture();
	t->loadFromFile(PathToHUDResources::pathToBotPanel);
	botPanel = new sf::Sprite(*t);

	allTextures.push_back(t);


	sf::Texture* t2 = new sf::Texture();
	t2->loadFromFile(PathToHUDResources::pathToHpMpBar);

	hpBarSprite = new sf::Sprite(*t2);
	hpBarSprite->setOrigin(hpBarSprite->getGlobalBounds().width / 2, hpBarSprite->getGlobalBounds().height / 2);

	mpBarSprite = new sf::Sprite(*t2);
	mpBarSprite->setOrigin(mpBarSprite->getGlobalBounds().width / 2, mpBarSprite->getGlobalBounds().height / 2);

	sf::Vector2f size(mpBarSprite->getGlobalBounds().width, mpBarSprite->getGlobalBounds().height);
	rectForHPMPBars = new sf::RectangleShape(size);
	rectForHPMPBars->setOrigin(0, rectForHPMPBars->getSize().y / 2);

	barsSprites.push_back(hpBarSprite);
	barsSprites.push_back(mpBarSprite);

	addSocket(SocketFunc::WEAPON_SOCKET);
	addSocket(SocketFunc::MAGIC_SOCKET);
	addSocket(SocketFunc::POUTION_SOCKET);
	addSocket(SocketFunc::EMPTY_SOCKET);
}

HUD::~HUD()
{
	if (botPanel)
	{
		delete botPanel;
		botPanel = nullptr;
	}
	for (sf::Texture* t : allTextures)
	{
		delete t;
	}
	for (HUDSocket* socket : allSockets)
	{
		delete socket;
	}
	if (rectForHPMPBars)
	{
		delete rectForHPMPBars;
		rectForHPMPBars = nullptr;
	}
}

void HUD::drawOnWindow(sf::RenderWindow* w)
{
	if (botPanel)
	{
		botPanel->setPosition(0, w->getSize().y - botPanel->getGlobalBounds().height);
		w->draw(*botPanel);

		if (character)
		{
			addInSocket(SocketFunc::WEAPON_SOCKET, character->getCurrentWeapon());
		}


		drawSockets(w);
		drawHpMpBars(w, 100, 100);
	}
}

// Some game states draw {

void HUD::drawGameHud(sf::RenderWindow* w)
{
	if (botPanel)
	{
		botPanel->setPosition(0, w->getSize().y - botPanel->getGlobalBounds().height);
		w->draw(*botPanel);

		if (character)
		{
			addInSocket(SocketFunc::WEAPON_SOCKET, character->getCurrentWeapon());
		}


		drawSockets(w);
		drawHpMpBars(w, 100, 100);
	}
}

void HUD::drawMainMenu(sf::RenderWindow* w)
{
	if (w && btnsOnWindow.size() > 0)
	{
		for (int i = 0; i < btnsOnWindow.size(); ++i)
		{
			btnsOnWindow[i]->setCurrentXYLocation(w->getSize().x,
				(w->getSize().y / btnsOnWindow.size()) * (i + 1));
			
			btnsOnWindow[i]->drawOnWindow(w);
		}
	}
}

void HUD::drawPauseMenu(sf::RenderWindow* w)
{

}

void HUD::drawSettingsMenu(sf::RenderWindow* w)
{

}


// Some game states draw }

void HUD::drawSockets(sf::RenderWindow* w)
{
	for (int i = 0; i < allSockets.size(); ++i)
	{
		if (allSockets[i])
		{
			sf::Vector2i posCoords;

			posCoords.x = ((botPanel->getGlobalBounds().width / 2) / allSockets.size()) * (i + 1);
			posCoords.y = w->getSize().y - botPanel->getGlobalBounds().height / 2;

			allSockets[i]->setPosition(posCoords);
			allSockets[i]->drawSocket(w);
		}
	}
}

void HUD::drawHpMpBars(sf::RenderWindow* w, int const& hp, int const& mp)
{
	for (int i = 0; i < barsSprites.size(); ++i)
	{
		if (barsSprites[i])
		{
			float x_coord = (botPanel->getGlobalBounds().width / 2) + ((botPanel->getGlobalBounds().width / 2) / 2);
			float y_coord = w->getSize().y - ((botPanel->getGlobalBounds().height / (barsSprites.size() + 1)) * (i + 1));
			barsSprites[i]->setPosition(x_coord, y_coord);
										

			//MP bar
			rectForHPMPBars->setFillColor(sf::Color::Blue);
			rectForHPMPBars->setPosition(x_coord - rectForHPMPBars->getSize().x / 2, y_coord);
			if (character)
			{
				rectForHPMPBars->setScale(character->getCurrentMP() / character->getMaxMP(), 1.0);
			}

			//HP bar
			if (i > 0)
			{
				rectForHPMPBars->setFillColor(sf::Color::Red);
				if (character)
				{
					rectForHPMPBars->setScale(character->getCurrentHP() / character->getMaxHP(), 1.0);
				}
			}

			w->draw(*rectForHPMPBars);
			w->draw(*barsSprites[i]);
		}
	}

}

void HUD::addSocket(SocketFunc sFunc, DrawableObject* obj)
{
	HUDSocket* s = new HUDSocket(sFunc, obj);
	allSockets.push_back(s);
}

void HUD::addInSocket(SocketFunc sClass, DrawableObject* obj)
{
	for (HUDSocket* socket : allSockets)
	{
		if (socket && socket->getSocketClass() == sClass)
		{
			socket->setIconToDraw(obj);
		}
	}

}

// Buttons preparation {

void HUD::prepareBtnsForMenu(std::string& _param)
{
	if (_param == "mm")
	{
		Button* b = new Button(ButtonFunction::NEW_GAME, "New game");
		Button* b2 = new Button(ButtonFunction::SETTINGS, "Settings");
		Button* b3 = new Button(ButtonFunction::CLOSE, "Exit");

		btnsOnWindow.push_back(b);
		btnsOnWindow.push_back(b2);
		btnsOnWindow.push_back(b3);
	}
	else if (_param == "st")
	{

	}
	else if (_param == "pa")
	{

	}

}



// Buttons preparation }


// HUD }




// HUDSocket {

HUDSocket::HUDSocket(SocketFunc wcClass, DrawableObject* object)
{
	socketText = new sf::Texture();
	socketText->loadFromFile(PathHUD::PathToHUDResources::pathToHUDSocket);
	socketToDraw = new sf::Sprite(*socketText);

	socketToDraw->setOrigin(socketToDraw->getGlobalBounds().width / 2, socketToDraw->getGlobalBounds().height / 2);

	socketClass = wcClass;

	if (object)
	{
		setIconToDraw(object);
	}

}

void HUDSocket::setSize(sf::Vector2i& newSize)
{
	if (socketToDraw)
	{
		socketToDraw->setScale(newSize.x, newSize.y);

		if (iconToDraw)
		{
			iconToDraw->setScale(newSize.x, newSize.y);
		}
	}
}

void HUDSocket::setPosition(sf::Vector2i& newPos)
{
	if (socketToDraw)
	{
		socketToDraw->setPosition(newPos.x, newPos.y);

		if (iconToDraw)
		{
			iconToDraw->setPosition(newPos.x, newPos.y);
		}
	}
}

void HUDSocket::setPosition(float x, float y)
{
	if (socketToDraw)
	{
		socketToDraw->setPosition(x, y);

		if (iconToDraw)
		{
			iconToDraw->setPosition(x, y);
		}
	}
}

void HUDSocket::drawSocket(sf::RenderWindow* w)
{
	if (socketToDraw)
	{
		w->draw(*socketToDraw);

		if (iconToDraw)
		{
			w->draw(*iconToDraw);
		}
	}
}

void HUDSocket::setIconToDraw(DrawableObject* object)
{
	if (iconToDraw)
	{
		delete iconToDraw;
		iconToDraw = nullptr;
	}

	iconToDraw = new sf::Sprite(*object->getDrawableSprite());
	iconToDraw->setOrigin(iconToDraw->getGlobalBounds().width, iconToDraw->getGlobalBounds().height);
}

HUDSocket::~HUDSocket()
{
	if (socketToDraw)
	{
		delete socketToDraw;
		socketToDraw = nullptr;
	}
	if (socketText)
	{
		delete socketText;
		socketToDraw = nullptr;
	}
	if (iconToDraw)
	{
		delete iconToDraw;
		iconToDraw = nullptr;
	}

}

// HUDSocket }


// Button {

Button::Button()
{
	baseBtnUp = new sf::Texture();
	baseBtnUp->loadFromFile(PathHUD::PathToButtonResources::pathToBtnUp);

	baseBtnDown = new sf::Texture();
	baseBtnDown->loadFromFile(PathHUD::PathToButtonResources::pathToBtnDown);

	buttonShape = new sf::RectangleShape(sf::Vector2f(width, hight));
	buttonShape->setOrigin(width / 2, hight / 2);
	buttonShape->setTexture(baseBtnUp);

	buttonText = new sf::Text();
}

Button::Button(ButtonFunction _bf, const char* _btnText)
{
	bf = _bf;

	baseBtnUp = new sf::Texture();
	baseBtnUp->loadFromFile(PathHUD::PathToButtonResources::pathToBtnUp);

	baseBtnDown = new sf::Texture();
	baseBtnDown->loadFromFile(PathHUD::PathToButtonResources::pathToBtnDown);

	buttonShape = new sf::RectangleShape(sf::Vector2f(width, hight));
	buttonShape->setOrigin(width / 2, hight / 2);
	buttonShape->setTexture(baseBtnUp);

	buttonText = new sf::Text();
	buttonText->setString(_btnText);
}

Button::~Button()
{
	if (buttonShape)
	{
		delete buttonShape;
	}

	if (baseBtnUp)
	{
		delete baseBtnUp;
	}

	if (baseBtnDown)
	{
		delete baseBtnDown;
	}

	if (buttonText)
	{
		delete buttonText;
	}
}


// Text support function {

void Button::setButtonText(std::string const &_text)
{
	if (buttonText)
	{
		buttonText->setString(_text);
	}
}

std::string Button::getButtonText() const
{
	if (!buttonText)
		return "none";


	return buttonText->getString();
}

int Button::getCharacterSize() const
{
	if (!buttonText)
		return 0;

	return buttonText->getCharacterSize();
}

void Button::setCharacterSize(int const& _size)
{
	if (buttonText)
	{
		buttonText->setCharacterSize(_size);
	}
}
	
	// Text support function }


// Base drawable {

void Button::drawOnWindow(sf::RenderWindow* w)
{
	if (buttonShape && w && buttonText)
	{
		buttonShape->setPosition(Xloc, Yloc);
		w->draw(*buttonShape);
	}
}

void Button::setCurrentXYLocation(int xLoc, int yLoc)
{
	Xloc = xLoc;
	Yloc = yLoc;
}

void Button::setCurrentScale(float const& scaleX, float const& scaleY)
{
	if (buttonShape)
	{
		buttonShape->setScale(scaleX, scaleY);
	}
}	
	
	// Base drawable }


// Button }