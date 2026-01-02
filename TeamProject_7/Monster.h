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

	virtual int MonsterATK() = 0;
	virtual void InitRandom() = 0;

	std::string GetName() const;
	int GetMaxHP() const;
	int GetHP() const;
	int GetATK() const;
	int GetGold() const;


	void SetMaxHP(int maxhp);
	void SetHP(int hp);
	void SetATK(int atk);
	void SetGold(int gold);

	int RandomInRange(int min, int max);


protected:
	std::string name_;
	int maxhp_;
	int hp_;
	int atk_;
	int gold_;
	Item* item_;
};