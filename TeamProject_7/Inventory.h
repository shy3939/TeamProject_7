#pragma once

#include <map>
#include <string>

class Item;
class Player;

class Inventory
{
public:
    bool IsEmpty() const;
    bool IsAvailable(const std::string& key) const;
    int GetItemCount(const std::string& key) const;
    void Use(const std::string& ItemName, Player* player);

    void AddItem(const std::string& key);
    void RemoveItem(const std::string& key);
    void ShowInventory() const;
    const std::map<std::string, int>& GetInventory() const;

    Inventory();
    ~Inventory();

private:
    std::map<std::string, int> items;       // 키 값의 이름에 해당하는 아이템의 재고 관리 (포션 5개)
    std::map<std::string, Item*> itemData;  // 아이템의 주소 값 
};
﻿