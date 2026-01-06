#include "Dragon.h"

Dragon::Dragon(const Player& player)
	: Monster()
{
	name_ = "(Boss)드래곤";
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

	// 드랍 아이템 설정
	dropType_ = ItemType::Potion;
	if (RandNum < 5)
	{
		dropId_ = (int)PotionID::ATKPotion;
	}
	else
	{
		dropId_ = (int)PotionID::HPPotion;
	}
}

Dragon::~Dragon()
{
	std::cout << "드래곤(를)을 처치하셨습니다!" << std::endl;
}

void Dragon::TakeDamage(int damage_)
{
	this->hp_ -= damage_;
}

void Dragon::InitRandom()
{
	rmaxhp_ = RandomInRange(20, 45);
	ratk_ = RandomInRange(5, 15);
	rgold_ = RandomInRange(10, 30);
	rstr_ = RandomInRange(10, 45);
	ragi_ = RandomInRange(1, 15);
	rvit_ = RandomInRange(0, 99);
	rint_ = RandomInRange(10, 45);
	rluk_ = RandomInRange(0, 40);
}

int Dragon::MonsterATK()
{
	return atk_ + str_ + int_;
}