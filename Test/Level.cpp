#include "Level.h"

#define LOG(str) printf("LOG::Level::%s\n", str)

// LevelTile {

LevelTile::LevelTile(const char* pathToSprite)
{
	baseTexture = new sf::Texture();
	baseTexture->loadFromFile(pathToSprite);

	mainTile = new sf::Sprite(*baseTexture);
	mainTile->setOrigin(mainTile->getGlobalBounds().width / 2, mainTile->getGlobalBounds().height / 2);
	setCollisionObject(mainTile);


	LOG("LvlTIle created");

}

LevelTile::~LevelTile()
{
	if (mainTile)
	{
		delete mainTile;
		mainTile = nullptr;
	}
	if (baseTexture)
	{
		delete baseTexture;
		baseTexture = nullptr;
	}
}

void LevelTile::drawOnWindow(sf::RenderWindow* w)
{
	if (mainTile)
	{
		w->draw(*mainTile);
	}
	
	drawCollision(w, mainTile);
}

void LevelTile::setCurrentXYLocation(int xLoc, int yLoc)
{
	if (mainTile)
	{
		mainTile->setPosition(xLoc * mainTile->getGlobalBounds().width, yLoc * mainTile->getGlobalBounds().height);
	}
}

void LevelTile::setCurrentRotation(int rotation)
{
	if (mainTile)
	{
		mainTile->setRotation(rotation);
	}
}

void LevelTile::setCurrentScale(float const& scaleX, float const& scaleY)
{
	if (mainTile)
	{
		mainTile->setScale(scaleX, scaleY);
	}
}

void LevelTile::setTileSprite(sf::Sprite* sprite)
{
	if (mainTile)
	{
		delete mainTile;
		mainTile = nullptr;
	}
	if (baseTexture)
	{
		delete baseTexture;
		baseTexture = nullptr;
	}

	mainTile = new sf::Sprite(*sprite);
	mainTile->setOrigin(mainTile->getGlobalBounds().width / 2, mainTile->getGlobalBounds().height / 2);
	setCollisionObject(mainTile);

}

// LevelTile }




// Level {

Level::~Level()
{
	if (backgroundSprite)
	{
		delete backgroundSprite;
		backgroundSprite = nullptr;
	}
	if (baseBackroundTexture)
	{
		delete baseBackroundTexture;
		baseBackroundTexture = nullptr;
	}
	for (auto obj : lvlObjects)
	{
		delete obj;
	}

}

Level::Level()
{
	sf::Texture* baseGroundText = new sf::Texture();
	baseGroundText->loadFromFile("K:\\PixelSheat\\Knight\\Sprites\\LVLTiles\\mud.png");
	allTexts.push_back(baseGroundText);
	sf::Sprite* baseGroundSprite = new sf::Sprite(*baseGroundText);
	allSprites.insert({ static_cast<std::string>("Ground"), baseGroundSprite });

	sf::Texture* baseRockText = new sf::Texture();
	baseRockText->loadFromFile("K:\\PixelSheat\\Knight\\Sprites\\LVLTiles\\rect_gray.png");
	allTexts.push_back(baseRockText);
	sf::Sprite* baseRockSprite = new sf::Sprite(*baseRockText);
	allSprites.insert({ static_cast<std::string>("Rock"), baseRockSprite });

	//LOG("Lvl was created");

	constructLvl();
}

void Level::drawLevel(sf::RenderWindow* mainWindow)
{
	if (backgroundSprite)
	{
		mainWindow->draw(*backgroundSprite);
	}

	drawBottom(mainWindow);


}

void Level::drawBottom(sf::RenderWindow* w)
{
	int iterator = 0;
	for (int i = 0; i < mapXLength; ++i)
	{
		
		if (taleMap[curRockCount][i] == 'R')
		{
			if (iterator > allLevelTiles.size() - 1)
				return;
			allLevelTiles[iterator]->drawOnWindow(w);
			++iterator;
		}
		if (taleMap[curGroundCount][i] == 'G')
		{
			if (iterator > allLevelTiles.size() - 1)
				return;
			allLevelTiles[iterator]->drawOnWindow(w);
			++iterator;
		}
		
	}
}

void Level::setBackgroundSprite(const char* path)
{
	if (backgroundSprite)
	{
		delete backgroundSprite;
		backgroundSprite = nullptr;
	}
	if (baseBackroundTexture)
	{
		delete baseBackroundTexture;
		baseBackroundTexture = nullptr;
	}


	baseBackroundTexture = new sf::Texture();
	baseBackroundTexture->loadFromFile(path);
	backgroundSprite = new sf::Sprite(*baseBackroundTexture);
}

void Level::addObjectOnLevel(DrawableObject* objectToDraw)
{
	if (objectToDraw)
	{
		lvlObjects.push_back(objectToDraw);
	}
}

void Level::constructLvl()
{
	for (int i = 0; i < mapXLength; ++i)
	{
		if (taleMap[curRockCount][i] == 'R')
		{
			auto temp = allSprites.find("Rock");
			if (temp != allSprites.end())
			{
				LevelTile* tile = new LevelTile();
				tile->setTileSprite(temp->second);
				tile->setCurrentXYLocation(i, floorCount);
				tile->setCollisionPurpose(CollisionPurpose::FLOOR);
				allLevelTiles.push_back(tile);
			}
		}
		if (taleMap[curGroundCount][i] == 'G')
		{
			auto temp = allSprites.find("Ground");
			if (temp != allSprites.end())
			{
				LevelTile* tile = new LevelTile();
				tile->setTileSprite(temp->second);
				tile->setCurrentXYLocation(i, groundCount);
				tile->setCollisionPurpose(CollisionPurpose::FLOOR);
				allLevelTiles.push_back(tile);
			}
		}
	}
}

void Level::clearLvl()
{
	for (auto el : allLevelTiles)
	{
		delete el;
	}
}

// Level }