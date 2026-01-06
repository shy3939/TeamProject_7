#pragma once
#include "Item.h"
#include "ItemEnum.h"

class IngredItem : public Item
{
public:
    IngredItem(IngredID id, const ItemDatabase& db)
        : Item(db), gid_(id)
    {
    }

    ItemType GetType() const override { return ItemType::Ingredient; }

    bool Use(Player* player) override
    {
        return false;
    }

private:
    IngredID gid_;
};
