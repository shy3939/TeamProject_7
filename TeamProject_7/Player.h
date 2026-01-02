#pragma once
#include <iostream>
#include <string>
#include "Inventory.h"

class Player
{
public:
    // 생성자
    Player(const std::string& Name);

    // 경험치 관련
    void GainExperience(int amount);
    void AddExp(int amount);

    // 데미지 처리
    void TakeDamage(int amount);

    // 골드 관련
    void AddGold(int amount);
    bool SpendGold(int amount);

    // 게터
    std::string GetName() const;
    int GetLevel() const;
    int GetEXP() const;
    int GetHP() const;
    int GetMaxHP() const;
    int GetATK() const;
    int GetGold() const;
    Inventory* GetInventory();

    // 세터
    void SetHP(int hp);
    void SetATK(int attack);
    void SetEXP(int exp);
    void SetLevel(int lv);
    void SetGold(int gold);
    void SetMaxHP(int maxHp);

    // 상태 출력
    void ShowStatus() const;

private:
    std::string name_;
    int level_;
    int hp_;
    int maxhp_;
    int atk_;
    int exp_;
    int gold_;
    Inventory* inventory_;
};

