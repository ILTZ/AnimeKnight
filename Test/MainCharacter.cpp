#include "MainCharacter.h"
#include "WeaponList.h"

#define LOG(str,str2) printf("MainCharacter::LOG::%s::%i\n", str, str2)


MainCharacter::MainCharacter()
{
	curAnim = CurrentAnimation::IDLE;
	curDir = CurrentDirection::LEFT;

	// Check the problem with fucking delay!!!
 
// Move animations {

	std::string pTIdle = "K:\\PixelSheat\\Knight\\Sprites\\MainChar\\Idle";
	std::string pTWalk = "K:\\PixelSheat\\Knight\\Sprites\\MainChar\\Walking";
	std::string pTJump = "K:\\PixelSheat\\Knight\\Sprites\\MainChar\\jump_rot";

	animationVector.insert({ static_cast<std::string>("idle"), AnimationList(pTIdle, 5) });
	animationVector.insert({ static_cast<std::string>("run"), AnimationList(pTWalk, 5) });
	animationVector.insert({ static_cast<std::string>("jump"), AnimationList(pTJump, 3) });

// Move animations }

	std::vector<sf::Vector2i> coordVector;
	std::vector<int> rotateVector;

// Attack animation {

	std::string pTPunch = "K:\\PixelSheat\\Knight\\Sprites\\MainChar\\fist_attack";
	std::string pTSword = "K:\\PixelSheat\\Knight\\Sprites\\MainChar\\sword_attack";
	std::string pTAxe = "K:\\PixelSheat\\Knight\\Sprites\\MainChar\\axe_attack";
	std::string pTLance = "K:\\PixelSheat\\Knight\\Sprites\\MainChar\\lance_attack";
	std::string pTGun = "K:\\PixelSheat\\Knight\\Sprites\\MainChar\\gun_attack";

	// Sword attack {

	AnimationList swordAttack(pTSword, 3);
	
		// Sword socket {

		DrawableSocket weapon_socket_sword(SocketName::WEAPON);
		coordVector.clear();
		coordVector.push_back(sf::Vector2i(-75, -50));
		coordVector.push_back(sf::Vector2i(-80, 100));
		coordVector.push_back(sf::Vector2i(-90, 90));

		rotateVector.clear();
		rotateVector.push_back(45);
		rotateVector.push_back(-80);
		rotateVector.push_back(-70);

		weapon_socket_sword.setCoordsVector(coordVector);
		weapon_socket_sword.setRotationVector(rotateVector);
		swordAttack.addSocket(weapon_socket_sword);

		// Sword socket }

	animationVector.insert({ static_cast<std::string>("sword_attack"), swordAttack/*AnimationList(pTSword, 3)*/});

	// Sword attack }




	// Fist attack {

	animationVector.insert({ static_cast<std::string>("fist_attack"), AnimationList(pTPunch, 3) });

	// Fist attack }

	


	// Axe attack {

	AnimationList axeAttack(pTAxe, 3);

		// Axe socket {

		DrawableSocket weapon_socket_axe(SocketName::WEAPON);
		coordVector.clear();
		coordVector.push_back(sf::Vector2i(70, 50));
		coordVector.push_back(sf::Vector2i(-100, 20));
		coordVector.push_back(sf::Vector2i(-100, 20));

		rotateVector.clear();
		rotateVector.push_back(180);
		rotateVector.push_back(-25);
		rotateVector.push_back(-20);

		weapon_socket_axe.setCoordsVector(coordVector);
		weapon_socket_axe.setRotationVector(rotateVector);
		axeAttack.addSocket(weapon_socket_axe);

		// Axe socket }

	animationVector.insert({ static_cast<std::string>("axe_attack"), axeAttack});

	// Axe attack }




	// Lance attack {

	AnimationList lanceAttack(pTLance, 3);

		// Lance socket {
		
		DrawableSocket weapon_socket_lance(SocketName::WEAPON);
		coordVector.clear();
		coordVector.push_back(sf::Vector2i(-20, -40));
		coordVector.push_back(sf::Vector2i(-100, 70));
		coordVector.push_back(sf::Vector2i(-100, 70));

		rotateVector.clear();
		rotateVector.push_back(45);
		rotateVector.push_back(-80);
		rotateVector.push_back(-78);

		weapon_socket_lance.setCoordsVector(coordVector);
		weapon_socket_lance.setRotationVector(rotateVector);
		lanceAttack.addSocket(weapon_socket_lance);

		// Lance socket }

	animationVector.insert({ static_cast<std::string>("lance_attack"), lanceAttack});

	// Lance attack }




	// Gun attack {

	AnimationList gunAttack(pTGun, 3);

		// Gun socket {

		// Gun socket }

	animationVector.insert({ static_cast<std::string>("gun_attack"), gunAttack });

	// Gun attack }




// Attack animation }


	Axe* baseAxe = new Axe("K:\\PixelSheat\\Knight\\Sprites\\WeaponSprites\\w_axe_war22.png", WeaponClass::AXE);
	addToCharacterArsenal(baseAxe);

	Lance* baseLance = new Lance("K:\\PixelSheat\\Knight\\Sprites\\WeaponSprites\\w_pike_base2.png", WeaponClass::LANCE);
	addToCharacterArsenal(baseLance);

	Sword* baseSword = new Sword("K:\\PixelSheat\\Knight\\Sprites\\WeaponSprites\\w_ugs_base2.png", WeaponClass::SWORD);
	addToCharacterArsenal(baseSword);


	curWeap = WeaponClass::SWORD;
	currentWeapon = baseSword;

	characterTimer.restart();
}


void MainCharacter::drawOnWindow(sf::RenderWindow* w) 
{
	

	std::string findKey = "";
	
	// Set current animation {
	switch (curAnim)
	{

	case CurrentAnimation::IDLE:
		{findKey = "idle";}
		break;

	case CurrentAnimation::RUN:
		{findKey = "run";}
		break;

	case CurrentAnimation::JUMP:
		{findKey = "jump";}
		break;


			// AttackAnimations {
			case CurrentAnimation::ATTACK:
				switch (curWeap)
				{
				case WeaponClass::FIST:
				{findKey = "fist_attack"; }break;

				case WeaponClass::BOW:
				{findKey = "arrow_attack"; } break;

				case WeaponClass::GUN:
				{findKey = "gun_attack"; } break;

				case WeaponClass::LANCE:
				{findKey = "lance_attack"; }break;

				case WeaponClass::SWORD:
				{findKey = "sword_attack"; }break;

				case WeaponClass::AXE:
				{findKey = "axe_attack"; } break;

				}
				break;
			// AttackAnimations }


	case CurrentAnimation::DEATH:
		{findKey = "death";}
		break;

	default:

			break;
	}
	// Set current animation }


	auto temp = animationVector.find(findKey);
	if (temp != animationVector.end())
	{
		// Attack animation get stuck without it {
		if (curAnim == CurrentAnimation::ATTACK)
		{
			if (temp->second.isDoCircle())
			{
				curAnim = CurrentAnimation::IDLE;
				return;
			}
		}
		// Attack animation get stuck without it }


		toFallCont();

		temp->second.setDirection(curDir);
		temp->second.setXYLocation(curXLocation, curYLocation);
		temp->second.drawSprite(w);
		drawCollision(w, temp->second.getCurrentAnimationSprite());

		

		if (checkTimer())
		{
			temp->second.nextSprite();
		}
	}

}

void MainCharacter::move(CurrentDirection const& dir)
{
	if (dir == CurrentDirection::LEFT)
	{
		curDir = dir;
		curXLocation -= stepLength;

		if (curAnim == CurrentAnimation::JUMP)
			return;


		if (curAnim != CurrentAnimation::ATTACK)
			setAnimation(CurrentAnimation::RUN);
	}
	else if (dir == CurrentDirection::RIGHT)
	{
		curDir = dir;
		curXLocation += stepLength;

		if (curAnim == CurrentAnimation::JUMP)
			return;

		if (curAnim != CurrentAnimation::ATTACK)
			setAnimation(CurrentAnimation::RUN);
	}
	else if (dir == CurrentDirection::STAY)
	{
		setAnimation(CurrentAnimation::IDLE);	
	}

	LOG("<move>", curXLocation);
}

bool MainCharacter::checkTimer()
{
	if (characterTimer.getElapsedTime().asSeconds() >= currentGameSpeed && isGameContinue)
	{
		characterTimer.restart();
		return true;
	}

	return false;
}

void MainCharacter::dropTimer()
{
	characterTimer.restart();
}

// CahrTamplate base func {


void MainCharacter::attack()
{
	curAnim = CurrentAnimation::ATTACK;
}

void MainCharacter::useAbility(int abilityNum)
{

}

void MainCharacter::usePoushen(int poushenNum)
{

}

void MainCharacter::interactiveAction()
{

}

void MainCharacter::changeWeapon(int const &weaponNum)
{
	switch (weaponNum)
	{
	case 1:
		switchWeapon(WeaponClass::SWORD);
		break;

	case 2:
		switchWeapon(WeaponClass::LANCE);
		break;

	case 3:
		switchWeapon(WeaponClass::AXE);
		break;

	case 4:
		switchWeapon(WeaponClass::FIST);
		break;


	default:
		break;
	} 
}

WeaponBase* MainCharacter::getCurrentWeapon() const
{
	return currentWeapon;
}

// CahrTamplate base func }

void MainCharacter::addToCharacterArsenal(WeaponBase* newWeapon)
{
	if (newWeapon)
	{
		characterArsenal.push_back(newWeapon);

		addWeaponInSocket(newWeapon, newWeapon->getWeaponType());
	}
}

void MainCharacter::addWeaponInSocket(DrawableObject* weapon, WeaponClass wClass)
{
	if (!weapon)
		return;

	std::string findKey = "";

	switch (wClass)
	{
	case (WeaponClass::AXE):
		findKey = "axe_attack";
		break;

	case (WeaponClass::BOW):
		findKey = "bow_attack";
		break;

	case (WeaponClass::GUN):
		findKey = "gun_attack";
		break;

	case (WeaponClass::LANCE):
		findKey = "lance_attack";
		break;

	case (WeaponClass::SWORD):
		findKey = "sword_attack";
		break;

	default:

		break;
	} 

	auto animList = animationVector.find(findKey);
	if (animList != animationVector.end())
	{
		animList->second.addWeaponInSocket(weapon);
	}

}

void MainCharacter::switchWeapon(WeaponClass weaponC)
{
	for (auto weapon : characterArsenal)
	{
		if (weapon && weapon->getWeaponType() == weaponC)
		{
			currentWeapon = weapon;
			curWeap = weaponC;
		}
	}
}