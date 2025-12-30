#include "Monster.h"

Monster::Monster()
	:monstername_("Unknow"),
	maxhp_(0),
	hp_(0),
	atk_(0),
	gold_(0)
{}

Monster::~Monster()
{}

std::string Monster::GetMonsterName() const
{
	return monstername_;
}
int Monster::GetMaxHp() const
{
	return maxhp_;
}
int Monster::GetHp() const
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
// 획득한 아이템 출력
void Monster::SetMaxHp(int maxhp)
{
	maxhp_ = maxhp;
}
void Monster::SetHp(int hp)
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
// 획득할 아이템 선택

int Monster::RandomInRange(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
