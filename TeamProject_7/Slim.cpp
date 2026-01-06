#include "Slim.h"
#include "UIHelper.h"

Slim::Slim(const Player& player)
	: Monster()
{
	name_ = "슬라임";
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

Slim::~Slim()
{
	UIHelper::UpdateBot("슬라임을 처치했다!");
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

