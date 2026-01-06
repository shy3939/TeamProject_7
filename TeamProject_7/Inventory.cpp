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
#include "utf.h"

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

int Inventory::GetSize() const
{
    int size = 0;
    for (const Slot& slot : slots_)
    {
        if (!slot.IsEmpty())
        {
            size++;
        }
    }
    return size;
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
    // 1. 인벤토리 데이터 준비
    std::vector<std::string> displayLines;

    if (IsEmpty())
    {
        displayLines.push_back("인벤토리가 비어 있습니다.");
    }
    else
    {
        // 인벤토리 내용을 문자열 리스트로 변환 (ID와 수량 표시)
        // Inventory 내부에서 직접 리스트를 반환하는 함수를 만들거나, 여기서 순회하며 생성
        for (int i = 1; i <= 30; ++i) // MAX_SLOT이 30이므로
        {
            if (IsAvailable(i))
            {
                // 예: [Slot 1] Item ID: 101 (3개)
                // 실제 구현 시 아이템 이름 정보를 ItemDatabase에서 가져오면 더 좋습니다.
                std::string line = "[슬롯 " + std::to_string(i) + "] 아이템 ID: " + std::to_string(i) + " x" + std::to_string(GetItemCount(ItemType::Potion, i));
                displayLines.push_back(line);
            }
        }
    }

    UIHelper::UpdateTopList(displayLines, "플레이어 인벤토리");
    UIHelper::UpdateBot("인벤토리를 닫으려면 [Enter]를 눌러주세요");
    GetEnterInput();
}
