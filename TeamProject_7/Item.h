#pragma once
#include <iostream>
#include <string>
#include"ItemDatabase.h"

class Player;

class Item
{
public:
    virtual ~Item() = default;
    virtual bool Use(Player* player) = 0;
    virtual ItemType GetType() const = 0;

protected:
    Item(const ItemDatabase& db) : db_(db) {}
    const ItemDatabase& db_;
};