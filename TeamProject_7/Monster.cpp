#include "Monster.h"

Monster::Monster()
	:name_("Unknown"),
	maxhp_(0),
	hp_(0),
	atk_(0),
	gold_(0),
	item_(nullptr)
{
}

Monster::~Monster()
{
	delete item_;
}

std::string Monster::GetName() const { return name_; }
int Monster::GetMaxHP() const { return maxhp_; }
int Monster::GetHP() const
{
	return hp_;
}
int Monster::GetATK() const
{
	return atk_;
}
int Monster::GetGold() const
{
	return gold_;
}
void Monster::SetMaxHP(int maxhp)
{
	maxhp_ = maxhp;
}
void Monster::SetHP(int hp)
{
	hp_ = hp;
}
void Monster::SetATK(int atk)
{
	atk_ = atk;
}
void Monster::SetGold(int gold)
{
	gold_ = gold;
}

int Monster::RandomInRange(int min, int max)
{
	return rand() % (max - min + 1) + min;
}