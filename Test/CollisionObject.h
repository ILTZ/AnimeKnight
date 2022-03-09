#ifndef CO_H
#define CO_H

#include <SFML/Graphics.hpp>
#include <tuple>
#include "Drawable.h"

enum class CollisionPurpose
{
	FLOOR,
	MOVE_BLOCK,
	DAMAGE,
	MAIN_CHARACTER,
	ENEMY,
	NONE
};

enum class CollisionPosition
{
	TOP,
	BOT,
	LEFT,
	RIGHT,
	EMPTY
};


class CollisionObject
{
private:

	bool hideBorder = false;

	CollisionPurpose cPurpose = CollisionPurpose::NONE;

	sf::Mutex* collisionObjectMutex = nullptr;

public:
	CollisionObject();

	virtual ~CollisionObject() {};

	sf::RectangleShape* collisionShape = nullptr;



	virtual void setCollisionObject(sf::Sprite* baseSprite);

	virtual void setCollisionSize(sf::Sprite* baseSprite);

	virtual void setCollisionLocation(sf::Sprite* baseSprite);

	virtual void hideBorderCollsison(bool const& value) { hideBorder = value; };

	virtual void drawCollision(sf::RenderWindow* w, sf::Sprite* baseSprite = nullptr);

	virtual void setCollisionScale(sf::Sprite* baseSprite);

	virtual void setCollisionRotation(sf::Sprite* baseSprite);

	virtual sf::RectangleShape* getCollisionShape() const;

	// Return <true> if other object interact with this object
	virtual std::tuple<bool, CurrentDirection> checkCollisionObject(CollisionObject* otherObject);




	virtual void setCollisionPurpose(CollisionPurpose nPurp) { cPurpose = nPurp; }

	virtual CollisionPurpose getCollisionPurpose() const { return cPurpose; }


	

};


#endif