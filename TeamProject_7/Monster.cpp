#include "Monster.h"

Monster::Monster(Player* player)
	:name_("Unknown"),
	maxhp_(0),
	hp_(0),
	atk_(0),
	gold_(0),
	str_(0),
	agi_(0),
	vit_(0),
	int_(0),
	luk_(0),
	item_(nullptr),
	player_(nullptr)

{
}

Monster::~Monster()
{
	delete item_;
}

std::string Monster::GetName() const { return name_; }
int Monster::GetMaxHP() const { return maxhp_; }
int Monster::GetHP() const { return hp_; }
int Monster::GetATK() const { return atk_; }
int Monster::GetGold() const { return gold_; }
int Monster::GetSTR() const { return str_; }
int Monster::GetAGI() const { return agi_; }
int Monster::GetVIT() const { return vit_; }
int Monster::GetINT() const { return int_; }
int Monster::GetLUK() const { return luk_; }

void Monster::SetMaxHP(int maxhp) { maxhp_ = maxhp; }
void Monster::SetHP(int hp) { hp_ = hp; }
void Monster::SetATK(int atk) { atk_ = atk; }
void Monster::SetGold(int gold) { gold_ = gold; }


int Monster::RandomInRange(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

float Monster::RandomInRange(float min, float max)
{
	return (rand() / (float)RAND_MAX) * (max-min) + min ;
	// 0부터1 -> max-min -> min부터 max까지
}
