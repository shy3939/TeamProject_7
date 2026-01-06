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