#include "Inventory.h"
#include <iostream>
#include "ItemEnum.h"
#include "Item.h"
#include "Player.h"
#include "UIHelper.h"

Inventory::Inventory()
{
    slots_.assign(MAX_SLOT, Slot());

    itemData_[(int)PotionID::HPPotion] = new HpPotion();
    itemData_[(int)PotionID::ATKPotion] = new AtkPotion();
}

Inventory::~Inventory()
{
    for (auto& pair : itemData_)
        delete pair.second;

    itemData_.clear();
}

bool Inventory::IsAvailable(int displaySlot) const
{
    int index = displaySlot - 1;
    if (index < 0 || index >= MAX_SLOT)
        return false;

    return !slots_[index].IsEmpty();
}

int Inventory::FindSameItemSlot(ItemType type, int id) const
{
    for (int i = 0; i < MAX_SLOT; ++i)
    {
        if (!slots_[i].IsEmpty() &&
            slots_[i].type == type &&
            slots_[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

int Inventory::FindEmptySlot() const
{
    for (int i = 0; i < MAX_SLOT; ++i)
    {
        if (slots_[i].IsEmpty())
            return i;
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

    for (int i = 0; i < MAX_SLOT && remaining > 0; ++i)
    {
        Slot& slot = slots_[i];

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

    auto it = itemData_.find(slot.id);
    if (it == itemData_.end())
    {
        UIHelper::UpdateBot("아이템 데이터가 없습니다.", 1);
        return;
    }

    it->second->Use(player);

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

    for (int i = 0; i < MAX_SLOT; ++i)
    {
        std::cout << "[" << i + 1 << "] ";

        if (slots_[i].IsEmpty())
            std::cout << "----\t";
        else
            std::cout << "ID:" << slots_[i].id
            << " x" << slots_[i].count << "\t";

        if ((i + 1) % 5 == 0)
            std::cout << std::endl;
    }

    std::cout << "=====================" << std::endl;
    std::cout << std::endl;
}
