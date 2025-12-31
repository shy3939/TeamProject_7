#include "Player.h"
#include <iostream>

// �⺻ ������
Player::Player()
    : Name("Hero"), LV(1), HP(200), MaxHP(200), Attack(30), Experience(0), Gold(0)
{
    cout << "Player created! Name: " << Name << endl;
    ShowStatus();
}

// �̸� ���� ������
Player::Player(const string& name, int lv, int hp, int attack, int exp, int gold)
    : Name(name), LV(lv), HP(hp), MaxHP(hp), Attack(attack), Experience(exp), Gold(gold)
{
    cout << "Player created! Name: " << Name << endl;
    ShowStatus();
}

// ����ġ ����
void Player::GainExperience(int amount)
{
    Experience += amount;
    while (Experience >= 100)
    {
        LV++;
        Experience -= 100;
        MaxHP += 20; // ������ �� �ִ� HP ���� ����
        HP = MaxHP;  // HP ȸ��
        cout << Name << " leveled up! Now LV: " << LV << endl;
    }
}

void Player::AddExp(int amount)
{
    GainExperience(amount);
}

// ������ ó��
void Player::TakeDamage(int amount)
{
    HP -= amount;
    if (HP < 0) HP = 0;
    cout << Name << " took " << amount << " damage! HP: " << HP << "/" << MaxHP << endl;
}

// ��� ó��
void Player::AddGold(int amount)
{
    Gold += amount;
}

bool Player::SpendGold(int amount)
{
    if (Gold >= amount)
    {
        Gold -= amount;
        return true;
    }
    return false;
}

// ����
string Player::GetName() const { return Name; }
int Player::GetLV() const { return LV; }
int Player::GetHP() const { return HP; }
int Player::GetMaxHP() const { return MaxHP; }
int Player::GetAttack() const { return Attack; }
int Player::GetGold() const { return Gold; }
Inventory* Player::GetInventory() { return &Inven; }

// ����
void Player::SetName(const string& name) { Name = name; }
void Player::SetHP(int hp) { HP = hp; }
void Player::SetAttack(int attack) { Attack = attack; }
void Player::SetExperience(int exp) { Experience = exp; }
void Player::SetLV(int lv) { LV = lv; }
void Player::SetGold(int gold) { Gold = gold; }
void Player::SetMaxHP(int maxHp) { MaxHP = maxHp; }

// ���� ���
void Player::ShowStatus() const
{
    cout << "Name: " << Name
        << ", LV: " << LV
        << ", HP: " << HP << "/" << MaxHP
        << ", Attack: " << Attack
        << ", Experience: " << Experience
        << ", Gold: " << Gold << endl;
}