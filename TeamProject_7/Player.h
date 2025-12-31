#pragma once
#include <iostream>
#include <string>
#include "Inventory.h"

using namespace std;

class Player
{
private:
    string Name;
    int LV;
    int HP;
    int MaxHP;
    int Attack;
    int Experience;
    int Gold;
    Inventory<string> Inven;

public:
    // 생성자
    Player();
    Player(const string& name, int lv = 1, int hp = 200, int attack = 30, int exp = 0, int gold = 0);

    // 경험치 관련
    void GainExperience(int amount);
    void AddExp(int amount);

    // 데미지 처리
    void TakeDamage(int amount);

    // 골드 관련
    void AddGold(int amount);
    bool SpendGold(int amount);

    // 게터
    string GetName() const;
    int GetLV() const;
    int GetHP() const;
    int GetMaxHP() const;
    int GetAttack() const;
    int GetGold() const;
    Inventory<string>* GetInventory();

    // 세터
    void SetName(const string& name);
    void SetHP(int hp);
    void SetAttack(int attack);
    void SetExperience(int exp);
    void SetLV(int lv);
    void SetGold(int gold);
    void SetMaxHP(int maxHp);

    // 상태 출력
    void ShowStatus() const;
};

