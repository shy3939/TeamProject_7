#include "BossMonster.h"

//이름: "Boss " + 기존 몬스터 이름
//hp = base.hp * 1.5
//atk = base.atk * 1.5
//gold도 1.5배
BossMonster::BossMonster(Player* player, const ItemDatabase& db, Monster& base_)
    : Monster(player), db_(db) // 부모 생성자 호출 및 db_ 초기화
{
    // base_ 인자를 통해 전달받은 몬스터의 능력치를 1.5배로 설정
    name_ = "Boss " + base_.GetName();
    maxhp_ = static_cast<int>(base_.GetMaxHP() * 1.5f);
    hp_ = maxhp_;
    atk_ = static_cast<int>(base_.GetATK() * 1.5f);
    gold_ = static_cast<int>(base_.GetGold() * 1.5f);
    str_ = static_cast<int>(base_.GetSTR() * 1.5f);
    agi_ = base_.GetAGI();
    vit_ = static_cast<int>(base_.GetVIT() * 1.5f);
    int_ = static_cast<int>(base_.GetINT() * 1.5f);
    luk_ = base_.GetLUK();
}
// 보스 변수 string이 포인터일때는 
// new string("Boss" + base_.GetName());

//몬스터 헤더파일의 버츄어 함수 사용주기 끝나면 종료
BossMonster::~BossMonster()
{
    std::cout << "보스 몬스터를 물리쳤습니다!" << std::endl;
}

int BossMonster::MonsterATK()
{
	return atk_ + str_ + int_;
}

void BossMonster::TakeDamage(int damage_)
{
	this->hp_ -= damage_;
}

void BossMonster::InitRandom()
{
}