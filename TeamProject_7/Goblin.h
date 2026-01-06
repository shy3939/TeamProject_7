#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
	Goblin(Player& player, const ItemDatabase& db);
	~Goblin() override;

	int MonsterATK() override;
	void TakeDamage(int damage_) override;
	void InitRandom() override;


private:
	int rmaxhp_;
	int ratk_;
	int rgold_;
	int rstr_;
	int ragi_;
	int rvit_;
	int rint_;
	int rluk_;
	const ItemDatabase& db_;
};