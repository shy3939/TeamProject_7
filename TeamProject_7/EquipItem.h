#pragma once
#include "Item.h"
#include "ItemEnum.h"

class EquipItem : public Item
{
public:
    EquipItem(EquipID id, const ItemDatabase& db)
        : Item(db), eid_(id)
    {
    }

    ItemType GetType() const override { return ItemType::Equipment; }

    bool Use(Player* player) override;
    void Equip(Player* player);
    void Unequip(Player* player);

private:
    EquipID eid_;
};