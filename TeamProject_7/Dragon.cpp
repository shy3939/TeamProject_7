#include "Dragon.h"
#include "UIHelper.h"

Dragon::Dragon(const Player& player)
	: Monster()
{
	name_ = "드래곤";
	InitRandom();

	int Level = player.GetLevel();

	int RandNum = RandomInRange(1, 10);

	maxhp_ = Level * rmaxhp_ * (1 + 0.01f * rvit_);
	hp_ = maxhp_;
	atk_ = Level * ratk_;
	gold_ = rgold_;
	str_ = rstr_;
	agi_ = ragi_;
	vit_ = rvit_;
	int_ = rint_;
	luk_ = rluk_;
}

Dragon::~Dragon()
{
	UIHelper::UpdateBot(" !!! 드래곤을 처치했다 !!! ");
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
