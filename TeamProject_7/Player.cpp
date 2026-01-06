#include "Player.h"
#include "Inventory.h"
#include <iostream>

// 이름 포함 생성자
Player::Player(const std::string& Name, const ItemDatabase& db)
    : name_(Name),
    level_(1),
    hp_(200),
    maxhp_(200),
    atk_(30),
    exp_(0),
    gold_(0),
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
int Player::CalcPhysicalDamage(int baseATK) const //STR
{
    float rate = 1.0f + str_ * 0.01f;
    return static_cast<int>(baseATK * rate);
}

bool Player::TryEvade(int MonsterAgi) const //AGI
{
    if (agi_ > MonsterAgi)
        return rand() % 100 < 50;
    return false;
}
int Player::ApplyDamageReduction(int rawDamage) const //VIT
{
    float rate = vit_ * 0.01f;
    if (rate > 0.5f) rate = 0.5f;
    return static_cast<int>(rawDamage * (1.0f - rate));
}

int Player::CalcMagicDamage(int baseMagic) const //INT
{
    float rate = 1.0f + int_ * 0.01f;
    return static_cast<int>(baseMagic * rate);
}

bool Player::IsCritical() const { return rand() % 100 < luk_; } //LUK


// 장비
void Player::Equipment(EquipID id)
{
    const auto& equipList = db_.GetEquipItems(id);
    if (equipList.empty()) return;
    const auto& data = equipList[0];

    EquipSlot slot = GetSlotFromEquipID(id);

    // 기존 장비 해제
    Unequip(slot);

    // 장착
    switch (slot)
    {
    case EquipSlot::Weapon: equipped_.weapon = id; break;
    case EquipSlot::Armor:  equipped_.armor = id; break;
    case EquipSlot::Gloves: equipped_.gloves = id; break;
    case EquipSlot::Shoes:  equipped_.shoes = id; break;
    }

    AddStat(
        data.BonusSTR,
        data.BonusAGI,
        data.BonusVIT,
        data.BonusINT,
        data.BonusLUK
    );
    std::cout << data.Name << " 장착 완료" << std::endl;
}

void Player::Unequip(EquipSlot slot)
{
    EquipID id = EquipID::None;

    switch (slot)
    {
    case EquipSlot::Weapon: id = equipped_.weapon; equipped_.weapon = EquipID::None; break;
    case EquipSlot::Armor:  id = equipped_.armor;  equipped_.armor = EquipID::None; break;
    case EquipSlot::Gloves: id = equipped_.gloves; equipped_.gloves = EquipID::None; break;
    case EquipSlot::Shoes:  id = equipped_.shoes;  equipped_.shoes = EquipID::None; break;
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

    std::cout << data.Name << " 장착 해제" << std::endl;
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
int Player::GetMaxHP() const { return maxhp_; }
int Player::GetEXP() const { return exp_;  }
int Player::GetATK() const { return atk_; }
int Player::GetGold() const { return gold_; }
Inventory* Player::GetInventory() { return inventory_.get(); }


// 세터
void Player::SetHP(int hp) { hp_ = std::max(0, std::min(hp, maxhp_)); }
void Player::SetATK(int attack) { atk_ = attack; }
void Player::SetEXP(int exp) { exp_ = exp; }
void Player::SetLevel(int lv) { level_ = lv; }
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

void Player::ShowEquipments() const
{
    std::cout << "[장착 장비]" << std::endl;
    std::cout << "Weapon: " << (int)equipped_.weapon << std::endl;
    std::cout << "Armor : " << (int)equipped_.armor << std::endl;
    std::cout << "Gloves: " << (int)equipped_.gloves << std::endl;
    std::cout << "Shoes : " << (int)equipped_.shoes << std::endl;
}


void Player::AddStat(int str, int agi, int vit, int intel, int luk)
{
    str_ += str;
    agi_ += agi;
    vit_ += vit;
    int_ += intel;
    luk_ += luk;
}
