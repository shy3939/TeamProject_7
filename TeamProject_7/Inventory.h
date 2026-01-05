#pragma once
#include <memory>
#include <vector>
#include <map>
#include "ItemEnum.h"
#include "ItemDatabase.h"

class Item;
class Player;

struct Slot
{
    ItemType type = ItemType::None;
    int id = -1;
    int count = 0;

    bool IsEmpty() const
    {
        return count <= 0 ? true : false;
    }

    void Clear()
    {
        type = ItemType::None;
        id = -1;
        count = 0;
    }
};

class Inventory
{
public:
    Inventory(const ItemDatabase& db);
    ~Inventory();

    bool IsEmpty() const;
    bool IsAvailable(int displaySlot) const;

    void Use(int displaySlot, Player* player);

    void AddItem(ItemType type, int id, int count = 1);
    void RemoveItem(ItemType type, int id, int count = 1);

    int GetItemCount(ItemType type, int id) const;

    void ShowInventory() const;

private:
    static const int MAX_SLOT = 30;

    const ItemDatabase& db_;
    std::map<int, std::unique_ptr<Item>> itemData_;
    std::vector<Slot> slots_;

    int FindSameItemSlot(ItemType type, int id) const;
    int FindEmptySlot() const;
};
