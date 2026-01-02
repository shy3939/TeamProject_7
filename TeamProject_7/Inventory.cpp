#include "Inventory.h"
#include <iostream>


Inventory::Inventory()
{
	itemData_["HpPotion"] = new HpPotion();
	itemData_["ATKPotion"] = new AtkPotion();
}

Inventory::~Inventory()
{
	for (auto& pair : itemData_)
	{
		delete pair.second;
	}
	itemData_.clear();
}

bool Inventory::IsEmpty() const                               // 맵이 아예 통째로 비여있는지 모든 아이템이 없으면 true 아이템이 하나라도 있으면 false
{
	return items_.empty();
}

bool Inventory::IsAvailable(const std::string& key) const     // key가 들어왔을때 맵에서 key를 찾아서 재고가 0개인지 사용가능한지를 반환.
{
	auto it = items_.find(key);
	if (it == items_.end())
		return false;

	return it->second > 0;
}

int Inventory::GetItemCount(const std::string& key) const     //key를 받아와서 key가 해당하는 재고의 갯수를 반환
{
	auto it = items_.find(key);
	if (it == items_.end())
		return 0;

	return it->second;
}

void Inventory::Use(const std::string& key, Player* player)
{
	if (items_[key] <= 0) return;

	itemData_[key]->Use(player);
	items_[key]--;
}

void Inventory::AddItem(const std::string& key)
{
	items_[key]++;
	std::cout << key << " 아이템이 인벤토리에 추가되었습니다." << std::endl;
}

void Inventory::RemoveItem(const std::string& key)
{
	auto it = items_.find(key);

	if (it == items_.end())
	{
		std::cout << "해당 아이템이 없습니다." << std::endl;
		return;
	}

	if (--it->second <= 0)
	{
		items_.erase(it);
		std::cout << key << " 아이템이 인벤토리에서 제거되었습니다." << std::endl;

	}
}

void Inventory::ShowInventory() const
{
	std::cout << "인벤토리가 열렸습니다." << std::endl;


	if (items_.empty())
	{
		std::cout << "인벤토리가 비어있습니다." << std::endl;
		return;
	}

	for (const auto& pair : items_)
	{
		std::cout << "- " << pair.first
			<< " x" << pair.second << std::endl;
	}
}

const std::map<std::string, int>& Inventory::GetInventory() const
{
	return items_;
}

