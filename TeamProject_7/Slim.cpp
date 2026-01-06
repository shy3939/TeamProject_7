#include "Slim.h"
#include "ItemEnum.h"

Slim::Slim(const Player& player)
	: Monster()
{
	name_ = "슬라임";
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

Slim::~Slim()
{
	std::cout << "슬라임(를)을 처치하셨습니다!" << std::endl;
}

void Slim::TakeDamage(int damage_)
{
	this->hp_ -= damage_;
}

void Slim::InitRandom()
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

int Slim::MonsterATK()
{
	return atk_ + str_ + int_;
}