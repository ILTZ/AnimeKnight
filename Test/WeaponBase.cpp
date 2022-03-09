#include "WeaponBase.h"

WeaponBase::WeaponBase(const char* pathToTexture, WeaponClass wClass)
{
	baseTexture = new sf::Texture();
	baseTexture->loadFromFile(pathToTexture);

	weaponSprite = new sf::Sprite(*baseTexture);
	weaponSprite->setOrigin(weaponSprite->getGlobalBounds().width / 2, weaponSprite->getGlobalBounds().height / 2);

	originWeaponSprite = new sf::Sprite(*baseTexture);
	originWeaponSprite->setScale(0.5, 0.5);
	originWeaponSprite->setOrigin(originWeaponSprite->getGlobalBounds().width / 2, weaponSprite->getGlobalBounds().height / 2);


	weaponType = wClass;

	setCollisionObject(weaponSprite);
}

WeaponBase::~WeaponBase()
{
	delete weaponSprite;
	delete originWeaponSprite;
	delete baseTexture;

	delete this;
}

void WeaponBase::drawWeapon(sf::RenderWindow* window, int const &xLoc, int const &yLoc)
{
	if (weaponSprite && window)
	{
		weaponSprite->setPosition(xLoc, yLoc);
		window->draw(*weaponSprite);

		drawCollision(window, weaponSprite);
	}

}

void WeaponBase::drawOnWindow(sf::RenderWindow* w)
{
	if (w)
	{
		drawWeapon(w, curXLocation, curYLocation);
	}
}

void WeaponBase::setCurrentXYLocation(int xLoc, int yLoc)
{
	curXLocation = xLoc;
	curYLocation = yLoc;

	
}

void WeaponBase::setCurrentRotation(int rotation)
{
	if (weaponSprite)
	{
		weaponSprite->setRotation(rotation);
	}

}

void WeaponBase::setOriginForSprite(float const& x, float const& y)
{
	if (weaponSprite)
	{
		weaponSprite->setOrigin(x, y);
	}
}

void WeaponBase::setCurrentScale(float const& scaleX, float const& scaleY)
{
	if (weaponSprite)
	{
		weaponSprite->setScale(scaleX, scaleY);
	}


}

sf::Sprite* WeaponBase::getDrawableSprite()
{
	if (originWeaponSprite)
	{
		return originWeaponSprite;
	}

	return nullptr;
}