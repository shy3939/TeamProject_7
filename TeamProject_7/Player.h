#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "ItemDatabase.h"
#include "ItemEnum.h"

class Inventory;

struct EquipmentSlots
{
    EquipID weapon = EquipID::None;
    EquipID armor = EquipID::None;
    EquipID gloves = EquipID::None;
    EquipID shoes = EquipID::None;
};


class Player
{
public:
    // 생성자
    Player(const std::string& Name, const ItemDatabase& db);
    // 소멸자
    ~Player();

    // 경험치 관련
    void GainExperience(int amount);
    void AddExp(int amount);

    // 데미지 처리
    void TakeDamage(int amount);

    // 골드 관련
    void AddGold(int amount);
    bool SpendGold(int amount);

    // 장비 관련
    void Equip(EquipID id);
    void Unequip(EquipSlot slot);
    EquipSlot GetSlotFromEquipID(EquipID id);

    // 능력치 관련
    int CalcPhysicalDamage(int baseAtk) const;      // STR
    bool TryEvade(int enemyAgi) const;              // AGI
    int  ApplyDamageReduction(int rawDamage) const; // VIT
    int CalcMagicDamage(int baseMagic) const;       // INT
    bool IsCritical() const;                        // LUK

    int RandomInRange(int min, int max);
    void AddStat(int str, int agi, int vit, int intel, int luk);

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
    void ShowEquipments() const;

private:
    std::string name_;
    int level_;
    int maxhp_;
    int hp_;
    int atk_;
    int exp_;
    int gold_;
    //능력치
    int str_;
    int agi_;
    int vit_;
    int int_;
    int luk_;
    //아이템
    std::unique_ptr<Inventory> inventory_;
    EquipmentSlots equipped_;
    const ItemDatabase& db_;
};

