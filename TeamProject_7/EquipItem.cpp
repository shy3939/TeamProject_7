#include "Item.h"
#include "ItemDatabase.h"
#include "Player.h"
#include "EquipItem.h"
#include "Inventory.h"
#include <iostream>

bool EquipItem::Use(Player* player)
{
    if (!player) return false;

    // 1. 플레이어에게 장착 명령
    player->Equip(eid_);

    // 2. 장착했으므로 인벤토리에서 해당 아이템 1개 제거
    player->GetInventory()->RemoveItem(ItemType::Equipment, (int)eid_, 1);

    return true;
}
