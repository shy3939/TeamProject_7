#include <iostream>
#include <string>
#include "Item.h"


Item::Item(std::string ItemName, int hp, int maxhp, int count) : ItemName_(ItemName), hp_(hp), maxhp_(maxhp), count_(count) {}
Item::Item(std::string ItemName, int atk, int count) : ItemName_(ItemName), atk_(atk), count_(count) {}
Item::~Item() {}

int Item::GetHp() const { return hp_; }

int Item::GetMaxHp() const { return maxhp_; }

int Item::GetAtk() const { return atk_; }

int Item::GetCount() const { return count_; }

void Item::SetHp(int Hp) { hp_ = Hp; }

void Item::SetMaxHp(int MaxHp) { maxhp_ = MaxHp; }

void Item::SetAtk(int Atk) { atk_ = Atk; }

void Item::SetCount(int Count) { count_ = Count; }




HpPotion::HpPotion(int Hp, int MaxHp, int Count) : Item("HP 포션", Hp, MaxHp, Count) {}

void HpPotion::Use()
{
	if (hp_ < maxhp_)
	{
		if (count_ > 0)
		{
			std::cout << ItemName_ << " 사용" << HealAmount_ << "의 체력을 회복했습니다." << std::endl;
			hp_ += HealAmount_;

			if (hp_ > maxhp_)
			{
				hp_ = maxhp_;
			}

			std::cout << "현재 체력 : " << hp_ << std::endl;
			std::cout << "남은 " << ItemName_ << " 갯수 : " << --count_ << std::endl;
		}
		else
		{
			std::cout << "아이템이 부족합니다." << std::endl;
		}
	}
	else
	{
		std::cout << "이미 체력이 가득 차 있어 포션을 사용할 수 없습니다." << std::endl;
	}
}

AtkPotion::AtkPotion(int Atk, int Count) : Item("공격력 포션", Atk, Count) {}

void AtkPotion::Use()
{
	if (count_ > 0)
	{
		std::cout << ItemName_ << " 사용" << AtkAmount_ << "의 공격력이 증가했습니다." << std::endl;
		atk_ += AtkAmount_;
		std::cout << "현재 공격력 : " << atk_ << std::endl;
		std::cout << "남은 " << ItemName_ << " 갯수 : " << --count_ << std::endl;
	}
	else
	{
		std::cout << "아이템이 부족합니다." << std::endl;
	}
}

