#pragma once
#include "Monster.h"

class Goblin : public Monster
{
public:
	Goblin(const Player& player);
	~Goblin();

	void InitRandom();

	void MosterAttack() override;

private:

};