#include "Item.h"
#include "ItemDatabase.h"
#include "Player.h"
#include "PotionItem.h"
#include <iostream>
#include <algorithm>

bool PotionItem::Use(Player* player)
{
    if (!player)
        return false;

    // DB에서 포션 데이터 가져오기
    const auto& potionList = db_.GetPotionItems(pid_);
    const auto& data = potionList[0]; // 지금은 0번(하급) 사용

    int curHp = player->GetHP();
    int maxHp = player->GetMaxHP();

    // 이미 체력이 가득 찬 경우
    if (curHp >= maxHp && data.PlusHP > 0)
    {
        std::cout << "이미 체력이 가득 차 있습니다." << std::endl;
        return false;
    }

    // HP 증가
    if (data.PlusHP > 0)
    {
        int healed = std::min(curHp + data.PlusHP, maxHp);
        player->SetHP(healed);

        std::cout << data.Name << " 사용! 체력 +"
            << data.PlusHP << std::endl;
        std::cout << "현재 체력: " << player->GetHP() << std::endl;
    }

    // ATK 증가 포션도 여기서 처리 가능
    if (data.PlusATK > 0)
    {
        player->SetATK(player->GetATK() + data.PlusATK);

        std::cout << data.Name << " 사용! 공격력 +"
            << data.PlusATK << std::endl;
        std::cout << "현재 공격력: " << player->GetATK() << std::endl;
    }

    return true;
}