#include "Monster.h"

Monster::Monster(std::string monstername, int maxhp, int atk, int gold)
	:monstername_(monstername),
	maxhp_(maxhp),
	hp_(maxhp),
	atk_(atk),
	gold_(gold)
{}

Monster::~Monster()
{}

std::string Monster::GetMonsterName()
{
	return monstername_;
}
int Monster::GetMaxHp()
{
	return maxhp_;
}
int Monster::GetHp()
{
	return hp_;
}
int Monster::GetATK()
{
	return atk_;
}
int Monster::GetGold()
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

int RandomInRange(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
