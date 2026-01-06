#include "Item.h"
#include "ItemDatabase.h"
#include "Player.h"
#include "EquipItem.h"
#include <iostream>

bool EquipItem::Use(Player* player)
{
    if (!player) return false;
    player->Equip(eid_);
    return true;
}
