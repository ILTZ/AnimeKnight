#include "HUD.h"

#define LOG(str) printf("HUD::%s\n", str)

// HUD {

HUD::HUD()
{
	const char* pathToPanel = "K:\\PixelSheat\\Knight\\HUD\\HUD_bot_panel.png";
	const char* pathToBar = "K:\\PixelSheat\\Knight\\HUD\\hud_bar2.png";

	sf::Texture* t = new sf::Texture();
	t->loadFromFile(pathToPanel);
	botPanel = new sf::Sprite(*t);

	allTextures.push_back(t);


	sf::Texture* t2 = new sf::Texture();
	t2->loadFromFile(pathToBar);

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

// HUD }




// HUDSocket {

HUDSocket::HUDSocket(SocketFunc wcClass, DrawableObject* object)
{
	const char* pathToDefaultSocketPanel = "K:\\PixelSheat\\Knight\\HUD\\bot_panel_socket.png";

	socketText = new sf::Texture();
	socketText->loadFromFile(pathToDefaultSocketPanel);
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