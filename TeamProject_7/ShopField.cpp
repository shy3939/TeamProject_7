// ShopField.cpp
#include "ShopField.h"
#include "Inventory.h"
#include <iostream>
#include <string>

void ShopField::Enter(Player* player)
{
    std::cout << "========================================" << std::endl;
    std::cout << "     🏪 상점에 입장했습니다! 🏪        " << std::endl;
    std::cout << "========================================" << std::endl;

    while (1)
    {
        std::cout << std::endl;
        std::cout << " 보유 골드 : " << player->GetGold() << " G" << std::endl;
        ShowMenu();

        int Choice;
        std::cin >> Choice;

        switch (Choice)
        {
        case 1:
            BuyItem(player);
            break;
        case 2:
            SellItem(player);
            break;
        case 3:
            player->ShowStatus();
            break;
        case 4:
            player->GetInventory()->ShowItems();
            break;
        case 0:
            std::cout << " 다음에도 살아서 만나요~ " << std::endl;
            return;
        default:
            std::cout << " 잘못된 입력입니다. " << std::endl;
            break;
        }
    }
}

void ShopField::ShowMenu()
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[상점 메뉴]" << std::endl;
    std::cout << "1. 아이템 구매" << std::endl;
    std::cout << "2. 아이템 판매" << std::endl;
    std::cout << "3. 상태 확인" << std::endl;
    std::cout << "4. 인벤토리 확인" << std::endl;
    std::cout << "0. 나가기" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "선택: ";
}

void ShopField::ShowShopItems()
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[판매 아이템 목록]" << std::endl;
    std::cout << " 1. 체력 포션  " << HealthPotionPrice << " G" << std::endl;
    std::cout << " 2. 공격력 포션 " << AttackPotionPrice << " G" << std::endl;
    std::cout << " 0. 취소 " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void ShopField::BuyItem(Player* player)
{
    ShowShopItems();
    std::cout << " 구매할 아이템: ";

    int Choice;
    std::cin >> Choice;

    std::string ItemName;
    int Price = 0;

    switch (Choice)
    {
    case 1:
        ItemName = "HealthPotion";
        Price = HealthPotionPrice;
        break;
    case 2:
        ItemName = "AttackPotion";
        Price = AttackPotionPrice;
        break;
    case 0:
        std::cout << "구매를 취소했습니다." << std::endl;
        return;
    default:
        std::cout << "잘못된 선택입니다." << std::endl;
        return;
    }

    // 골드 체크
    if (player->GetGold() < Price)
    {
        std::cout << "골드가 부족합니다!" << std::endl;
        std::cout << "현재 골드 : " << player->GetGold() << " G 보유중 " << std::endl;
        return;
    }

    // 몇 개 살지 물어보기
    std::cout << "몇 개 구매하시겠습니까? (보유 골드: " << player->GetGold() << " G): ";
    int Quantity;
    std::cin >> Quantity;

    if (Quantity <= 0)
    {
        std::cout << " 불가능한 입력입니다! " << std::endl;
        return;
    }

    const int TotalPrice = Price * Quantity;

    // 골드 부족 처리
    if (player->GetGold() < TotalPrice)
    {
        std::cout << "골드가 부족합니다!" << std::endl;
        std::cout << "필요: " << TotalPrice << " G, 보유: " << player->GetGold() << " G" << std::endl;
        return;
    }

    // 구매 처리
    player->SpendGold(TotalPrice);
    player->GetInventory()->AddItem(ItemName, Quantity);

    std::cout << "✅ " << ItemName << " " << Quantity << "개 구매 완료!" << std::endl;
    std::cout << "사용 골드: " << TotalPrice << " G" << std::endl;
}

void ShopField::SellItem(Player* player)
{
    Inventory* inventory = player->GetInventory();

    // 인벤토리 비어있는지
    if (inventory->IsEmpty())
    {
        std::cout << "판매할 아이템이 없습니다." << std::endl;
        return;
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[보유 아이템] (판매가는 구입가의 60%)" << std::endl;
    std::cout << "1. 체력 포션 - 보유: " << inventory->GetItemCount("HealthPotion") 
        << "개 (판매가: " << (int)(HealthPotionPrice * 0.6) << " G)" << std::endl;
    std::cout << "2. 공격력 포션 - 보유: " << inventory->GetItemCount("AttackPotion")
        << "개 (판매가: " << (int)(AttackPotionPrice * 0.6) << " G)" << std::endl;
    std::cout << "0. 취소" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "판매할 아이템: ";

    int Choice;
    std::cin >> Choice;

    std::string ItemName;
    int SellPrice = 0;

    switch (Choice)
    {
    case 1:
        ItemName = "HealthPotion";
        SellPrice = (int)(HealthPotionPrice * 0.6);  // 60%
        break;
    case 2:
        ItemName = "AttackPotion";
        SellPrice = (int)(AttackPotionPrice * 0.6);  // 60%
        break;
    case 0:
        std::cout << "판매를 취소했습니다." << std::endl;
        return;
    default:
        std::cout << "잘못된 선택입니다." << std::endl;
        return;
    }

    // 보유 체크
    int Owned = inventory->GetItemCount(ItemName);
    if (Owned <= 0)
    {
        std::cout << "해당 아이템을 보유하고 있지 않습니다." << std::endl;
        return;
    }

    std::cout << "몇 개 판매하시겠습니까? (보유: " << Owned << "개): ";
    int Quantity;
    std::cin >> Quantity;

    // 입력 체크
    if (Quantity <= 0)
    {
        std::cout << " 불가능한 입력입니다! " << std::endl;
        return;
    }

    // 보유 수량 체크
    if (Quantity > Owned)
    {
        std::cout << " 보유 수량보다 많이 판매할 수 없습니다. " << std::endl;
        return;
    }

    // 판매 처리
    const int TotalGold = SellPrice * Quantity;
    inventory->RemoveItem(ItemName, Quantity);
    player->AddGold(TotalGold);

    std::cout << "✅ " << ItemName << " " << Quantity << "개 판매 완료!" << std::endl;
    std::cout << "획득 골드: " << TotalGold << " G" << std::endl;
}