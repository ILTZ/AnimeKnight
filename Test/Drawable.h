#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <string>



class DrawableObject;


enum class CurrentDirection
{
	UP,
	BOT,
	RIGHT,
	LEFT,
	STAY,
	NONE
};

enum class SocketName
{
	LEFT_HAND,
	RIGHT_HAND,
	LEFT_LEG,
	RIGHT_LEG,
	CHEST,
	BACK,
	HEAD,
	EMPTY,

	WEAPON,

};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Need to attach some objects (like sword or bow) to characters

// Socket for some objets {

class DrawableSocket
{
private:

	SocketName socketName = SocketName::EMPTY;

	std::vector<sf::Vector2i> coordsVectorLeft;
	std::vector<sf::Vector2i> coordVectorRight;

	std::vector<int> rotationVectorLeft;
	std::vector<int> rotationVectorRight;


	DrawableObject* socketObject = nullptr;
;

public:

	DrawableSocket(SocketName sName = SocketName::EMPTY);

	~DrawableSocket();


	sf::Vector2i getSocketCoord(int const& coordCount) const;
	int getSocketRotation(int const& rotCount) const;


	void setCoordsVector(std::vector<sf::Vector2i> const& nCoords) { coordsVectorLeft = nCoords; }
	void setRotationVector(std::vector<int> const& nRotation) { rotationVectorLeft = nRotation; }



	DrawableObject* getDrawableObject() const { return socketObject; }
	void setDrawableObject(DrawableObject* socketObj) { socketObject = socketObj; }

	SocketName getPurpose() const { return socketName; }
	void setPurpose(SocketName purpose) { socketName = purpose; }
};

// Socket for some objets }
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Animation list {
class AnimationList
{
public:

	std::vector<DrawableSocket> allSockets;

	std::vector<DrawableSocket*> allSocketsPtr;

	AnimationList(std::string &pathToAnim, int spritesCount);

	AnimationList(const std::string& pathToAnim, int spritesCount);

	AnimationList() {};

	~AnimationList();



	void drawSprite(sf::RenderWindow* w);

	void setXYLocation(const int xLoc, const int yLoc) { xLocation = xLoc; yLocation = yLoc; }

	void nextSprite();

	void setDirection(CurrentDirection const& direction) { curDir = direction; }

	void loopOnSprite(const int& spriteCount);

	void dropStopSprite();

	// Was draw all sprites in array 1 time?
	bool isDoCircle();

	bool doLoop = false;

	void addSocket(DrawableSocket& nSocket) { allSockets.push_back(nSocket); }

	void addSocket(DrawableSocket* nSocket) { allSocketsPtr.push_back(nSocket); }

	void addWeaponInSocket(DrawableObject* weapon);

	sf::Sprite* getCurrentAnimationSprite();

private:

	int currentAnimCount = 0;

	int tempAnimCount = 0;

	bool loopAnimation = false;

	bool forwardStep = false;

	bool backStep = false;

	std::vector<sf::Sprite*> animationList;

	std::vector<sf::Texture*> textureList;

	int xLocation = 0;

	int yLocation = 0;

	CurrentDirection curDir = CurrentDirection::STAY;


};
// Animation list }
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Drawable object base class {
class DrawableObject
{
public:

	DrawableObject() {};
	
	virtual ~DrawableObject() {};

	virtual void drawOnWindow(sf::RenderWindow* w) = 0;

	virtual void setCurrentXYLocation(int xLoc, int yLoc) = 0;

	virtual void setCurrentRotation(int rotation) = 0;

	virtual void setCurrentScale(float const& scaleX, float const& scaleY) = 0;

	virtual sf::Sprite* getDrawableSprite() = 0;



};
// Drawable object base class {
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////



#endif