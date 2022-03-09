#ifndef WEAPONBASE_H
#define WEAPONBASE_H

#include "Drawable.h"
#include "PicableItem.h"
#include "CollisionObject.h"

enum class WeaponClass
{
	SWORD,
	BOW,
	GUN,
	LANCE,
	AXE,
	FIST,
	NONETYPE,
};


class WeaponBase : public DrawableObject, public PicableItem, public CollisionObject
{
private:
	
	float baseDamage = 0.f;

	float baseDelay = 0.f;

	int curXLocation = 0;
	int curYLocation = 0;

	WeaponClass weaponType = WeaponClass::NONETYPE;







	sf::Sprite* weaponSprite = nullptr;

	sf::Sprite* originWeaponSprite = nullptr;

	sf::Texture* baseTexture = nullptr;

public:
	WeaponBase(const char* pathToTexture, WeaponClass wClass);

	virtual ~WeaponBase();




// Get\Set {

	WeaponClass getWeaponType() const { return weaponType; }
	void setWeaponType(WeaponClass const& nClass) { weaponType = nClass; }

	float getBaseDamage() const { return baseDamage; }
	void setBaseDamage(const float& nDamage) { baseDamage = nDamage; }

	// Delay betwen attack
	float getBaseDeleay() const { return baseDelay; }
	void setBaseDelay(float const& nDeleay) { baseDelay = nDeleay; }

	void setXYLocation(int const& nXLoc, int const& nYLoc) { curXLocation = nXLoc, curYLocation = nYLoc; }

	void setOriginForSprite(float const& x, float const& y);

	

// Get\Set }




	void drawWeapon(sf::RenderWindow* window, int const &xLoc, int const &yLoc);



// Drawable base func {

	virtual void drawOnWindow(sf::RenderWindow* w) override;

	virtual void setCurrentXYLocation(int xLoc, int yLoc) override;

	virtual void setCurrentRotation(int rotation) override;

	virtual void setCurrentScale(float const& scaleX, float const& scaleY) override;

	virtual sf::Sprite* getDrawableSprite() override;

// Drawable base func }


private:



};



#endif
