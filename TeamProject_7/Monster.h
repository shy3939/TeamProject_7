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
	virtual void TakeDamage(int damage_) = 0;
	virtual void InitRandom() = 0;

	//getter
	std::string GetName() const;
	int GetMaxHP() const;
	int GetHP() const;
	int GetATK() const;
	int GetGold() const;

	//setter
	void SetMaxHP(int maxhp);
	void SetHP(int hp);
	void SetATK(int atk);
	void SetGold(int gold);

	int RandomInRange(int min, int max);

	Monster* CreateRandomMonster(Player& player);


protected:
	std::string name_;
	int maxhp_;
	int hp_;
	int atk_;
	int gold_;
	Item* item_;
	Player* player_;
};