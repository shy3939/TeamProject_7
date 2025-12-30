#include "Goblin.h"

Goblin::Goblin(const Player& player)
	: Monster()
{
	monstername_ = "고블린";
	InitRandom();
	int Level = player.GetLevel();

	maxhp_ = Level* rmaxhp_;
	hp_ = maxhp_;
	atk_ = Level* ratk_;
	gold_ = rgold_;

	// 아이템 보유 or 미보유

}

Goblin::~Goblin()
{
	std::cout << "고블린(를)을 처치하셨습니다!" << std::endl;
	
	// 동적 할당할 아이템 delete할 공간
}



void Goblin::InitRandom()
{
	rmaxhp_ = RandomInRange(20, 30);
	ratk_ = RandomInRange(5, 10);
	rgold_ = RandomInRange(10, 20);
	ritem_ = RandomInRange(1, 10);
}

int Goblin::MosterAttack()
{
	return atk_;
}

void Goblin::RHoldingItem()
{
	if (RandomInRange(1, 10) <= 3)
	{
		// 아이템 부여
	}
	// 아이템 미부여
}