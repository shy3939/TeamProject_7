#include "Item.h"
#include "ItemDatabase.h"
#include "Player.h"
#include "EquipItem.h"
#include <iostream>

bool EquipItem::Use(Player* player)
{
    if (!player) return false;
    player->Equipment(eid_);
    return true;
}
