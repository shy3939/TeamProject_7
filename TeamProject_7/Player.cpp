#include "Player.h"
#include "Inventory.h"
#include <string>
#include <iostream>
#include "UIHelper.h"

// 이름 포함 생성자
Player::Player(const std::string& Name, const ItemDatabase& db)
    : name_(Name),
    level_(1),
    maxhp_(200),
    vmaxhp_(VitUpdate()),
    hp_(vmaxhp_),
    atk_(30),
    exp_(0),
    gold_(99999999),
    str_(RandomInRange(10, 50)),
    agi_(RandomInRange(1, 10)),
    vit_(RandomInRange(10, 100)),
    int_(RandomInRange(10, 30)),
    luk_(RandomInRange(0, 40)),
    db_(db),
    inventory_(std::make_unique<Inventory>(db))
{}

// 소멸자
Player::~Player()
{}

int Player::VitUpdate() const
{
    return  maxhp_ * (1 + 0.01f * vit_);
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
        vmaxhp_ = VitUpdate();
        hp_ = vmaxhp_;  // HP 회복
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

//능력치 처리
int Player::CalcDamage(int baseATK) const //STR
{
    float rate = 1.0f + std::max(str_, int_) * 0.01f;
    return static_cast<int>(baseATK * rate);
}

bool Player::TryEvade(int MonsterAgi) const //AGI
{
    if (agi_ > MonsterAgi)
        return rand() % 100 < 50;
    return false;
}


bool Player::IsCritical() const { return rand() % 100 < luk_; } //LUK


// 장비
void Player::Equip(EquipID id)
{
    Inventory* inv = nullptr;
    const auto& equipList = db_.GetEquipItems(id);
    if (equipList.empty()) return;
    const auto& data = equipList[0];

    EquipSlot slot = GetSlotFromEquipID(id);
    EquipID oldEquip = EquipID::None;

    // 기존 장비 해제
    Unequip(slot);

    // 장착
    switch (slot)
    {
    case EquipSlot::Weapon:
        oldEquip = equipped_.weapon;
        equipped_.weapon = id; 
        break;
    case EquipSlot::Armor:  
        oldEquip = equipped_.armor;
        equipped_.armor = id; 
        break;
    case EquipSlot::Gloves: 
        oldEquip = equipped_.gloves;
        equipped_.gloves = id; 
        break;
    case EquipSlot::Shoes:  
        oldEquip = equipped_.shoes;
        equipped_.shoes = id; 
        break;
    }
    
    if (oldEquip != EquipID::None)
    {
        inv->AddItem(ItemType::Equipment, (int)id, 1);
    }

    AddStat(
        data.BonusSTR,
        data.BonusAGI,
        data.BonusVIT,
        data.BonusINT,
        data.BonusLUK
    );
    
    vmaxhp_ = VitUpdate();
    std::cout << data.Name << " 장착 완료" << std::endl;
}

void Player::Unequip(EquipSlot slot)
{
    Inventory* inv = nullptr;
    EquipID id = EquipID::None;

    switch (slot)
    {
    case EquipSlot::Weapon:
        id = equipped_.weapon; 
        equipped_.weapon = EquipID::None; 
        break;
    case EquipSlot::Armor:  
        id = equipped_.armor;  
        equipped_.armor = EquipID::None; 
        break;
    case EquipSlot::Gloves: 
        id = equipped_.gloves; 
        equipped_.gloves = EquipID::None; 
        break;
    case EquipSlot::Shoes:  
        id = equipped_.shoes;  
        equipped_.shoes = EquipID::None; 
        break;
    }

    if (id == EquipID::None)
        return;

    const auto& data = db_.GetEquipItems(id)[0];

    AddStat(
        -data.BonusSTR,
        -data.BonusAGI,
        -data.BonusVIT,
        -data.BonusINT,
        -data.BonusLUK
    );
    
    vmaxhp_ = VitUpdate();
    std::cout << data.Name << " 장착 해제" << std::endl;
}

EquipID Player::GetEquippedID(EquipSlot slot) const
{
    switch (slot)
    {
    case EquipSlot::Weapon: return equipped_.weapon;
    case EquipSlot::Armor:  return equipped_.armor;
    case EquipSlot::Gloves: return equipped_.gloves;
    case EquipSlot::Shoes:  return equipped_.shoes;
    default: return EquipID::None;
    }
}


EquipSlot Player::GetSlotFromEquipID(EquipID id) const
{
    switch (id)
    {
    case EquipID::RustySword:
    case EquipID::NormalSword:
        return EquipSlot::Weapon;

    case EquipID::RustyArmor:
        return EquipSlot::Armor;

    default:
        throw std::runtime_error("Invalid EquipID");
    }
}


// 게터
std::string Player::GetName() const { return name_; }
int Player::GetLevel() const { return level_; }
int Player::GetHP() const { return hp_; }
int Player::GetMaxHP() const { return vmaxhp_; }
int Player::GetEXP() const { return exp_;  }
int Player::GetATK() const { return atk_; }
int Player::GetGold() const { return gold_; }
int Player::GetSTR() const { return str_; }
int Player::GetAGI() const { return agi_; }
int Player::GetVIT() const { return vit_; }
int Player::GetINT() const { return int_; }
int Player::GetLUK() const { return luk_; }
Inventory* Player::GetInventory() { return inventory_.get(); }


// 세터
void Player::SetHP(int hp) { hp_ = std::max(0, std::min(hp, vmaxhp_)); }
void Player::SetATK(int attack) { atk_ = attack; }
void Player::SetEXP(int exp) { exp_ = exp; }
void Player::SetLevel(int lv) { level_ = lv; }
void Player::SetGold(int gold) { gold_ = gold; }

// 상태 출력
void Player::ShowStatus() const
{
    std::cout << "Name: " << name_
        << ", LV: " << level_
        << ", HP: " << hp_ << "/" << vmaxhp_
        << ", Attack: " << atk_
        << ", Experience: " << exp_
        << ", Gold: " << gold_ << std::endl;
}

void Player::ShowEquipments() const
{
    UIHelper::UpdateBot("[장착 장비]", 1);
    UIHelper::UpdateBot("Weapon: " + std::to_string((int)equipped_.weapon), 1);
    UIHelper::UpdateBot("Armor: " + std::to_string((int)equipped_.armor), 1);
    UIHelper::UpdateBot("Gloves: " + std::to_string((int)equipped_.gloves), 1);
    UIHelper::UpdateBot("Shoes: " + std::to_string((int)equipped_.shoes), 1);
}


void Player::AddStat(int str, int agi, int vit, int intel, int luk)
{
    str_ += str;
    agi_ += agi;
    vit_ += vit;
    int_ += intel;
    luk_ += luk;
    vmaxhp_ = VitUpdate();
}

int Player::RandomInRange(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
