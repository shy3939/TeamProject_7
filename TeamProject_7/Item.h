#pragma once
#include <iostream>
#include <string>

class Player;

class Item
{
public:

    Item();

    virtual ~Item();

    virtual bool Use(Player* player) = 0;

protected:

    std::string ItemName_ = "";
};

class HpPotion : public Item
{
public:

    HpPotion();
    bool Use(Player* player) override;

private:
    int HealAmount_ = 50;
};

class AtkPotion : public Item
{
public:
    AtkPotion();
    bool Use(Player* player) override;

private:

    int AtkAmount_ = 10;
};