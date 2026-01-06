#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Player.h"
#include "ItemEnum.h"

class Monster
{
public:
	Monster();
	virtual ~Monster();
	
	virtual void TakeDamage(int damage_) = 0;
	virtual void InitRandom() = 0;
	

	
	//getter
	std::string GetName() const;
	int GetMaxHP() const;
	int GetHP() const;
	int GetATK() const;
	int GetGold() const;
	int GetSTR() const;
	int GetAGI() const;
	int GetVIT() const;
	int GetINT() const;
	int GetLUK() const;
	
	//setter
	void SetMaxHP(int maxhp);
	void SetHP(int hp);
	void SetATK(int atk);
	void SetGold(int gold);
	int RandomInRange(int min, int max);
	float RandomInRange(float min, float max);
	
	int MonsterATK();
	//stats
	int CalcDamage(int baseATK) const;
	bool TryEvade(int MonsterAgi) const;
	bool IsCritical() const;

	Monster* CreateRandomMonster(Player& player);


protected:
	std::string name_;
	int maxhp_;
	int hp_;
	int atk_;
	int gold_;
	// 능력치
	int str_;
	int agi_;
	int vit_;
	int int_;
	int luk_;
	// 드랍 아이템 정보
	ItemType dropType_ = ItemType::None;
	int dropId_ = -1;
	Player* player_;
};