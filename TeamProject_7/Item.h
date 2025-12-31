#pragma once
#include <iostream>
#include <string>

class Player;

class Item
{
public:

	Item(std::string ItemName, int count);
	
	virtual ~Item();

	virtual void Use(Player& player) = 0;

protected:

	std::string ItemName_ = "";
	int count_ = 0;
};

class HpPotion : public Item
{
public:

	HpPotion(std::string ItemName, int Count);
	void Use(Player& player) override;

private:
	int HealAmount_ = 50;
};

class AtkPotion : public Item
{
public:

	AtkPotion(std::string ItemName, int Count);
	void Use(Player& player) override;

private:

	int AtkAmount_ = 10;
};