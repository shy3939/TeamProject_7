// ShopField.cpp
#include "ShopField.h"
#include "Inventory.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

// [1] 생성자: 상점의 기본 아이템 풀(Pool) 설정
ShopField::ShopField() {
    // 랜덤 매대에 올라올 후보 아이템들을 등록
    // (포션류는 고정 판매이므로 여기서 제외하여 중복 등장을 방지)
    ItemPool.push_back({ "아이템1", 500, 500 });
    ItemPool.push_back({ "아이템2", 200, 200 });
    ItemPool.push_back({ "아이템3", 300, 300 });
    ItemPool.push_back({ "아이템4", 1000, 1000 });
    ItemPool.push_back({ "아이템5", 1500, 1500 });
}
// [2] 입장 함수: 매대 새로고침 및 메인 루프 실행
void ShopField::Enter(Player* player)
{
    RefreshShop(); // 상점 입장 시마다 아이템 구성을 새로고침
    std::cout << "========================================" << std::endl;
    std::cout << "      🏪 상점에 입장했습니다! 🏪        " << std::endl;
    std::cout << "========================================" << std::endl;

    while (1)
    {
        std::cout << std::endl;
        std::cout << " 보유 골드 : " << player->GetGold() << " G" << std::endl;
        ShowMenu();

        int Choice;
        // 숫자가 아닌 입력이 들어왔을 때의 예외 처리
        if (!(std::cin >> Choice))
        {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            continue;
        }

        switch (Choice)
        {
        case 1: BuyItem(player); break;
        case 2: SellItem(player); break;
        case 3: player->ShowStatus(); break;
        case 4: player->GetInventory()->ShowInventory(); break;
        case 0:
            std::cout << " 다음에도 살아서 만나요~ " << std::endl;
            return;
        default:
            std::cout << " 잘못된 입력입니다. " << std::endl;
            break;
        }
    }
}
// [3] 메뉴 UI 출력
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
// [4] 판매 목록 UI: 고정 상품과 랜덤 상품을 구분하여 출력
void ShopField::ShowShopItems()
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[오늘의 상품 목록]" << std::endl;

    // 1 & 2번은 변하지 않는 고정 필수 아이템
    std::cout << " 1. 체력 포션 \t| 가격: " << HealthPotionPrice << " G (고정)" << std::endl;
    std::cout << " 2. 공격력 포션 \t| 가격: " << AttackPotionPrice << " G (고정)" << std::endl;
    
    // 3번부터는 RefreshShop에 의해 결정된 랜덤 아이템들
    for (int i = 0; i < CurrentStock.size(); ++i) 
    {
        std::cout << " " << i + 3 << ". " << CurrentStock[i].Name
            << " \t| 가격: " << CurrentStock[i].CurrentPrice << " G" << std::endl;
    }

    std::cout << " 0. 취소 " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}
// [5] 아이템 구매 로직: 선택 번호에 따른 인덱스 매핑이 핵심
void ShopField::BuyItem(Player* player)
{
    ShowShopItems();
    if (CurrentStock.empty()) return;
    
    std::cout << " 구매할 아이템 번호: ";
    int Choice;
    std::cin >> Choice;

    if (Choice == 0) return;

    std::string finalName;
    int finalPrice = 0;
    bool isEquipment = false;

    // 번호에 따른 아이템 판별
    if (Choice == 1) 
    {   
        finalName = "체력 포션";
        finalPrice = HealthPotionPrice;
    }
    else if (Choice == 2) 
    {   
        finalName = "공격력 포션";
        finalPrice = AttackPotionPrice;
    }
    else if (Choice >= 3 && Choice < 3 + (int)CurrentStock.size()) 
    {
        // 3번 이상 선택 시 랜덤 리스트(CurrentStock)에서 인덱스 계산 (선택번호 - 3)
        ShopItem& selected = CurrentStock[Choice - 3];
        finalName = selected.Name;
        finalPrice = selected.CurrentPrice;
        isEquipment = true; // 3번 이후는 장비 아이템으로 간주
    }
    else 
    {
        std::cout << "잘못된 번호입니다." << std::endl;
        return;
    }

    // 2. 수량 입력 및 확인
    int Quantity = 1;
    if (!isEquipment) {
        // [포션] 수량을 입력받음
        std::cout << finalName << "을(를) 몇 개 구매하시겠습니까?: ";
        std::cin >> Quantity;
        if (Quantity <= 0) return;
    }
    else {
        // [장비] 단품 구매 확인만 거침
        std::cout << finalName << "을(를) 구매하시겠습니까? (1.예 / 0.아니오): ";
        int confirm;
        std::cin >> confirm;
        if (confirm != 1) return;
        Quantity = 1;
    }

    // 3. 골드 체크 및 결제
    int TotalPrice = finalPrice * Quantity;
    if (player->GetGold() < TotalPrice) {
        std::cout << " 골드가 부족합니다! " << std::endl;
        return;
    }

    player->SpendGold(TotalPrice);
    player->GetInventory()->AddItem(finalName, id, Quantity);

    // 4. 아이템 종류에 따른 출력 문구 차별화
    std::cout << " --------------------------------------- " << std::endl;
    if (isEquipment) {
        // 장착형 아이템: "✅ [아이템이름] 구매 완료!"
        std::cout << " ✅ " << finalName << " 구매 완료!" << std::endl;
    }
    else {
        // 소모품(포션): "✅ [아이템이름] [개수]개 구매 완료!"
        std::cout << " ✅ " << finalName << " " << Quantity << "개 구매 완료!" << std::endl;
    }
    std::cout << " --------------------------------------- " << std::endl;
}


void ShopField::SellItem(Player* player)
{
    // [1] 사전 검사: 인벤토리 포인터를 가져오고 비어있는지 확인합니다.
    Inventory* inventory = player->GetInventory();

    // 인벤토리 비어있는지 확인
    if (inventory->IsEmpty())
    {
        std::cout << "판매할 아이템이 없습니다." << std::endl;
        return;
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[보유 아이템] (판매가는 구입가의 60%)" << std::endl;


    // [2] 마스터 리스트 작성: 상점이 가격 정보를 알고 있는 모든 품목을 모음
    // 고정 상품(포션)과 랜덤 상품(ItemPool)을 하나의 벡터에 임시로 합침
    std::vector<ShopItem> AllPossibleItems;
    
    // 고정 상품(포션) 정보 추가
    AllPossibleItems.push_back({ "체력 포션", HealthPotionPrice, HealthPotionPrice });
    AllPossibleItems.push_back({ "공격력 포션", AttackPotionPrice, AttackPotionPrice });

    // ItemPool(랜덤 상품 후보군)에 있는 정보들을 추가
    for (const auto& item : ItemPool)
    {
        AllPossibleItems.push_back(item);
    }

    // [3] 필터링: 플레이어가 실제로 가지고 있는 아이템만 골라냄
    // 사용자가 입력할 번호(1, 2, 3...)와 실제 아이템 객체를 매핑하기 위해 포인터(*) 벡터를 활용
    std::vector<ShopItem*> SellableItems;

    for (int i = 0; i < AllPossibleItems.size(); ++i)
    {
        // 인벤토리 클래스에 해당 아이템 이름의 개수가 1개 이상인지 확인
        int count = inventory->GetItemCount(AllPossibleItems[i].Name);
        if (count > 0)
        {
            // 실제 보유 중인 아이템만 판매 가능 목록(SellableItems)에 저장
            SellableItems.push_back(&AllPossibleItems[i]);

            // 판매가 계산: 기준 가격(BasePrice)의 60%
            int sellPrice = static_cast<int>(AllPossibleItems[i].BasePrice * 0.6);
            // 화면에는 1번부터 순차적으로 보이게 출력
            std::cout << SellableItems.size() << ". " << AllPossibleItems[i].Name
                << " - " << count << "개 보유 (개당 " << sellPrice << " G)" << std::endl;
        }
    }
    // [4] 예외 처리: 인벤토리에 아이템은 있지만, 상점에서 안 사는 물건만 있을 경우
    if (SellableItems.empty())
    {
        std::cout << "상점에서 매입하는 아이템을 보유하고 있지 않습니다." << std::endl;
        return;
    }

    std::cout << "0. 취소" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "판매할 아이템 번호: ";

    // [5] 입력 처리: 어떤 아이템을 팔지 결정
    int Choice;
    if (!(std::cin >> Choice) || Choice == 0) return; // 입력 오류 및 취소 처리

    if (Choice < 1 || Choice >(int)SellableItems.size())
    {
        std::cout << "잘못된 선택입니다." << std::endl;
        return;
    }

    // [6] 정보 추출: 선택한 아이템의 포인터를 통해 이름과 원가를 가져옴
    ShopItem* selected = SellableItems[Choice - 1];
    int ownedCount = inventory->GetItemCount(selected->Name);
    int sellPricePerOne = static_cast<int>(selected->BasePrice * 0.6);

    // [7] 수량 결정: 팔고자 하는 개수를 입력받고 보유 수량을 넘지 않는지 체크
    std::cout << selected->Name << "을(를) 몇 개 판매하시겠습니까? (보유: " << ownedCount << "개): ";
    int Quantity;
    std::cin >> Quantity;

    if (Quantity <= 0 || Quantity > ownedCount)
    {
        std::cout << "수량이 올바르지 않습니다." << std::endl;
        return;
    }
    // [8] 최종 정산: 인벤토리에서 제거하고 플레이어에게 골드를 지급
    int TotalGold = sellPricePerOne * Quantity;
    inventory->RemoveItem(selected->Name, Quantity); // 인벤토리 데이터 갱신
    player->AddGold(TotalGold);                      // 플레이어 재화 갱신

    std::cout << "✅ " << selected->Name << " " << Quantity << "개 판매 완료!" << std::endl;
    std::cout << "💰 획득 골드: " << TotalGold << " G" << std::endl;
}

void ShopField::RefreshShop()
{
    // 1. 현재 진열대 비우기
    CurrentStock.clear(); 

    // 2. 랜덤 엔진 설정
    std::random_device rd;
    std::mt19937 g(rd());

    // 3. 전체 목록을 무작위로 섞기
    std::shuffle(ItemPool.begin(), ItemPool.end(), g);

    // 4. 섞인 목록의 앞부분에서 MaxDisplayCount만큼 가져오기
    for (int i = 0; i < MaxDisplayCount && i < ItemPool.size(); ++i) 
    {
        ShopItem item = ItemPool[i];

        // 5. 가격 랜덤화 (예: 80% ~ 120% 사이)
        float ratio = (80 + (rand() % 41)) / 100.0f;
        item.CurrentPrice = static_cast<int>(item.BasePrice * ratio);

        CurrentStock.push_back(item);
    }
}
