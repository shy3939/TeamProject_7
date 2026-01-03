#pragma once
#include <vector>
#include "ItemEnum.h"
#include "ItemData.h"

class ItemDatabase
{
public:
	const std::vector<EquipData>& GetEquipItems(EquipID eid) const;
	const std::vector<PotionData>& GetPotionItems(PotionID pid) const;
	const std::vector<IngredData>& GetIngredItems(IngredID gid) const;
};