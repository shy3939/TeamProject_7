#include "Item.h"
#include "ItemDatabase.h"
#include "Player.h"
#include "EquipItem.h"
#include <iostream>

void EquipItem::Equip(Player* player)
{
    if (!player)
        return;

    const auto& equipList = db_.GetEquipItems(eid_);
    const auto& data = equipList[0];

    player->AddStat(
        data.BonusSTR,
        data.BonusAGI,
        data.BonusVIT,
        data.BonusINT,
        data.BonusLUK
    );

    std::cout << data.Name << " 장착 완료" << std::endl;
}

void EquipItem::Unequip(Player* player)
{
    if (!player)
        return;

    const auto& equipList = db_.GetEquipItems(eid_);
    const auto& data = equipList[0];

    player->AddStat(
        -data.BonusSTR,
        -data.BonusAGI,
        -data.BonusVIT,
        -data.BonusINT,
        -data.BonusLUK
    );

    std::cout << data.Name << " 장착 해제" << std::endl;
}
