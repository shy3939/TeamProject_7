// ShopField.h
#pragma once
#include "Field.h"
#include "Player.h"


class ShopField : public Field
{
public:
    ShopField() {};
    void Enter(Player* player) override;

private:
    void ShowMenu();
    void ShowShopItems();
    void BuyItem(Player* player);
    void SellItem(Player* player);

    // 아이템 가격 (고정)
    const int HealthPotionPrice = 30;
    const int AttackPotionPrice = 50;
};