#pragma once

#include <vector>
#include <map>
#include "ItemEnum.h"

class Item;
class Player;

struct Slot
{
    ItemType type = ItemType::Potion;
    int id = -1;
    int count = 0;

    bool IsEmpty() const
    {
        return count <= 0;
    }

    void Clear()
    {
        type = ItemType::Potion;
        id = -1;
        count = 0;
    }
};

class Inventory
{
public:
    Inventory();
    ~Inventory();

    bool IsEmpty() const;
    bool IsAvailable(int displaySlot) const;
    void Use(int displaySlot, Player* player);

    void AddItem(ItemType type, int id, int count = 1);
    void RemoveItem(ItemType type, int id, int count = 1);

    int GetItemCount(ItemType type, int id, int count = 1) const;

    void ShowInventory() const;

private:
    static const int MAX_SLOT = 30;
    std::vector<Slot> slots_;

    std::map<int, Item*> itemData_;

    int FindSameItemSlot(ItemType type, int id) const;
    int FindEmptySlot() const;
};
