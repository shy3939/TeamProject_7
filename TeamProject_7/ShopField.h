// ShopField.h
#pragma once
#include "Field.h"
#include "Player.h"
#include "ItemDatabase.h"

class ShopItem
{
public:
    std::string Name;
    int BasePrice;    // 기준 가격
    int CurrentPrice; // 실제 판매가 (랜덤 변동 적용)
    int itemID;
    ItemType type;
};

class ShopField : public Field
{
public:
    ShopField(ItemDatabase* db);
    void Enter(Player* player) override;
 
private:

    void BuyItem(Player* player);
    void SellItem(Player* player);
    void RefreshShop(); // 매번 목록을 새로고침하는 함수
    void UpdateShopUI(); // 리롤이나 입장 시 UI를 갱신해주는 보조 함수

    ItemDatabase* dbPtr; // 데이터베이스 참조를 위한 포인터 선언

    std::vector<ShopItem> CurrentStock; // 현재 매대에 진열할 아이템
    const int MaxDisplayCount = 6; // 포션 이외에 추가적으로 진열할 것
    // 포션 아이템 가격 (고정)
    const int HealthPotionPrice = 30;
    const int AttackPotionPrice = 50;
    const int RerollCost = 50; //리롤 비용 상수 추가
};
