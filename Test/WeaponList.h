#ifndef WEAPONL_H
#define WEAPONL_H

#include "WeaponBase.h"


class Sword : public WeaponBase
{
private:


public:
	Sword(const char* pathToTexture, WeaponClass wClass) : WeaponBase(pathToTexture, wClass) {};

	virtual ~Sword() {};



private:

};


class Lance : public WeaponBase
{
public:
	Lance(const char* pathToTexture, WeaponClass wClass) : WeaponBase(pathToTexture, wClass) {};

	virtual ~Lance() {};


};


class Gun : public WeaponBase
{
public:
	Gun(const char* pathToTexture, WeaponClass wClass) : WeaponBase(pathToTexture, wClass) {};

	virtual ~Gun() {};
};


class Bow : public WeaponBase
{
public:
	Bow(const char* pathToTexture, WeaponClass wClass) : WeaponBase(pathToTexture, wClass) {};

	virtual ~Bow() {};
};


class Axe : public WeaponBase
{
public:
	Axe(const char* pathToTexture, WeaponClass wClass) : WeaponBase(pathToTexture, wClass) {};

	virtual ~Axe() {};



};


#endif

