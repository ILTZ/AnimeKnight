#ifndef CHAR_T_H
#define CHAR_T_H

#include <map>
#include "Drawable.h"
#include "WeaponBase.h"
#include "CollisionObject.h"

#include <vector>

enum class CurrentAnimation
{
	IDLE,
	RUN,
	JUMP,
	ATTACK,
	DEATH
};

enum class CurrentWeapon
{
	SWORD,
	LANCE,
	ARROW,
	GUN,
	FIST,
	AXE
};





class CharTemplate : public CollisionObject, public DrawableObject
{
public:

	CharTemplate() {};
	
	virtual ~CharTemplate() {};




	virtual void moveToSomeSide(CurrentDirection const& dir);
	// If 1 - press, if 0 - realise
	virtual void jump(CurrentDirection const& dir, int const &pressRealise);

	virtual void attack() = 0;

	virtual void useAbility(int abilityNum) = 0;

	virtual void usePoushen(int poushenNum) = 0;

	virtual void interactiveAction() = 0;

	virtual void changeWeapon(int const& weaponNum) = 0;

	virtual WeaponBase* getCurrentWeapon() const = 0;

	virtual WeaponClass getWeaponClass() const = 0;

	virtual void dropTimer() = 0;

	virtual void damageEvent(int const& damage) = 0;




// DefaultSockets {

	DrawableSocket leftHand{ SocketName::LEFT_HAND };

	DrawableSocket rightHand{ SocketName::RIGHT_HAND };

// DefaultSockets }




// Animations {

	AnimationList animations;

	std::map<std::string, AnimationList> animationVector;

	std::map<std::string, AnimationList*> animVec;

	CurrentAnimation curAnim;

	CurrentDirection curDir;

// Animations }




// Base prop {

	const int maxHitPoints{ 100 };

	int currentHitPotints{ maxHitPoints };

	const int maxManaPoints{ 100 };

	int currentManaPoints{ maxManaPoints };

	int curXLocation = 400;

	int curYLocation = 300;

	std::vector<CurrentDirection> lockDirections;


	// Const movement {
	const int stepLength{ 3 };

	const int maxJumpHeight{ 200 };

	const int jumpStep{ 3 };

	int currentJumpHeight = 0;
	// Const movement }

	virtual void toFallCont();

	bool firstFall = false;

	bool toFall = true;

// Base prop }




// Base get/set {

	virtual int getCurrentHP() const { return currentHitPotints; }
	virtual int getMaxHP() const { return maxHitPoints; }

	virtual int getCurrentMP() const { return currentManaPoints; }
	virtual int getMaxMP() const { return maxManaPoints; }

	virtual void lockMovement(CurrentDirection nLockDirection) { lockDirections.push_back(nLockDirection); }
	virtual void unlockMovement() { lockDirections.clear(); }

	CurrentAnimation getAnimation() const { return curAnim; }
	void setAnimation(CurrentAnimation const& anim) { curAnim = anim; }

// Base get/set }


// Base Drawable func {



// Base Drawable func }



};






#endif // !CHAR_T_H