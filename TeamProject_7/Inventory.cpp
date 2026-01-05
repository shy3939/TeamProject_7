#include "Inventory.h"
#include <iostream>
#include "ItemEnum.h"
#include "Item.h"
#include "Player.h"
#include "UIHelper.h"

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
	if (player == nullptr) return;
	auto itemIt = items_.find(key);
	auto dataIt = itemData_.find(key);
	if (itemIt == items_.end() || dataIt == itemData_.end()) {
		UIHelper::UpdateBot(" 해당하는 아이템이 인벤토리에 존재하지 않습니다. ", 1);
		return;
	}
	dataIt->second->Use(player);
	if (--itemIt->second <= 0) // 수량 감소
		std::cout << "아이템 사용" << std::endl;
		items_.erase(itemIt);
}

void Inventory::AddItem(ItemType type, int id, int count)
{
	if (itemData_.find(key) == itemData_.end())
	{
		UIHelper::UpdateBot("존재하지 않는 아이템입니다.", 1);
		return;
	}
	items_[key]++;  // 삽입 목적이라 이건 OK
	UIHelper::UpdateBot(key + "이(가) 인벤토리에 추가되었습니다.", 1);
}

void Inventory::Use(int displaySlot, Player* player)
{
	auto it = items_.find(key);
	if (it == items_.end())
	{
		UIHelper::UpdateBot(" 해당하는 아이템이 인벤토리에 존재하지 않습니다. ", 1);
		return;
	}
	if (--it->second <= 0)
	{
		items_.erase(it);
		UIHelper::UpdateBot(" 아이템이 인벤토리에서 제거되었습니다.", 1);
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
