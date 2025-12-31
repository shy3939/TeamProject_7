#include "Goblin.h"

Goblin::Goblin(const Player& player)
	: Monster()
{
	monstername_ = "고블린";
	InitRandom();
	int Level = player.GetLV();

	int RandNum = RandomInRange(1, 10);
	maxhp_ = Level * rmaxhp_;
	hp_ = maxhp_;
	atk_ = Level * ratk_;
	gold_ = rgold_;

	if (RandNum < 4)
	{
		item_ = new AtkPotion(5, 1);
	}

}

Goblin::~Goblin()
{
	std::cout << "고블린(를)을 처치하셨습니다!" << std::endl;
}



void Goblin::InitRandom()
{
	rmaxhp_ = RandomInRange(20, 30);
	ratk_ = RandomInRange(5, 10);
	rgold_ = RandomInRange(10, 20);
}

int Goblin::MosterAttack()
{
	return atk_;
}