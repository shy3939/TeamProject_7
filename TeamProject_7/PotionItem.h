#pragma once
#include "Item.h"
#include "ItemEnum.h"

class Player;
class ItemDatabase;

class PotionItem : public Item
{
public:
    PotionItem(PotionID id, const ItemDatabase& db)
        : Item(db), pid_(id)
    {
    }

    bool Use(Player* player) override;

private:
    PotionID pid_;
};
