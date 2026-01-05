#include "Inventory.h"
#include <iostream>
#include "ItemEnum.h"
#include "Item.h"
#include "Player.h"

Inventory::Inventory()
{
    // 슬롯 30칸 생성 (기본값 Slot 사용)
    slots_.assign(MAX_SLOT, Slot());

    // 아이템 데이터 등록
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

void Inventory::RemoveItem(ItemType type, int id, int count)
{
    int remaining = count;

    for (int i = 1; i < MAX_SLOT && remaining > 0; ++i)
    {
        Slot& slot = slots_[i];

        if (!slot.IsEmpty() &&
            slot.type == type &&
            slot.id == id)
        {
            // 슬롯에 있는 개수가 충분한 경우
            if (slot.count > remaining)
            {
                slot.count -= remaining;
                remaining = 0;
            }
            // 슬롯 개수가 부족하거나 정확히 같은 경우
            else
            {
                remaining -= slot.count;
                slot.Clear();
            }
        }
    }

    if (remaining > 0)
    {
        std::cout << "제거할 아이템 수량이 부족합니다." << std::endl;
    }
}

int Inventory::FindSameItemSlot(ItemType type, int id) const
{
    for (int i = 1; i < MAX_SLOT; ++i)
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
    for (int i = 1; i < MAX_SLOT; ++i)
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
        return;
    }

    int emptySlot = FindEmptySlot();
    if (emptySlot == -1)
    {
        std::cout << "인벤토리가 가득 찼습니다." << std::endl;
        return;
    }

    slots_[emptySlot].type = type;
    slots_[emptySlot].id = id;
    slots_[emptySlot].count = count;
}

void Inventory::Use(int displaySlot, Player* player)
{
    if (!player) return;

    int index = displaySlot - 1;
    if (index < 1 || index >= MAX_SLOT || slots_[index].IsEmpty())
    {
        std::cout << "비어있는 슬롯입니다." << std::endl;
        return;
    }

    Slot& slot = slots_[index];

    auto it = itemData_.find(slot.id);
    if (it == itemData_.end())
    {
        std::cout << "아이템 데이터 없음" << std::endl;
        return;
    }

    // 타입별 처리
    switch (slot.type)
    {
    case ItemType::Potion:
        itemData_[slot.id]->Use(player);
        break;

    case ItemType::Equipment:
        std::cout << "장비는 장착만 가능합니다." << std::endl;
        break;

    case ItemType::Ingredient:
        std::cout << "재료는 사용할 수 없습니다." << std::endl;
        break;
    }
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

    for (int i = 1; i < MAX_SLOT; ++i)
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
