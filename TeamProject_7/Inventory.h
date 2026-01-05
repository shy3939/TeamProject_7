#pragma once

#include <vector>
#include <map>
#include "ItemEnum.h"

class Item;
class Player;

struct Slot
{
    ItemType type;   // "무엇이 들어있나"
    int id;          // 구체적인 아이템 ID
    int count;

    bool IsEmpty() const
    {
        return count <= 0;
    }

    void Clear()
    {
        id = -1;
        count = 0;
        // type은 의미 없으므로 굳이 초기화 안 해도 됨
    }
};
class Inventory
{
public:
    Inventory();
    ~Inventory();

    // 슬롯 번호는 1 ~ 30
    bool IsSlotAvailable(int displaySlot) const;
    void Use(int displaySlot, Player* player);

    void AddItem(ItemType type, int id, int count = 1);
    int GetItemCount(ItemType type, int id) const;

    void ShowInventory() const;

private:
    static const int MAX_SLOT = 30;
    std::vector<Slot> slots_;

    // enum id → Item*
    std::map<int, Item*> itemData_;

    int FindSameItemSlot(ItemType type, int id) const;
    int FindEmptySlot() const;
};
