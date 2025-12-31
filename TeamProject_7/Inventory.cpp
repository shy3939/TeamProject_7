#include "Inventory.h"
#include <iostream>

void Inventory::AddItem(const std::string& item)
{
    items[item]++;
    std::cout << item << " 아이템이 인벤토리에 추가되었습니다.\n";
}

void Inventory::RemoveItem(const std::string& item)
{
    auto it = items.find(item);

    if (it == items.end())
    {
        std::cout << "해당 아이템이 없습니다.\n";
        return;
    }

    if (--it->second <= 0)
    {
        items.erase(it);
        std::cout << item << " 아이템이 인벤토리에서 제거되었습니다.\n";
    }
}

void Inventory::ShowInventory() const
{
    std::cout << "인벤토리가 열렸습니다\n";

    if (items.empty())
    {
        std::cout << "인벤토리가 비어있습니다.\n";
        return;
    }

    for (const auto& pair : items)
    {
        std::cout << "- " << pair.first
            << " x" << pair.second << "\n";
    }
}

const std::map<std::string, int>& Inventory::GetInventory() const
{
    return items;
}
