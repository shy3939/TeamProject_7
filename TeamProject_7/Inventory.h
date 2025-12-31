#pragma once

#include <map>
#include <string>

template<typename T>
class Inventory
{
private:
    std::map<T, int> items;

public:
    void AddItem(const T& item);
    void RemoveItem(const T& item);
    void ShowInventory() const;
    const std::map<T, int>& GetInventory() const;
};