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
    int VitUpdate() const;

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
    EquipSlot GetSlotFromEquipID(EquipID id) const;

    // 능력치 관련
    int CalcDamage(int baseAtk) const;      // STR, INT
    bool TryEvade(int enemyAgi) const;              // AGI
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
    
    //stats
    int GetSTR() const;
    int GetAGI() const;
    int GetVIT() const;
    int GetINT() const;
    int GetLUK() const;
    
    int GetGold() const;
    Inventory* GetInventory();

    // 세터
    void SetHP(int hp);
    void SetATK(int attack);
    void SetEXP(int exp);
    void SetLevel(int lv);
    void SetGold(int gold);


    // 상태 출력
    void ShowStatus() const;
    void ShowEquipments() const;
    EquipID GetEquippedID(EquipSlot slot) const;

private:
    std::string name_;
    int str_;
    int agi_;
    int vit_;
    int int_;
    int luk_;
    int level_;
    int maxhp_;
    int vmaxhp_;
    int hp_;
    int atk_;
    int exp_;
    int gold_;
    //능력치

    //아이템
    std::unique_ptr<Inventory> inventory_;
    EquipmentSlots equipped_;
    const ItemDatabase& db_;
};