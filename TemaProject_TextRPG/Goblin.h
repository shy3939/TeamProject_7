#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
	Goblin(const Player& player);

	~Goblin() override;

	int MosterAttack() override;

	void InitRandom() override;
	void RHoldingItem() override;


private:
	int rmaxhp_;
	int ratk_;
	int rgold_;
	int ritem_;
};