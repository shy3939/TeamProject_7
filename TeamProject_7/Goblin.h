#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
	Goblin(const Player& player);
	~Goblin() override;

	int MonsterATK() override;
	void TakeDamage(int damage_) override;
	void InitRandom() override;


private:
	int rmaxhp_;
	int ratk_;
	int rgold_;

};