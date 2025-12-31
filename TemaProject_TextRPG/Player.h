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
    Inventory Inven;

public:
    // ������
    Player();
    Player(const string& name, int lv = 1, int hp = 200, int attack = 30, int exp = 0, int gold = 0);

    // ����ġ ����
    void GainExperience(int amount);
    void AddExp(int amount);

    // ������ ó��
    void TakeDamage(int amount);

    // ��� ����
    void AddGold(int amount);
    bool SpendGold(int amount);

    // ����
    string GetName() const;
    int GetLV() const;
    int GetHP() const;
    int GetMaxHP() const;
    int GetAttack() const;
    int GetGold() const;
    Inventory* GetInventory();

    // ����
    void SetName(const string& name);
    void SetHP(int hp);
    void SetAttack(int attack);
    void SetExperience(int exp);
    void SetLV(int lv);
    void SetGold(int gold);
    void SetMaxHP(int maxHp);

    // ���� ���
    void ShowStatus() const;
};
