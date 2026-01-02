#include "Player.h"
#include "Inventory.h"
#include <iostream>

// 이름 포함 생성자
Player::Player(const std::string& Name)
    : name_(Name), level_(1), maxhp_(200), hp_(maxhp_), atk_(30), exp_(0), gold_(0)
{
    ShowStatus();
}

// 경험치 증가
void Player::GainExperience(int amount)
{
    exp_ += amount;
    while (exp_ >= 100)
    {
        level_++;
        exp_ -= 100;
        maxhp_ += 20; // 레벨업 시 최대 HP 증가 예시
        hp_ = maxhp_;  // HP 회복
        std::cout << name_ << " leveled up! Now LV: " << level_ << std::endl;
    }
}

void Player::AddExp(int amount)
{
    GainExperience(amount);
}

// 데미지 처리
void Player::TakeDamage(int amount)
{
    hp_ -= amount;
    if (hp_ < 0) 
    {
        hp_ = 0;
    }
    std::cout << name_ << " took " << amount << " damage! HP: " << hp_ << "/" << maxhp_ << std::endl;
}

// 골드 처리
void Player::AddGold(int amount)
{
    gold_ += amount;
}

bool Player::SpendGold(int amount)
{
    if (gold_ >= amount)
    {
        gold_ -= amount;
        return true;
    }
    return false;
}

// 게터
std::string Player::GetName() const { return name_; }
int Player::GetLevel() const { return level_; }
int Player::GetHP() const { return hp_; }
int Player::GetMaxHP() const { return maxhp_; }
int Player::GetEXP() const { return exp_;  }
int Player::GetATK() const { return atk_; }
int Player::GetGold() const { return gold_; }
Inventory* Player::GetInventory() { return inventory_; }


// 세터
void Player::SetHP(int hp) { hp_ = hp; }
void Player::SetATK(int attack) { atk_ = attack; }
void Player::SetEXP(int exp) { exp_ = exp; }
void Player::SetLevel(int lv) { hp_ = lv; }
void Player::SetGold(int gold) { gold_ = gold; }
void Player::SetMaxHP(int maxHp) { maxhp_ = maxHp; }

// 상태 출력
void Player::ShowStatus() const
{
    std::cout << "Name: " << name_
        << ", LV: " << level_
        << ", HP: " << hp_ << "/" << maxhp_
        << ", Attack: " << atk_
        << ", Experience: " << exp_
        << ", Gold: " << gold_ << std::endl;
}