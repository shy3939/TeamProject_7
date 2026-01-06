#pragma once
#include "Monster.h"
#include "ItemDatabase.h"
#include <string>

class BossMonster : public Monster
{
public:
	BossMonster(Player* player, const ItemDatabase& db, Monster& base_monster);
	~BossMonster() override;

	int MonsterATK() override;
	void TakeDamage(int damage_) override;
	void InitRandom() override;

private:
	const ItemDatabase& db_;
	std::string name;
	int maxhp_;
	int atk_;
	int gold_;

};