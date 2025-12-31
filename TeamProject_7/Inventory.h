#pragma once

#include <map>
#include <string>

class Inventory
{
public:
    void AddItem(const std::string& key);
    void RemoveItem(const std::string& key);
    void ShowInventory() const;
    const std::map<std::string, int>& GetInventory() const;

private:
    std::map<std::string, int> items;
};