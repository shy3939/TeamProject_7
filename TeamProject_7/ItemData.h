#pragma once
#include <string>

struct ItemBaseData
{
	std::string Name;
	int Price;
};

struct EquipData : ItemBaseData
{
	EquipData(
		const std::string& name_,
		int price_,
		int str_,
		int agi_,
		int vit_,
		int int_,
		int luk_)
		: ItemBaseData{name_, price_},
		BonusSTR(str_),
		BonusAGI(agi_),
		BonusVIT(vit_),
		BonusINT(int_),
		BonusLUK(luk_)
	{}
	int BonusSTR;
	int	BonusAGI;
	int	BonusVIT;
	int	BonusINT;
	int	BonusLUK;
};

struct PotionData : ItemBaseData
{
	PotionData(
		const std::string& name_,
		int price_,
		int hp_,
		int mp_)
		: ItemBaseData{name_, price_},
		PlusHP(hp_),
		PlusMP(mp_)
	{}
	int PlusHP;
	int PlusMP;
};

struct IngredData : ItemBaseData
{
	IngredData(
		const std::string& name_,
		int price_)
		:ItemBaseData{ name_, price_ }
	{}
};