#pragma once
#include <iostream>
#include <string>

class Item
{
public:

	Item(std::string ItemName, int hp, int maxhp, int count);
	Item(std::string ItemName, int atk, int count);
	virtual ~Item();

	virtual void Use() = 0;

	int GetHp() const;

	int GetMaxHp() const;

	int GetAtk() const;

	int GetCount() const;

	void SetHp(int Hp);

	void SetMaxHp(int MaxHp);

	void SetAtk(int Atk);

	void SetCount(int Count);

protected:

	std::string ItemName_ = "";
	int hp_ = 0;
	int maxhp_ = 0;
	int atk_ = 0;
	int count_ = 0;
};

class HpPotion : public Item
{
public:

	HpPotion(int Hp, int MaxHp, int Count);
	void Use() override;

private:
	int HealAmount_ = 50;
};

class AtkPotion : public Item
{
public:

	AtkPotion(int Atk, int Count);
	void Use() override;

private:

	int AtkAmount_ = 10;
};