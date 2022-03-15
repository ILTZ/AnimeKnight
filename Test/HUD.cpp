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
		
		const std::string pathToFont	= getCurrentAssetsDirectory() + "HUD\\Fonts\\Game_Of_Squids.ttf";
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
	supMutex = new sf::Mutex();

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

	prepareBtnsForMenu(static_cast<std::string>("mm"));
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
	if (supMutex)
	{
		delete supMutex;
		supMutex = nullptr;
	}
}

void HUD::drawOnWindow(sf::RenderWindow* w)
{

	drawGameHud(w);
	drawMainMenu(w);

	switch (currentGameMode)
	{
	

	default:
		break;
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
			btnsOnWindow[i]->setCurrentXYLocation(w->getSize().x / 2,
				((w->getSize().y / 2) / (btnsOnWindow.size()) * (i + 1)));
			
			btnsOnWindow[i]->drawOnWindow(w);
		}
	}
}

void HUD::drawPauseMenu(sf::RenderWindow* w)
{
	if (w && btnsOnWindow.size() > 0)
	{
		for (int i = 0; i < btnsOnWindow.size(); ++i)
		{
			btnsOnWindow[i]->setCurrentXYLocation(w->getSize().x / 2,
				((w->getSize().y / 2) / (btnsOnWindow.size()) * (i + 1)));

			btnsOnWindow[i]->drawOnWindow(w);
		}
	}
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

// Buttons {

void HUD::prepareBtnsForMenu(std::string const &_param)
{
	if (_param == "mm")
	{
		Button* b = new Button(BtnFunc::BtnFunc::MM_NEW_GAME, "New game");
		Button* b2 = new Button(BtnFunc::BtnFunc::MM_SETTING, "Settings");
		Button* b3 = new Button(BtnFunc::BtnFunc::MM_EXIT, "Exit");

		supMutex->lock();
		btnsOnWindow.clear();

		btnsOnWindow.push_back(b);
		btnsOnWindow.push_back(b2);
		btnsOnWindow.push_back(b3);

		supMutex->unlock();
	}
	else if (_param == "st")
	{

	}
	else if (_param == "pa")
	{
		Button* b = new Button(BtnFunc::BtnFunc::PA_CONTINUE, "Continue");
		Button* b2 = new Button(BtnFunc::BtnFunc::PA_BACK_TO_MAIN_MENU, "Main Menu");
		Button* b3 = new Button(BtnFunc::BtnFunc::PA_SAVE, "Save");
		Button* b4 = new Button(BtnFunc::BtnFunc::PA_EXIT, "Exit");

		supMutex->lock();
		btnsOnWindow.clear();

		btnsOnWindow.push_back(b);
		btnsOnWindow.push_back(b2);
		btnsOnWindow.push_back(b3);
		btnsOnWindow.push_back(b4);

		supMutex->unlock();

	}

}

void HUD::clearBtnsStorage()
{
	if (btnsOnWindow.size() > 0)
	{
		btnsOnWindow.clear();
	}
}

bool HUD::checkMouseClickOnButton(sf::Vector2i const& _mousePosition)
{
	for (Button* btn : btnsOnWindow)
	{
		if (!btn)
			continue;

		if (btn->checkMouseClick(_mousePosition))
		{
			return true;
		}
	}

	return false;
}

std::tuple<bool, BtnFunc::BtnFunc> HUD::dropIsClickedButoonStatus() const&
{
	BtnFunc::BtnFunc tempFucnc = BtnFunc::BtnFunc::NONE;

	for (Button* btn : btnsOnWindow)
	{
		if (!btn)
			continue;

		if (btn->getBtnIsPressedStatus())
		{
			btn->setBtnIsPressed(false);
			tempFucnc = btn->getBtnFunction();

			return std::make_tuple(true, tempFucnc);
		}
	}
	return std::make_tuple(false, tempFucnc);
}

// Buttons }


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
	buttonShape->setOrigin(width / 2.0, hight / 2.0);
	buttonShape->setTexture(baseBtnUp);

	buttonText = new sf::Text();
	textFont.loadFromFile(PathHUD::PathToButtonResources::pathToFont);
	buttonText->setFont(textFont);
	buttonText->setFillColor(sf::Color::Black);
}

Button::Button(BtnFunc::BtnFunc _bf, const char* _btnText) : Button()
{

	buttonFunction = _bf;
	//buttonText = new sf::Text();
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

bool Button::checkMouseClick(sf::Vector2i const &mousePos)
{
	if (buttonShape)
	{
		int xl = (buttonShape->getPosition().x + (buttonShape->getGlobalBounds().width / 2));
		int sr = (buttonShape->getPosition().x - (buttonShape->getGlobalBounds().width / 2));
		int hb = (buttonShape->getPosition().y + (buttonShape->getGlobalBounds().height / 2));
		int hu = (buttonShape->getPosition().y - (buttonShape->getGlobalBounds().height / 2));

		if ((mousePos.x <= (buttonShape->getPosition().x + (buttonShape->getGlobalBounds().width / 2)))
			&&
			(mousePos.x >= (buttonShape->getPosition().x - (buttonShape->getGlobalBounds().width / 2)))
			&&
			(mousePos.y <= (buttonShape->getPosition().y + (buttonShape->getGlobalBounds().height / 2)))
			&&
			(mousePos.y >= (buttonShape->getPosition().y - (buttonShape->getGlobalBounds().height / 2)))
			)
		{
			isPressed = true;
			return true;
		}
	}

	return false;
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
		buttonText->setOrigin(buttonText->getGlobalBounds().width / 2, buttonText->getGlobalBounds().height / 2);
		buttonShape->setPosition(Xloc, Yloc);

		if (!isPressed)
		{
			buttonShape->setTexture(baseBtnUp);
			buttonText->setPosition(Xloc, Yloc - 10);
		}
		else
		{
			buttonShape->setTexture(baseBtnDown);
			buttonText->setPosition(Xloc, Yloc + 8.0);
		}

		

		

		w->draw(*buttonShape);
		w->draw(*buttonText);
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