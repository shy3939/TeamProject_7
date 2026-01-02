#include "Goblin.h"

Goblin::Goblin(const Player& player)
	: Monster()
{
	name_ = "고블린";
	InitRandom();
	int Level = player.GetLevel();

	int RandNum = RandomInRange(1, 10);
	maxhp_ = Level * rmaxhp_;
	hp_ = maxhp_;
	atk_ = Level * ratk_;
	gold_ = rgold_;
	
	if (RandNum < 4)
	{
		item_ = new AtkPotion("공격력 포션",1);
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

int Goblin::MonsterATK()
{
	return atk_;
}