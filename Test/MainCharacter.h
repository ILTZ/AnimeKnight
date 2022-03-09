#ifndef MAINCHAR_H
#define MAINCHAR_H

#include "CharTemplate.h"
#include "Drawable.h"
#include "WeaponBase.h"


#include <map>
#include <string>
#include <vector>

class MainCharacter : public CharTemplate
{

	WeaponClass curWeap;


// Character death {

	bool isGameContinue = false;

// Character death }




// CharacterTimer {

	sf::Clock characterTimer;

	float currentGameSpeed = 0.f;

	bool checkTimer();

	// Afte switch anim
	virtual void dropTimer() override;

// CharacterTimer }



// Character items {

	std::vector<WeaponBase*> characterArsenal;

	WeaponBase* currentWeapon = nullptr;

	void addWeaponInSocket(DrawableObject* weapon, WeaponClass wClass);

// Character items }


public:

	MainCharacter();

	void getCurrentMagic() const {};

	void getCurrentPoution() const {};





// DrawableObject base func {

	virtual void drawOnWindow(sf::RenderWindow* w) override;

	virtual void setCurrentXYLocation(int xLoc, int yLoc) override {};

	virtual void setCurrentRotation(int rotation) override {};

	virtual void setCurrentScale(float const& scaleX, float const& scaleY) override {};

	virtual sf::Sprite* getDrawableSprite() override { return nullptr; }

// DrawableObject base func }



// CharTemplate base func {

	//virtual void jump(CurrentDirection const& dir, int const &pressRealise) override;

	virtual void attack() override;

	virtual void useAbility(int abilityNum) override;

	virtual void usePoushen(int poushenNum) override;

	virtual void interactiveAction() override;

	virtual void changeWeapon(int const &weaponNum) override;

	virtual WeaponBase* getCurrentWeapon() const override;

	virtual WeaponClass getWeaponClass() const override { return curWeap; }

	virtual void damageEvent(int const& damage) override {};

// CharTemplate base func }




//GET_SET {

	void setDirection(CurrentDirection const& dir) { curDir = dir; }
	CurrentDirection getDirection() const { return curDir; }

	CurrentAnimation getAnimation() const { return curAnim; }
	void setAnimation(CurrentAnimation const& anim) { curAnim = anim; }

	void setCurrentGameSpeed(float const& gameSpeed) { currentGameSpeed = gameSpeed; }

	void setGameStatus(bool const& gameCont) { isGameContinue = gameCont; }

//GET_SET }




	void move(CurrentDirection const& dir);

	void addToCharacterArsenal(WeaponBase* newWeapon);

	void switchWeapon(WeaponClass weaponC);
};



#endif