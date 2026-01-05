#include "BossMonster.h"

//이름: "Boss " + 기존 몬스터 이름
//hp = base.hp * 1.5
//atk = base.atk * 1.5
//gold도 1.5배
BossMonster::BossMonster(Monster& base_)
{
	name_ = "Boss " + base_.GetName();
	maxhp_ = base_.GetHP() * RandomInRange(1, 1.5);
	hp_ = maxhp_;
	atk_ = base_.GetATK() * RandomInRange(1, 1.5);
	gold_ = base_.GetGold() * RandomInRange(1, 1.5);
	str_ = base_.GetSTR() * RandomInRange(1, 1.5);
	agi_ = base_.GetAGI();
	vit_ = base_.GetVIT() * 1.5;
	int_ = base_.GetINT() * 1.5;
	luk_ = base_.GetLUK();

}
// 보스 변수 string이 포인터일때는 
// new string("Boss" + base_.GetName());

//몬스터 헤더파일의 버츄어 함수 사용주기 끝나면 종료
BossMonster::~BossMonster()
{}

int BossMonster::MonsterATK()
{
	return atk_ + str_ + int_;
}

void BossMonster::TakeDamage(int damage_)
{
	this->hp_ -= damage_;
}
