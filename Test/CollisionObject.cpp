#include "CollisionObject.h"
#include <SFML/Graphics/Color.hpp>

#define LOG(str) printf("CollisionObject::LOG::%str\n", str);

CollisionObject::CollisionObject()
{
	collisionShape = new sf::RectangleShape();

	collisionShape->setOutlineColor(sf::Color::Red);
	collisionShape->setOutlineThickness(5);

	sf::Color color(0, 0, 0, 0);
	collisionShape->setFillColor(color);


	collisionObjectMutex = new sf::Mutex();
}

void CollisionObject::setCollisionObject(sf::Sprite* baseSprite)
{
	if (baseSprite)
	{
		sf::Vector2f size;
		size.x = baseSprite->getGlobalBounds().width;
		size.y = baseSprite->getGlobalBounds().height;

		if (collisionShape)
		{
			delete collisionShape;
			collisionShape = nullptr;
		}
			
		collisionShape = new sf::RectangleShape(size);
		collisionShape->setOrigin(size.x / 2, size.y / 2);
		collisionShape->setOutlineColor(sf::Color::Red);
		collisionShape->setOutlineThickness(5);

		sf::Color color(0, 0, 0, 0);
		collisionShape->setFillColor(color);
	}
}

void CollisionObject::setCollisionSize(sf::Sprite* baseSprite)
{
	sf::Vector2f size;
	size.x = baseSprite->getGlobalBounds().width;
	size.y = baseSprite->getGlobalBounds().height;
	collisionShape->setOrigin(size.x / 2, size.y / 2);

	collisionShape->setSize(size);
	
}

void CollisionObject::setCollisionLocation(sf::Sprite* baseSprite)
{
	collisionShape->setPosition(baseSprite->getPosition());
}

void CollisionObject::setCollisionScale(sf::Sprite* baseSprite)
{
	collisionShape->setScale(baseSprite->getScale());	
}

void CollisionObject::setCollisionRotation(sf::Sprite* baseSprite)
{
	collisionShape->setRotation(baseSprite->getRotation());
}

void CollisionObject::drawCollision(sf::RenderWindow* w, sf::Sprite* baseSprite)
{
	if (w)
	{
		if (baseSprite && collisionShape)
		{
			setCollisionSize(baseSprite);
			setCollisionLocation(baseSprite);
			setCollisionScale(baseSprite);
			setCollisionRotation(baseSprite);


			w->draw(*collisionShape);
		}
	}
}

sf::RectangleShape* CollisionObject::getCollisionShape() const 
{
	if (!collisionShape)
		return nullptr;

	return collisionShape;
}

std::tuple<bool, CurrentDirection> CollisionObject::checkCollisionObject(CollisionObject* otherObject)
{
	

	sf::Vector2f thisPos = collisionShape->getPosition();

	sf::RectangleShape* temp = new sf::RectangleShape(*otherObject->getCollisionShape());
	sf::Vector2f otherPos = temp->getPosition();
	
	
	// Some trubles with multithreading collision handler.....
	
	// Is other left side?
	if	(
			(// Left side check {
				((thisPos.x + collisionShape->getGlobalBounds().width / 2) >= (otherPos.x - temp->getGlobalBounds().width / 2)) &&
				((thisPos.x + collisionShape->getGlobalBounds().width / 2) <= (otherPos.x + temp->getGlobalBounds().width / 2))
			)// Left side check }
		&&
			(// Top/botom check {
				(((thisPos.y - collisionShape->getGlobalBounds().height / 2) <= (otherPos.y + temp->getGlobalBounds().height / 2)) &&
				((thisPos.y - collisionShape->getGlobalBounds().height / 2) >= (otherPos.y - temp->getGlobalBounds().height / 2))) 
				||
				(((thisPos.y + collisionShape->getGlobalBounds().height / 2) >= (otherPos.y - temp->getGlobalBounds().height / 2)) &&
				((thisPos.y + collisionShape->getGlobalBounds().height / 2) <= (otherPos.y + temp->getGlobalBounds().height / 2)))
			)// Top/botom check }
		)
	{
		delete temp;
		return { true, CurrentDirection::LEFT };
	}
	// Is other right side?
	if	(
			(// Right side checl {
				((thisPos.x - collisionShape->getGlobalBounds().width / 2) <= (otherPos.x - temp->getGlobalBounds().width / 2)) &&
				((thisPos.x - collisionShape->getGlobalBounds().width / 2) >= (otherPos.x + temp->getGlobalBounds().width / 2))
			)// Right side checl }
		&&
			(// Top/botop check {
				(((thisPos.y - collisionShape->getGlobalBounds().height / 2) <= (otherPos.y + temp->getGlobalBounds().height / 2)) &&
				((thisPos.y - collisionShape->getGlobalBounds().height / 2) >= (otherPos.y - temp->getGlobalBounds().height / 2))) 
				||
				(((thisPos.y + collisionShape->getGlobalBounds().height / 2) >= (otherPos.y - temp->getGlobalBounds().height / 2)) &&
				((thisPos.y + collisionShape->getGlobalBounds().height / 2) <= (otherPos.y + temp->getGlobalBounds().height / 2)))
			)// Top/botop check }
		)
	{
		delete temp;
		return { true, CurrentDirection::RIGHT };
	}
	// Is other higher?
	if	(
			(// Collision top check {
				((thisPos.y - collisionShape->getGlobalBounds().height / 2) <= (otherPos.y + temp->getGlobalBounds().height / 2)) &&
				((thisPos.y - collisionShape->getGlobalBounds().height / 2) >= (otherPos.y - temp->getGlobalBounds().height / 2))
			)// Collision top check } 
		&&
			(// Left right sides check {
				(((thisPos.x + collisionShape->getGlobalBounds().width / 2) >= (otherPos.x - temp->getGlobalBounds().width / 2)) &&
				((thisPos.x + collisionShape->getGlobalBounds().width / 2) <= (otherPos.x + temp->getGlobalBounds().width / 2))) 
				||
				(((thisPos.x - collisionShape->getGlobalBounds().width / 2) <= (otherPos.x - temp->getGlobalBounds().width / 2)) &&
				((thisPos.x - collisionShape->getGlobalBounds().width / 2) >= (otherPos.x + temp->getGlobalBounds().width / 2)))
			)// Left right sides check }
		)
	{
		delete temp;
		return { true, CurrentDirection::UP };
	}
	// Is other lower?
	if	(
			(// Collision botom check {
				((thisPos.y + collisionShape->getGlobalBounds().height / 2) >= (otherPos.y - temp->getGlobalBounds().height / 2) &&
				(thisPos.y + collisionShape->getGlobalBounds().height / 2) <= (otherPos.y - temp->getGlobalBounds().height / 2))
			)// Collision botom check }
		&&
			(// Left/right collision side across the line of other collision object? {
				(((thisPos.x + collisionShape->getGlobalBounds().width / 2) >= (otherPos.x - temp->getGlobalBounds().width / 2)) &&
				((thisPos.x + collisionShape->getGlobalBounds().width / 2) <= (otherPos.x + temp->getGlobalBounds().width / 2))) 
				||
				(((thisPos.x - collisionShape->getGlobalBounds().width / 2) <= (otherPos.x - temp->getGlobalBounds().width / 2)) &&
				((thisPos.x - collisionShape->getGlobalBounds().width / 2) >= (otherPos.x + temp->getGlobalBounds().width / 2)))
			)// Left/right collision side across the line of other collision object? }
		)
	{
		delete temp;
		return { true, CurrentDirection::BOT };
	}


	
	delete temp;
	return { false, CurrentDirection::NONE };
}
