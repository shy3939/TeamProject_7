#pragma once

#include <vector>
#include <string>

template<typename T>
class Inventory
{
private:
    std::vector<T> items;

public:
    void AddItem(const T& item);
    void RemoveLastItem();
    void ShowInventory() const;
};