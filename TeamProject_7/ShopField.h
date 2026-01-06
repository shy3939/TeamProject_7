// ShopField.h
#pragma once
#include "Field.h"
#include "Player.h"
#include "ItemDatabase.h"

class ShopItem
{
public:
    std::string Name;
    ItemType ItemType;
    int ItemId;
    int BasePrice;    // 기준 가격
    int CurrentPrice; // 실제 판매가 (랜덤 변동 적용)
};

class ShopField : public Field
{
public:
    ShopField(const ItemDatabase& db);
    void Enter(Player* player) override;

private:
    void BuyItem(Player* player);
    void CloseSellUI();
    void SellItem(Player* player);
    void RefreshShop(); // 매번 목록을 새로고침하는 함수

    const ItemDatabase& m_DB;
    std::vector<ShopItem> ItemPool; // 상점에서 팔 수 있는 전체 아이템
    std::vector<ShopItem> CurrentStock; // 현재 매대에 진열할 아이템
    const int MaxDisplayCount = 4; // 포션 이외에 추가적으로 진열할 것
    // 포션 아이템 가격 (고정)
    const int HealthPotionPrice = 30;
    const int AttackPotionPrice = 50;
};
