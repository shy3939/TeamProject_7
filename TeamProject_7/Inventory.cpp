#include "Inventory.h"
#include <iostream>

void Inventory::AddItem(const std::string& key)
{
    items_[key]++;
    std::cout << key << " 아이템이 인벤토리에 추가되었습니다." << std::endl;
}

void Inventory::RemoveItem(const std::string& key)
{
    auto it = items_.find(key);

    if (it == items_.end())
    {
        std::cout << "해당 아이템이 없습니다." << std::endl;
        return;
    }

    if (--it->second <= 0)
    {
        items_.erase(it);
        std::cout << key << " 아이템이 인벤토리에서 제거되었습니다." << std::endl;

    }
}

void Inventory::ShowInventory() const
{
    std::cout << "인벤토리가 열렸습니다." << std::endl;


    if (items_.empty())
    {
        std::cout << "인벤토리가 비어있습니다." << std::endl;
        return;
    }

    for (const auto& pair : items_)
    {
        std::cout << "- " << pair.first
            << " x" << pair.second << std::endl;
    }
}

const std::map<std::string, int>& Inventory::GetInventory() const
{
    return items_;
}