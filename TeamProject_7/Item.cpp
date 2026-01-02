#include <iostream>
#include <string>
#include "Item.h"
#include "player.h"


Item::Item(std::string ItemName) : ItemName_(ItemName) {}
Item::~Item() {}


HpPotion::HpPotion(std::string ItemName) : Item("HP 포션") {}

void HpPotion::Use(Player& player)
{
    int CurrentHp = player.GetHP();
    int MaxHp = player.GetMaxHP();

    if (CurrentHp < MaxHp)
    {
        std::cout << ItemName_ << " 사용" << HealAmount_ << "의 체력을 회복했습니다." << std::endl;
        CurrentHp += HealAmount_;

        if (CurrentHp > MaxHp)
        {
            CurrentHp = MaxHp;
        }

        player.SetHP(CurrentHp);

        std::cout << "현재 체력 : " << player.GetHP() << std::endl;
    }
    else
    {
        std::cout << "이미 체력이 가득 차 있어 포션을 사용할 수 없습니다." << std::endl;
    }
}

AtkPotion::AtkPotion(std::string ItemName, int count) : Item("공격력 포션") {}

void AtkPotion::Use(Player& player)
{

    int nextAtk = player.GetATK() + AtkAmount_;

    player.SetATK(nextAtk);

    std::cout << ItemName_ << " 사용" << AtkAmount_ << "의 공격력이 증가했습니다." << std::endl;
    std::cout << "현재 공격력 : " << player.GetATK() << std::endl;
}