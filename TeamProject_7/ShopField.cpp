// ShopField.cpp
#include "ShopField.h"
#include "Inventory.h"
#include "UIHelper.h"
#include "AsciiArt.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

// [1] 생성자: 상점의 기본 아이템 풀(Pool) 설정
ShopField::ShopField(const ItemDatabase& db) : m_DB(db) {
    // ItemPool 초기화 - ItemDatabase에서 장비 정보를 가져옴
    std::vector<EquipID> shopEquips = {
        EquipID::NormalSword, EquipID::SharpSword,
        EquipID::NormalBow, EquipID::SturdyBow,
        EquipID::NormalStaff,
        EquipID::NormalSpear,
        EquipID::NormalAxe,
        EquipID::NormalDagger,
        EquipID::NormalArmor,
        EquipID::NormalGloves,
        EquipID::NormalShoes
    };

    for (EquipID eid : shopEquips) {
        const auto& equipData = m_DB.GetEquipItems(eid)[0]; // 첫 번째 변형 사용
        ItemPool.push_back({
            equipData.Name,
            ItemType::Equipment,
            (int)eid,
            equipData.Price,
            equipData.Price
        });
    }
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
        std::string Choice =  UIHelper::UpdateBotInput("[상점 메뉴] : 1. 아이템 구매  2. 아이템 판매 3. 나가기 ");

        if (Choice == "1") {
            BuyItem(player);
        }
        else if (Choice == "2") {
            SellItem(player);
        }
        else if (Choice == "3") {
            UIHelper::UpdateBot("다음에도 살아서 만나요~ ", 1);
            return;
        }
        else {
            UIHelper::UpdateBot("잘못된 입력입니다 !", 0.5);
        }
    }
}

// [5] 아이템 구매 로직: 선택 번호에 따른 인덱스 매핑이 핵심
void ShopField::BuyItem(Player* player)
{
//////////////////////
    // 1. 구매할 아이템 선택
    if (CurrentStock.empty()) return;
    
    std::string strChoice = UIHelper::UpdateBotInput("구매할 아이템 번호를 입력해주세요");
   
    // 빈 문자열 체크
    if (strChoice.empty()) {
        UIHelper::UpdateBot("숫자를 입력해주세요 : 구매를 취소합니다!", 0.5);
        return;
    }

    // 전체가 숫자인지 체크
    size_t pos;
    int Choice = std::stoi(strChoice, &pos);

    if (pos != strChoice.length()) {
        UIHelper::UpdateBot("숫자만 입력해주세요 : 구매를 취소합니다 !", 0.5);
        return;
    }

    if (Choice == 0) return;

    std::string finalName;
    int finalPrice = 0;
    bool isEquipment = false;

    
    // 번호에 따른 아이템 판별
    if (Choice == 1 || Choice == 2) 
    {   
        isEquipment = false;
    }
    else if (Choice >= 3 && Choice <= CurrentStock.size())

    {
        isEquipment = true; // 3번 이후는 장비 아이템으로 간주
    }
    else 
    {
        UIHelper::UpdateBot("잘못된 번호 : 구매를 취소합니다 !", 0.5);
        return;
    }

    ShopItem& selected = CurrentStock[Choice - 1];
    finalName = selected.Name;
    finalPrice = selected.CurrentPrice;

////////////////////
    // 2. 수량 입력 및 확인
    int Quantity;
    if (!isEquipment) {
        // [포션] 수량을 입력받음
        std::string strQunatity = UIHelper::UpdateBotInput(finalName + "을(를) 몇 개 구매하시겠습니까?");

        // 빈 문자열 체크
        if (strQunatity.empty()) {
            UIHelper::UpdateBot("숫자를 입력해주세요 : 구매를 취소합니다!", 0.5);
            return;
        }

        // 전체가 숫자인지 체크
        size_t pos;
        Quantity = std::stoi(strQunatity, &pos);

        if (pos != strQunatity.length()) {
            UIHelper::UpdateBot("숫자만 입력해주세요 : 구매를 취소합니다 !", 0.5);
            return;
        }

        if (Quantity <= 0) {
            UIHelper::UpdateBot("잘못된 수량 : 구매를 취소합니다 !", 0.5);
            return;
        }
    }

    else {
        // [장비] 단품 구매 확인만 거침
        char Confirm;
        std::string strConfirm = UIHelper::UpdateBotInput(finalName + "을(를) 구매하시겠습니까? ( y / n )");
        
        if (strConfirm.length() != 1) {
            UIHelper::UpdateBot("잘못된 입력입니다. 구매를 취소합니다.", 1);
            return;
        }
    
        Confirm = strConfirm[0];
    
        switch (Confirm)
        {
        case 'y':
        case 'Y':
            Quantity = 1;
            break;
        case 'n':
        case 'N':
            UIHelper::UpdateBot("구매를 취소합니다 !", 0.5);
            return;
        default:
            UIHelper::UpdateBot("잘못된 입력 : 구매를 취소합니다 !", 0.5);
            return;
        }
    }

    // 3. 골드 체크 및 결제
    int TotalPrice = finalPrice * Quantity;
    if (player->GetGold() < TotalPrice) {
        UIHelper::UpdateBot("보유 골드가 부족합니다 : 구매를 취소합니다 !", 0.5);
        return;
    }

    player->SpendGold(TotalPrice);
    player->GetInventory()->AddItem(selected.ItemType, selected.ItemId, Quantity);
    UIHelper::UpdateStatus(player);

    // 4. 아이템 종류에 따른 출력 문구 차별화
    if (isEquipment) {
        UIHelper::UpdateBot("[" + finalName + "]" + " 구매 완료!", 1);
    }
    else {
        // 소모품(포션): "✅ [아이템이름] [개수]개 구매 완료!"
        UIHelper::UpdateBot("[" + finalName + "] " + std::to_string(Quantity) +"개 구매 완료!", 1);
    }
}
void ShopField::CloseSellUI()
{
    UIHelper::UpdateTop(AsciiArt::ShopBackGround);
    for (int i = 0; i < 6; ++i) {
        UIHelper::AddToShopList(CurrentStock[i].Name, std::to_string(CurrentStock[i].CurrentPrice) , i);
    }
}

void ShopField::SellItem(Player* player)
{
    // [1] 사전 검사: 인벤토리 포인터를 가져오고 비어있는지 확인합니다.
    Inventory* inventory = player->GetInventory();

    // 인벤토리 비어있는지 확인
    if (inventory->IsEmpty())
    {
        UIHelper::UpdateBot("판매할 아이템이 없습니다.", 1);
        CloseSellUI();
        return;
    }

    UIHelper::UpdateBot("알림 ! : 판매가는 구입가의 60%입니다", 0.7);

    // [2] 마스터 리스트 작성: 상점이 가격 정보를 알고 있는 모든 품목을 모음
    // 고정 상품(포션)과 랜덤 상품(ItemPool)을 하나의 벡터에 임시로 합침
    std::vector<ShopItem> AllPossibleItems;

    // 고정 상품(포션) 정보 추가
    AllPossibleItems.push_back({ "체력 포션", ItemType::Potion, (int)PotionID::HPPotion, HealthPotionPrice, HealthPotionPrice});
    AllPossibleItems.push_back({ "공격력 포션", ItemType::Potion, (int)PotionID::ATKPotion, AttackPotionPrice, AttackPotionPrice });

    // ItemPool(랜덤 상품 후보군)에 있는 정보들을 추가
    for (const auto& item : ItemPool)
    {
        AllPossibleItems.push_back(item);
    }

    // [3] 필터링: 플레이어가 실제로 가지고 있는 아이템만 골라냄
    // 사용자가 입력할 번호(1, 2, 3...)와 실제 아이템 객체를 매핑하기 위해 포인터(*) 벡터를 활용
    std::vector<ShopItem*> SellableItems;
    std::vector<std::string> displayLines;  // Top 영역에 표시할 리스트

    for (int i = 0; i < AllPossibleItems.size(); ++i)
    {
        // 인벤토리 클래스에 해당 아이템 이름의 개수가 1개 이상인지 확인
        int count = inventory->GetItemCount(AllPossibleItems[i].ItemType, AllPossibleItems[i].ItemId);

        if (count > 0)
        {
            // 실제 보유 중인 아이템만 판매 가능 목록(SellableItems)에 저장
            SellableItems.push_back(&AllPossibleItems[i]);

            // 판매가 계산: 기준 가격(BasePrice)의 60%
            int sellPrice = static_cast<int>(AllPossibleItems[i].BasePrice * 0.6);
            // 리스트 항목 문자열 생성
            std::string line = std::to_string(SellableItems.size()) + ". " + AllPossibleItems[i].Name
                + " - " + std::to_string(count) + "개 보유 (개당 " + std::to_string(sellPrice) + " G)";
            displayLines.push_back(line);
        }
    }

    // [4] 예외 처리: 인벤토리에 아이템은 있지만, 상점에서 안 사는 물건만 있을 경우
    if (SellableItems.empty())
    {
        UIHelper::UpdateBot("상점에서 매입하는 아이템을 보유하고 있지 않습니다.", 1);
        CloseSellUI();
        return;
    }

    displayLines.push_back("0. 취소");

    // Top 영역에 판매 가능 아이템 리스트 표시
    UIHelper::UpdateTopList(displayLines, "판매 가능 아이템");

    // [5] 입력 처리: 어떤 아이템을 팔지 결정
    std::string strChoice = UIHelper::UpdateBotInput("판매할 아이템 번호를 입력하세요");

    if (strChoice.empty()) {
        CloseSellUI();
        UIHelper::UpdateBot("입력이 없습니다. 판매를 취소합니다.", 0.5);
        return;
    }

    size_t pos;
    int Choice;
    try {
        Choice = std::stoi(strChoice, &pos);
    } catch (...) {
        CloseSellUI();
        UIHelper::UpdateBot("잘못된 입력입니다. 판매를 취소합니다.", 0.5);
        return;
    }

    if (pos != strChoice.length()) {
        CloseSellUI();
        UIHelper::UpdateBot("숫자만 입력해주세요. 판매를 취소합니다.", 0.5);
        return;
    }

    if (Choice == 0)
    {
        CloseSellUI(); 
        return;
    }

    if (Choice < 1 || Choice > (int)SellableItems.size())
    {
        CloseSellUI();
        UIHelper::UpdateBot("잘못된 선택입니다.", 0.5);
        return;
    }

    // [6] 정보 추출: 선택한 아이템의 포인터를 통해 이름과 원가를 가져옴
    ShopItem* selected = SellableItems[Choice - 1];
    int ownedCount = inventory->GetItemCount(selected->ItemType, selected->ItemId);
    int sellPricePerOne = static_cast<int>(selected->BasePrice * 0.6);

    // [7] 수량 결정: 팔고자 하는 개수를 입력받고 보유 수량을 넘지 않는지 체크
    std::string strQuantity = UIHelper::UpdateBotInput(selected->Name + " 몇 개 판매? (보유: " + std::to_string(ownedCount) + "개)");

    if (strQuantity.empty()) {
        CloseSellUI();
        UIHelper::UpdateBot("입력이 없습니다. 판매를 취소합니다.", 0.5);
        return;
    }

    int Quantity;
    try {
        Quantity = std::stoi(strQuantity, &pos);
    } catch (...) {
        UIHelper::UpdateBot("잘못된 입력입니다. 판매를 취소합니다.", 0.5);
        CloseSellUI();
        return;
    }

    if (pos != strQuantity.length()) {
        UIHelper::UpdateBot("숫자만 입력해주세요. 판매를 취소합니다.", 0.5);
        CloseSellUI();
        return;
    }

    if (Quantity <= 0 || Quantity > ownedCount)
    {
        UIHelper::UpdateBot("수량이 올바르지 않습니다.", 0.5);
        CloseSellUI();
        return;
    }

    // [8] 최종 정산: 인벤토리에서 제거하고 플레이어에게 골드를 지급
    int TotalGold = sellPricePerOne * Quantity;
    inventory->RemoveItem(selected->ItemType, selected->ItemId, Quantity); // 인벤토리 데이터 갱신
    player->AddGold(TotalGold);                      // 플레이어 재화 갱신
    UIHelper::UpdateStatus(player);
    CloseSellUI();
    UIHelper::UpdateBot(selected->Name + " " + std::to_string(Quantity) + "개 판매 완료! (+" + std::to_string(TotalGold) + " G)", 1);
}

void ShopField::RefreshShop()
{
    // 1. 현재 진열대 비우기
    CurrentStock.clear();

    // 2. 고정 아이템 (포션) 추가 - 1번, 2번 슬롯
    CurrentStock.push_back({ "체력 포션", ItemType::Potion, (int)PotionID::HPPotion, HealthPotionPrice, HealthPotionPrice });
    CurrentStock.push_back({ "공격력 포션", ItemType::Potion, (int)PotionID::ATKPotion, AttackPotionPrice, AttackPotionPrice });

    // 3. 랜덤 엔진 설정
    std::random_device rd;
    std::mt19937 g(rd());

    // 4. 전체 목록을 무작위로 섞기
    std::shuffle(ItemPool.begin(), ItemPool.end(), g);

    // 5. 섞인 목록의 앞부분에서 MaxDisplayCount만큼 가져오기 (3번~6번 슬롯)
    for (int i = 0; i < MaxDisplayCount && i < (int)ItemPool.size(); ++i)
    {
        ShopItem item = ItemPool[i];

        // 6. 가격 랜덤화 (예: 80% ~ 120% 사이)
        float ratio = (80 + (rand() % 41)) / 100.0f;
        item.CurrentPrice = static_cast<int>(item.BasePrice * ratio);

        CurrentStock.push_back(item);
    }
}
