#include <iostream>
#include <map>
#include "Inventory.h"

template<typename T>
void Inventory<T>::AddItem(const T& item)
{
    items[item]++;
    std::cout << item << " 아이템이 인벤토리에 추가되었습니다.\n";
}

template<typename T>
void Inventory<T>::RemoveItem(const T& item)
{
    auto it = items.find(item);

    if (it == items.end())
    {
        std::cout << "해당 아이템이 없습니다.\n";
        return;
    }

    it->second--;

    if (it->second <= 0)
    {
        items.erase(it);
        std::cout << item << " 아이템이 인벤토리에서 제거되었습니다.\n";
    }
}

template<typename T>
void Inventory<T>::ShowInventory() const
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

template<typename T>
const std::map<T, int>& Inventory<T>::GetInventory() const
{
    return items;
}