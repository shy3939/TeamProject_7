#include <iostream>
#include "Inventory.h"

template<typename T>
void Inventory<T>::AddItem(const T& item)
{
    items.push_back(item);
    std::cout << item << " 아이템이 인벤토리에 추가되었습니다.\n";
}

template<typename T>
void Inventory<T>::RemoveLastItem()
{
    if (items.empty())
    {
        std::cout << "인벤토리가 비어있습니다.\n";
        return;
    }

    std::cout << items.back()
        << " 아이템이 인벤토리에서 제거되었습니다.\n";
    items.pop_back();
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

    for (const T& item : items)
    {
        std::cout << "- " << item << "\n";
    }
}
