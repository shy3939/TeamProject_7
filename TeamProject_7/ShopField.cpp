// ShopField.cpp
#include "ShopField.h"
#include "Inventory.h"
#include "UIHelper.h"
#include "AsciiArt.h"
#include "ItemDatabase.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>


ShopField::ShopField(ItemDatabase* db) : dbPtr(db) {
    // 이제 ItemPool은 사용하지 않고 Database에서 직접 가져옵니다.
}
// [2] 입장 함수: 매대 새로고침 및 메인 루프 실행
void ShopField::Enter(Player* player)
{
    RefreshShop(); 
        // 상점 입장 시마다 아이템 구성을 새로고침
      
        // UI 상단부에 아이템 정보 삽입
    UIHelper::UpdateTop(AsciiArt::ShopBackGround);
    for (int i = 0; i < 6; ++i) {
        UIHelper::AddToShopList(CurrentStock[i].Name, std::to_string(CurrentStock[i].CurrentPrice) , i);
    }
    UIHelper::UpdateBot("  상점에 입장했습니다! " , 1);

    while (1)
    {
        std::string Choice =  UIHelper::UpdateBotInput("[상점 메뉴] : 1. 아이템 구매  2. 아이템 판매 3. 리롤(" + std::to_string(RerollCost) + "G) 4. 나가기 ");

        if (Choice == "1") 
        {
            BuyItem(player);
        }
        else if (Choice == "2") 
        {
            SellItem(player);
        }
        else if (Choice == "3") 
        {
            // 리롤 로직
            if (player->GetGold() >= RerollCost) 
            {
                player->SpendGold(RerollCost);
                RefreshShop();
                UpdateShopUI(); // 리롤된 정보로 UI 갱신
                UIHelper::UpdateBot("매대 상품을 갱신했습니다! (-" + std::to_string(RerollCost) + "G)", 1);
            }
            else 
            {
                UIHelper::UpdateBot("골드가 부족하여 리롤할 수 없습니다!", 1);
            }
        }
        else if (Choice == "4") 
        {
            UIHelper::UpdateBot("다음에도 살아서 만나요~ ", 1);
            return;
        }
        else 
        {
            UIHelper::UpdateBot("잘못된 입력입니다 !", 0.5);
        }
    }
}

void ShopField::UpdateShopUI() 
{
    for (int i = 0; i < 6; ++i) 
    {
        if (i < (int)CurrentStock.size()) 
        {
            UIHelper::AddToShopList(CurrentStock[i].Name, std::to_string(CurrentStock[i].CurrentPrice), i);
        }
    }
}

void ShopField::RefreshShop()
{
    CurrentStock.clear();
    std::random_device rd;
    std::mt19937 g(rd());

    // 카테고리 분포 (0: 장비, 1: 포션, 2: 재료)
    std::uniform_int_distribution<int> categoryDist(0, 2);
    // 가격 변동 분포 (80% ~ 120%)
    std::uniform_int_distribution<int> priceVar(80, 120);

    // 총 6개의 아이템을 무작위로 추출
    for (int i = 0; i < 6; ++i) {
        int cat = categoryDist(g);
        ShopItem newItem;

        if(cat == 0) { // 장비
            std::uniform_int_distribution<int> idDist(0, (int)EquipID::SturdyShoes);
            EquipID rid = static_cast<EquipID>(idDist(g));
            const auto& data = dbPtr->GetEquipItems(rid)[0];
            newItem = { data.Name, data.Price, 0, (int)rid, ItemType::Equipment};
        }
        else if (cat == 1) { // 포션
            std::uniform_int_distribution<int> idDist(0, (int)PotionID::ATKPotion);
            PotionID rid = static_cast<PotionID>(idDist(g));
            const auto& data = dbPtr->GetPotionItems(rid)[0];
            newItem = { data.Name, data.Price, 0, (int)rid, ItemType::Potion };
            }
        else { // 재료
                std::uniform_int_distribution<int> idDist(0, (int)IngredID::Whetstone);
                IngredID rid = static_cast<IngredID>(idDist(g));
                const auto& data = dbPtr->GetIngredItems(rid)[0];
                newItem = { data.Name, data.Price, 0, (int)rid, ItemType::Ingredient };
                }

                newItem.CurrentPrice = static_cast<int>(newItem.BasePrice * (priceVar(g) / 100.0f));
                CurrentStock.push_back(newItem);
    }
}

// [5] 아이템 구매 로직: 선택 번호에 따른 인덱스 매핑이 핵심
void ShopField::BuyItem(Player* player)
{
    if (CurrentStock.empty()) return;

    // 1. 번호 선택 입력
    std::string strChoice = UIHelper::UpdateBotInput("구매할 번호(1~6)를 입력해주세요");
    if (strChoice.empty()) return;

    int Choice = std::stoi(strChoice);
    if (Choice < 1 || Choice > 6) 
    {
        UIHelper::UpdateBot("잘못된 번호입니다!", 0.5);
        return;
    }

    // 선택된 아이템 정보 참조
    ShopItem& selected = CurrentStock[Choice - 1];
    int Quantity = 1;

    // 2. 아이템 타입에 따른 구매 방식 분기
    if (selected.type != ItemType::Equipment) {
        std::string strQty = UIHelper::UpdateBotInput(selected.Name + " 몇 개 구매?");
        if (strQty.empty()) return;
        Quantity = std::stoi(strQty);
    }
    else {
        std::string confirm = UIHelper::UpdateBotInput(selected.Name + " 구매? (y/n)");
        if (confirm != "y" && confirm != "Y") return;
    }

    if (Quantity <= 0) return;

    int TotalPrice = selected.CurrentPrice * Quantity;
    if (player->GetGold() >= TotalPrice) {
        player->SpendGold(TotalPrice);
        player->GetInventory()->AddItem(selected.type, selected.itemID, Quantity);
        UIHelper::UpdateBot(selected.Name + " 구매 완료!", 1);
    }
    else {
        UIHelper::UpdateBot("골드가 부족합니다!", 0.7);
    }
}

void ShopField::SellItem(Player* player)
{
    Inventory* inv = player->GetInventory();
    if (inv->IsEmpty()) {
        UIHelper::UpdateBot("판매할 아이템이 없습니다.", 1);
        return;
    }

    inv->ShowInventory(); // 현재 인벤토리 출력

    std::string strSlot = UIHelper::UpdateBotInput("판매할 슬롯 번호를 입력하세요 (1~30)");
    if (strSlot.empty()) return;

    int displaySlot = std::stoi(strSlot);
    if (!inv->IsAvailable(displaySlot)) {
        UIHelper::UpdateBot("해당 슬롯이 비어있습니다.", 0.7);
        return;
    }

    // [ID 역추적] 슬롯 정보를 통해 DB에서 가격 조회
    const Slot& targetSlot = inv->GetSlot(displaySlot);
    int basePrice = 0;
    std::string itemName = "";

    // 타입에 맞는 DB 호출 (EquipID 등으로 형변환)
    if (targetSlot.type == ItemType::Equipment) {
        const auto& data = dbPtr->GetEquipItems(static_cast<EquipID>(targetSlot.id))[0];
        basePrice = data.Price; itemName = data.Name;
    }
    else if (targetSlot.type == ItemType::Potion) {
        const auto& data = dbPtr->GetPotionItems(static_cast<PotionID>(targetSlot.id))[0];
        basePrice = data.Price; itemName = data.Name;
    }
    else if (targetSlot.type == ItemType::Ingredient) {
        const auto& data = dbPtr->GetIngredItems(static_cast<IngredID>(targetSlot.id))[0];
        basePrice = data.Price; itemName = data.Name;
    }

    // 최종 판매 수량 확인 및 정산
    std::string strQty = UIHelper::UpdateBotInput(itemName + " 몇 개 판매? (보유:" + std::to_string(targetSlot.count) + ")");
    int sellQty = std::stoi(strQty);

    if (sellQty > 0 && sellQty <= targetSlot.count) {
        int reward = static_cast<int>(basePrice * 0.6) * sellQty;
        inv->RemoveItem(targetSlot.type, targetSlot.id, sellQty);
        player->AddGold(reward);
        UIHelper::UpdateBot(itemName + " 판매 완료! +" + std::to_string(reward) + "G", 1);
    }
}

