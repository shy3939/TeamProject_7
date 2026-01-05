#include <windows.h>
#include "utf.h"
#include "Player.h"
#include "GameField.h"
#include "ShopField.h"
#include "UIHelper.h"
#include "AsciiArt.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main()
{
    SetConsoleOutputCP(65001);
    srand(time(nullptr));

    for (const auto& frame : AsciiArt::TITLE) {
        UIHelper::UpdateTop(frame, 0.7);
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
    Player* player = new Player(PlayerName);
    GameField* gamefield = new GameField();
    //ShopField* shopfield = new ShopField();

    UIHelper::UpdateStatus(player);

    while (1)
    {
        gamefield->Enter(player);
        gamefield->ShowLog();

        if (gamefield->GetGameIsOver())
        {
            break;
        }

        /*
        // 상점 선택 루프
        while (1)
        {
            char bShop;
            std::cout << " 상점에서 아이템을 구매하시겠습니까? (y/n) " << std::endl;
            std::cin >>bShop;

            switch (bShop)
            {
            case 'y':
            case 'Y':
                //shopfield->Enter(player);
                break;
            case 'n':
            case 'N':
                std::cout << " 상점을 지나쳤다 " << std::endl;
                break;
            default:
                std::cout << " 잘못된 입력입니다. 다시 입력해주세요 " << std::endl;
                continue;
            }
            break;
        }
        */
    }

    Sleep(10000);
    delete player;
    delete gamefield;
    //delete shopfield;
    return 0;
}