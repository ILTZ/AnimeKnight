#include "Drawable.h"
#include "WeaponBase.h"

AnimationList::AnimationList(std::string& pathToAnim, int spritesCount)
{

	for (int i = 0; i < spritesCount; ++i)
	{
		sf::Texture* t = new sf::Texture();
		t->loadFromFile(pathToAnim + "\\" + std::to_string(i) + ".png");
		sf::Sprite* s = new sf::Sprite(*t);
		// Set sprite center
		s->setOrigin(s->getGlobalBounds().height / 2, s->getGlobalBounds().width / 2);

		animationList.push_back(s);
		textureList.push_back(t);
	}
}

AnimationList::~AnimationList()
{
	for (int i = 0; i < animationList.size(); ++i)
	{
		if (animationList[i])
		{
			//delete animationList[i];
		}
		animationList.clear();
	}

	for (int i = 0; i < textureList.size(); ++i)
	{
		if (textureList[i])
		{
			//delete textureList[i];
		}
		textureList.clear();
	}
	
}

AnimationList::AnimationList(const std::string& pathToAnim, int spritesCount)
{
	for (int i = 0; i < spritesCount; ++i)
	{
		sf::Texture* t = new sf::Texture();
		t->loadFromFile(pathToAnim + "\\" + std::to_string(i) + ".png");
		sf::Sprite* s = new sf::Sprite(*t);
		// Set sprite center
		s->setOrigin(s->getGlobalBounds().height / 2, s->getGlobalBounds().width / 2);

		animationList.push_back(s);
		textureList.push_back(t);
	}
}

void AnimationList::drawSprite(sf::RenderWindow* w)
{
	if (curDir == CurrentDirection::LEFT)
	{
		animationList[currentAnimCount]->setScale(1, 1);
	}
	else if (curDir == CurrentDirection::RIGHT)
	{
		animationList[currentAnimCount]->setScale(-1, 1);
	}

	animationList[currentAnimCount]->setPosition(xLocation, yLocation);
	w->draw(*animationList[currentAnimCount]);



	
	if (allSocketsPtr.size() > 0)
	{
		for (auto el : allSocketsPtr)
		{

			sf::Vector2i coords = el->getSocketCoord(currentAnimCount);
			int rot = el->getSocketRotation(currentAnimCount);

			auto obj = el->getDrawableObject();

			if (!obj)
				return;

			

			if (curDir == CurrentDirection::LEFT)
			{
				obj->setCurrentRotation(rot);
				obj->setCurrentXYLocation(xLocation + (coords.x /*/ 2*/), yLocation + (coords.y /*/ 2*/));
				obj->setCurrentScale(1.0, 1.0);
			}
			else if (curDir == CurrentDirection::RIGHT)
			{
				obj->setCurrentRotation(-rot);
				obj->setCurrentXYLocation(xLocation + (-(coords.x /*/ 2*/)), yLocation + (coords.y /*/ 2*/));
				obj->setCurrentScale(-1.0, 1.0);
			}
			obj->drawOnWindow(w);
		}
	}
}

void AnimationList::nextSprite()
{
	if ((currentAnimCount >= animationList.size() - 1))
	{
		currentAnimCount = 0;
		doLoop = true;
		return;
	}


	if (loopAnimation && currentAnimCount >= tempAnimCount)
	{
		forwardStep = false;
		backStep = true;
	}
	if (backStep)
	{
		--currentAnimCount;
		if (currentAnimCount == 0)
		{
			backStep = false;
		}
		return;
	}


	++currentAnimCount;
}

void AnimationList::loopOnSprite(const int& spriteCount)
{
	if (spriteCount > animationList.size() - 1)
		return;

	loopAnimation = true;
	tempAnimCount = spriteCount;

}

void AnimationList::dropStopSprite()
{
	loopAnimation = false;
	tempAnimCount = 0;
}

bool AnimationList::isDoCircle()
{
	if (doLoop)
	{
		doLoop = false;
		return true;
	}

	return false;
}

void AnimationList::addWeaponInSocket(DrawableObject* weapon)
{
	if (weapon)
	{
		for(DrawableSocket* s :allSocketsPtr)
		{
			if (s->getPurpose() == SocketName::WEAPON)
			{
				s->setDrawableObject(weapon);
			}
		}
	}
}

sf::Sprite* AnimationList::getCurrentAnimationSprite()
{
	if (animationList.size() < 1)
		return nullptr;

	return animationList[currentAnimCount];
}




//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Socket }

DrawableSocket::DrawableSocket(SocketName sName)
{
	socketName = sName;
}

DrawableSocket::~DrawableSocket()
{
	if (socketObject)
	{
		socketObject = nullptr;
	}
}

sf::Vector2i DrawableSocket::getSocketCoord(int const& coordCount) const
{
	return coordsVectorLeft[coordCount];
}

int DrawableSocket::getSocketRotation(int const& rotCount) const
{
	return rotationVectorLeft[rotCount];
}

// Socket }
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
