#include "Inventory.h"
#include "PotionItem.h"
#include "EquipItem.h"
#include "IngredItem.h"
#include "ItemDatabase.h"
#include <iostream>
#include "ItemEnum.h"
#include "Item.h"
#include "Player.h"
#include "UIHelper.h"



Inventory::Inventory(const ItemDatabase& db)
    : db_(db)
{
    slots_.assign(MAX_SLOT, Slot());

    itemData_.emplace(
        ItemKey{ ItemType::Potion, (int)PotionID::HPPotion },
        std::make_unique<PotionItem>(PotionID::HPPotion, db_)
    );

    itemData_.emplace(
        ItemKey{ ItemType::Potion, (int)PotionID::ATKPotion },
        std::make_unique<PotionItem>(PotionID::ATKPotion, db_)
    );
}


Inventory::~Inventory()
{}

bool Inventory::IsEmpty() const            // 맵이 아예 통째로 비여있는지 모든 아이템이 없으면 true 아이템이 하나라도 있으면 false
{
    for (const Slot& slot : slots_)
    {
        if (!slot.IsEmpty())
            return false;
    }
    return true;
}

bool Inventory::IsAvailable(int displaySlot) const
{
    int index = displaySlot - 1;
    if (index < 0 || index >= MAX_SLOT)
    {
        return false;
    }
    return !slots_[index].IsEmpty();
}

const Slot& Inventory::GetSlot(int displaySlot) const
{
    int index = displaySlot - 1; // 1~30번 입력을 0~29 인덱스로 변환
    return slots_[index];
}

int Inventory::FindSameItemSlot(ItemType type, int id) const
{
    for (int index = 0; index < MAX_SLOT; ++index)
    {
        if (!slots_[index].IsEmpty() &&
            slots_[index].type == type &&
            slots_[index].id == id)
        {
            return index;
        }
    }
    return -1;
}

int Inventory::FindEmptySlot() const
{
    for (int index = 0; index < MAX_SLOT; ++index)
    {
        if (slots_[index].IsEmpty())
            return index;
    }
    return -1;
}

void Inventory::AddItem(ItemType type, int id, int count)
{
    int sameSlot = FindSameItemSlot(type, id);
    if (sameSlot != -1)
    {
        slots_[sameSlot].count += count;
        UIHelper::UpdateBot("아이템 수량이 증가했습니다.", 1);
        return;
    }

    int emptySlot = FindEmptySlot();
    if (emptySlot == -1)
    {
        UIHelper::UpdateBot("인벤토리가 가득 찼습니다.", 1);
        return;
    }

    slots_[emptySlot].type = type;
    slots_[emptySlot].id = id;
    slots_[emptySlot].count = count;

    UIHelper::UpdateBot("아이템을 획득했습니다.", 1);
}

void Inventory::RemoveItem(ItemType type, int id, int count)
{
    int remaining = count;

    if (count <= 0) return;

    for (int index = 0; index < MAX_SLOT && remaining > 0; ++index)
    {
        Slot& slot = slots_[index];

        if (!slot.IsEmpty() &&
            slot.type == type &&
            slot.id == id)
        {
            if (slot.count > remaining)
            {
                slot.count -= remaining;
                remaining = 0;
            }
            else
            {
                remaining -= slot.count;
                slot.Clear();
            }
        }
    }

    if (remaining > 0)
        UIHelper::UpdateBot("제거할 아이템 수량이 부족합니다.", 1);
}

void Inventory::Use(int displaySlot, Player* player)
{
    if (!player) return;

    int index = displaySlot - 1;
    if (index < 0 || index >= MAX_SLOT || slots_[index].IsEmpty())
    {
        UIHelper::UpdateBot("비어있는 슬롯입니다.", 1);
        return;
    }

    Slot& slot = slots_[index];

    ItemKey key{ slot.type, slot.id };

    auto it = itemData_.find(key);
    if (it == itemData_.end())
    {
        UIHelper::UpdateBot("아이템 데이터가 없습니다.", 1);
        return;
    }

    if (!it->second->Use(player))
    {
        UIHelper::UpdateBot("아이템을 사용할 수 없습니다.", 1);
        return;
    }

    if (--slot.count <= 0)
        slot.Clear();
}

int Inventory::GetItemCount(ItemType type, int id) const
{
    int total = 0;

    for (const auto& slot : slots_)
    {
        if (!slot.IsEmpty() &&
            slot.type == type &&
            slot.id == id)
        {
            total += slot.count;
        }
    }
    return total;
}

void Inventory::ShowInventory() const
{
    std::cout << std::endl;
    std::cout << "====== 인벤토리 ======" << std::endl;

    for (int index = 0; index < MAX_SLOT; ++index)
    {
        std::cout << "[" << index + 1 << "] ";

        if (slots_[index].IsEmpty())
            std::cout << "----\t";
        else
            std::cout << "ID:" << slots_[index].id
            << " x" << slots_[index].count << "\t";

        if ((index + 1) % 5 == 0)
            std::cout << std::endl;
    }

    std::cout << "=====================" << std::endl;
    std::cout << std::endl;
}
