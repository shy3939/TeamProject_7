#pragma once
#include "Monster.h"
class Dragon : public Monster
{
public:
	Dragon(const Player& player);
	~Dragon() override;

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
};
