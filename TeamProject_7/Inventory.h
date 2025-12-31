#pragma once

#include <map>
#include <string>

class Inventory
{
private:
    std::map<std::string, int> items;

public:
    void AddItem(const std::string& item);
    void RemoveItem(const std::string& item);
    void ShowInventory() const;
    const std::map<std::string, int>& GetInventory() const;
};