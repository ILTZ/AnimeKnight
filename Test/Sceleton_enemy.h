#pragma once
#include "CharTemplate.h"



class Sceleton_enemy : public CharTemplate
{
private:



public:
	Sceleton_enemy() {};

	virtual ~Sceleton_enemy() {};




// Drawable base func {

	virtual void drawOnWindow(sf::RenderWindow* w) {};

	virtual void setCurrentXYLocation(int xLoc, int yLoc) {};

	virtual void setCurrentRotation(int rotation) {};

	virtual void setCurrentScale(float const& scaleX, float const& scaleY) {};

	virtual sf::Sprite* getDrawableSprite() {};

// Drawable base func }




// Char template base func {

	virtual void moveToSomeSide(CurrentDirection const& dir) {};
	
	virtual void jump(CurrentDirection const& dir, int const& pressRealise) {};

	virtual void attack() {};

	virtual void useAbility(int abilityNum) {};

	virtual void usePoushen(int poushenNum) {};

	virtual void interactiveAction() {};

	virtual void changeWeapon(int const& weaponNum) {};

	virtual WeaponBase* getCurrentWeapon() const {};

	virtual WeaponClass getWeaponClass() const {};

	virtual void dropTimer() {};

	virtual void damageEvent(int const& damage) {};

// Char template base func }




private:


};

