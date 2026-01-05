#pragma once
#include "Monster.h"
#include <string>

class BossMonster : public Monster
{
public:
	BossMonster(Monster& base_);
	~BossMonster() override;

	int MonsterATK() override;
	void TakeDamage(int damage_) override;

private:
	std::string name;
	int maxhp_;
	int atk_;
	int gold_;

};