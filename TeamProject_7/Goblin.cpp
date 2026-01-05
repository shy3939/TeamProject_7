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
	str_ = rstr_;
	agi_ = ragi_;
	vit_ = rvit_;
	int_ = rint_;
	luk_ = rluk_;
	if (RandNum < 4)
	{
		item_ = new AtkPotion();
		item_ = new HpPotion();
	}
	else if (RandNum >= 4 && RandNum < 8)
	{
		item_ = new AtkPotion();
	}
	else
	{
		item_ = new HpPotion();
	}
}

Goblin::~Goblin()
{
	std::cout << "고블린(를)을 처치하셨습니다!" << std::endl;
}

void Goblin::TakeDamage(int damage_)
{
	this->hp_ -= damage_;
}

void Goblin::InitRandom()
{
	rmaxhp_ = RandomInRange(20, 30);
	ratk_ = RandomInRange(5, 10);
	rgold_ = RandomInRange(10, 20);
	rstr_ = RandomInRange(10, 30);
	ragi_ = RandomInRange(1, 10);
	rvit_ = RandomInRange(0, 100);
	rint_ = RandomInRange(10, 30);
	rluk_ = RandomInRange(0, 40);
}

int Goblin::MonsterATK()
{
	return atk_ + str_ + int_;
}