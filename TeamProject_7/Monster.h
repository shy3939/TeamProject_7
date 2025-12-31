#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Player.h"
#include "Item.h"

class Monster
{
public:
	Monster();

	virtual ~Monster();

	virtual int MosterAttack() = 0;
	virtual void InitRandom() = 0;

	std::string GetMonsterName() const;
	int GetMaxHp() const;
	int GetHp() const;
	int GetATK() const;
	int GetGold() const;
	void SetMaxHp(int maxhp);
	void SetHp(int hp);
	void SetATK(int atk);
	void SetGold(int gold);
	int RandomInRange(int min, int max);


protected:
	std::string monstername_;
	int maxhp_;
	int hp_;
	int atk_;
	int gold_;
	Item* item_;
};