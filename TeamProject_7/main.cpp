#include <windows.h>
#include "utf.h"
#include "Player.h"
#include "Inventory.h"
#include "GameField.h"
#include "ShopField.h"
#include "UIHelper.h"
#include "AsciiArt.h"
#include "ItemDatabase.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main()
{
    SetConsoleOutputCP(65001);
    srand(time(nullptr));

    for (const auto& frame : AsciiArt::TITLE) {
        //UIHelper::UpdateTop(frame, 0.5);
        UIHelper::UpdateTop(frame, 0.1);
    }

    UIHelper::Init();

    std::string PlayerName;

    while (1)
    {
        PlayerName = UIHelper::UpdateBotInput("플레이어의 이름을 정해주세요 ");

        // 빈 문자열 체크
        if (PlayerName.empty())
        {
            UIHelper::UpdateBot("경고 ! : 이름은 비워둘 수 없습니다! ", 1);
            continue;
        }

        // 공백만 있는지 체크
        bool OnlySpaces = true;
        for (char c : PlayerName)
        {
            if (c != ' ')
            {
                OnlySpaces = false;
                break;
            }
        }

        if (OnlySpaces)
        {
            UIHelper::UpdateBot("경고 ! : 올바른 이름을 입력해주세요! ", 1);
            continue;
        }
        break;
    }

    UIHelper::UpdateBot("용사 [" + PlayerName + "] 모험 시작!", 1);

    ItemDatabase db;
    Player* player = new Player(PlayerName, db);
    GameField* gamefield = new GameField();
    ShopField* shopfield = new ShopField(db);

    UIHelper::UpdateTop(AsciiArt::Hero);
    UIHelper::UpdateStatus(player);

    // 상점 선택 루프
    while (1)
    {
        if (gamefield->GetGameIsOver())
        {
            break;
        }
        
        char bSelect;
        std::string bSelectBuffer = UIHelper::UpdateBotInput("행동을 선택해 주세요 (1 : 전투 2 : 상점 3 : 인벤토리 4 : 장비 관리) " );
        
        if (bSelectBuffer.length() != 1) {
            UIHelper::UpdateBot("잘못된 입력입니다 : 다시 입력해주세요!", 1);
            continue;
        }

        bSelect = bSelectBuffer[0];

        switch (bSelect)
        {
        case '1':
            gamefield->Enter(player);
            gamefield->ShowLog();
            break;
        case '2':
            shopfield->Enter(player);
            break;
        case '3':
            {
            player->GetInventory()->ShowInventory();
            break;
            }
        case '4' :
        {
            // 장비 관리 메뉴
            while (true)
            {
                player->ShowEquipments();
                std::string equipInput = UIHelper::UpdateBotInput("장비 관리 (1:장착하기 2:해제하기 0:나가기) ");

                if (equipInput == "0") break;

                if (equipInput == "1") // 장착하기
                {
                    std::vector<std::string> equipList;
                    std::vector<int> originalSlots;
                    const auto& slots = player->GetInventory()->GetSlots();

                    for (int i = 0; i < slots.size(); ++i)
                    {
                        if (!slots[i].IsEmpty() && slots[i].type == ItemType::Equipment)
                        {
                            std::string itemName = db.GetEquipItems((EquipID)slots[i].id)[0].Name;
                            equipList.push_back("[" + std::to_string(equipList.size() + 1) + "] " + itemName);
                            originalSlots.push_back(i + 1);
                        }
                    }

                    if (equipList.empty())
                    {
                        UIHelper::UpdateBot("장착 가능한 장비가 인벤토리에 없습니다.", 1);
                        continue;
                    }

                    UIHelper::UpdateTopList(equipList, "장착 가능한 장비 목록");
                    std::string selectIdxStr = UIHelper::UpdateBotInput("장착할 장비 번호를 입력하세요 (0:취소): ");

                    if (selectIdxStr == "0") continue;

                    if (selectIdxStr.empty()) {
                        UIHelper::UpdateBot("번호를 입력해주세요.", 1);
                        continue;
                    }
                    std::cin.clear();

                    try {
                        int selectIdx = std::stoi(selectIdxStr);
                        if (selectIdx > 0 && selectIdx <= equipList.size())
                        {
                            if (player->GetInventory()->Use(originalSlots[selectIdx - 1], player))
                            {
                                UIHelper::UpdateBot("장비를 장착했습니다.", 1);
                            }
                        }
                        else {
                            UIHelper::UpdateBot("잘못된 번호입니다.", 1);
                        }
                    }
                    catch (...) {
                        UIHelper::UpdateBot("숫자를 입력해주세요.", 1);
                    }
                }
                else if (equipInput == "2") // 해제하기
                {
                    std::string unequipInput = UIHelper::UpdateBotInput("해제할 슬롯 (1:무기 2:방어구 3:장갑 4:신발 0:취소): ");
                    if (unequipInput == "0") continue;

                    EquipSlot targetSlot;
                    if (unequipInput == "1") targetSlot = EquipSlot::Weapon;
                    else if (unequipInput == "2") targetSlot = EquipSlot::Armor;
                    else if (unequipInput == "3") targetSlot = EquipSlot::Gloves;
                    else if (unequipInput == "4") targetSlot = EquipSlot::Shoes;
                    else {
                        UIHelper::UpdateBot("잘못된 입력입니다.", 1);
                        continue;
                    }

                    if (player->GetEquippedID(targetSlot) == EquipID::None)
                    {
                        UIHelper::UpdateBot("해당 슬롯에 장착된 장비가 없습니다.", 1);
                    }
                    else
                    {
                        player->Unequip(targetSlot);
                        UIHelper::UpdateBot("장비를 해제했습니다.", 1);
                    }
                }
                else
                {
                    UIHelper::UpdateBot("잘못된 입력입니다.", 1);
                }
            }
            break;
        }
        default:
            UIHelper::UpdateBot("잘못된 입력입니다. 다시 입력해주세요", 1);
            continue;
        }

        UIHelper::UpdateTop(AsciiArt::Hero);
        UIHelper::UpdateStatus(player);
    } 

    
    UIHelper::UpdateTop(AsciiArt::TITLE[0]);
    UIHelper::UpdateBot("플레이 해주셔서 감사합니다!", 5);

    delete player;
    delete gamefield;
    delete shopfield;
    return 0;
}