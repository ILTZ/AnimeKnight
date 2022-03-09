#ifndef LEVEL_H
#define LEVEL_H

#include "Drawable.h"
#include "CollisionObject.h"

class LevelTile : public DrawableObject, public CollisionObject
{
private:

	sf::Sprite* mainTile = nullptr;

	sf::Texture* baseTexture = nullptr;

public:
	LevelTile() {};

	LevelTile(const char* pathToSprite);

	~LevelTile();


	// Drawable base func {

	virtual void drawOnWindow(sf::RenderWindow* w) override;

	virtual void setCurrentXYLocation(int xLoc, int yLoc) override;

	virtual void setCurrentRotation(int rotation) override;

	virtual void setCurrentScale(float const& scaleX, float const& scaleY) override;

	virtual sf::Sprite* getDrawableSprite() override { return nullptr; }

	// Drawable base func }

	void setTileSprite(sf::Sprite* sprite);

private:

	

};


class Level
{
private:

	std::vector<DrawableObject*> lvlObjects;

	std::map<std::string, sf::Sprite*> allSprites;

	//Tiles placed on game field
	std::vector<LevelTile*> allLevelTiles;
	
	std::vector < sf::Texture*> allTexts;

	

	sf::Sprite* backgroundSprite = nullptr;

	sf::Texture* baseBackroundTexture = nullptr;

	const char* taleMap[20] ={
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR",
	"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"////////////////////////////////" ,
	"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR" ,
	"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG" ,
	"////////////////////////////////",
	"////////////////////////////////" };

	int curRockCount = 0;
	int curGroundCount = 1;

	const int floorCount = 16;
	const int groundCount = 17;
	const int mapXLength = 33;


public:
	Level();

	~Level();


	void drawLevel(sf::RenderWindow* mainWindow);

	void setBackgroundSprite(const char* pathToSprite);

	void addObjectOnLevel(DrawableObject* objectToDraw);

	void constructLvl();

	void clearLvl();

	std::vector<LevelTile*> getAllLevelTilesArray() { return allLevelTiles; }






private:

	void drawBottom(sf::RenderWindow* w);

};




#endif