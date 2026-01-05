#include "RecipeDatabase.h"


const std::vector<Recipe>& RecipeDatabase::GetAllRecipes()
{
	return RecipeDB;
}


static std::vector<Recipe> RecipeDB = {
	{
		{	// [철 주괴] 녹슨 철 조각(5) + 숫돌(1) -> 철 주괴(1)
			{ItemType::Ingredient, static_cast<int>(IngredID::RustyIronPiece), 5},
			{ItemType::Ingredient, static_cast<int>(IngredID::Whetstone), 1}
		},

		{
			ItemType::Ingredient,
			static_cast<int>(IngredID::IronBar),
			1
		}
	},
	{
		{
			// [HP 물약] 푸른 이파리(2) + 물(1) + 빈 유리병(1) -> HP 물약(1)
			{ItemType::Ingredient, static_cast<int>(IngredID::BlueLeaf), 2},
			{ItemType::Ingredient, static_cast<int>(IngredID::Water), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::EmptyGlassBottle), 1}
		},

		{
			ItemType::Potion, 
			static_cast<int>(PotionID::HPPotion),
			1
		}
	},
	{
		{
			// [MP 물약] 마법 가루(2) + 물(1) + 빈 유리병(1) -> MP 물약(1)
			{ItemType::Ingredient, static_cast<int>(IngredID::MagicDust), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::BlueLeaf), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::Water), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::EmptyGlassBottle), 1}
		},
		{
			ItemType::Potion, 
			static_cast<int>(PotionID::MPPotion), 
			1
		}
	},
	{
		{
			// [공격의 영약] 날카로운 이빨(3) + 몬스터 기름(1) + 빈 유리병(1) -> 공격 물약(1)
			{ItemType::Ingredient, static_cast<int>(IngredID::SharpFang), 3},
			{ItemType::Ingredient, static_cast<int>(IngredID::MonsterOil), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::EmptyGlassBottle), 1}
		},

		{
			ItemType::Potion,
			static_cast<int>(PotionID::ATKPotion),
			1
		}
	},
	{
		{
			// 녹슨 검(1) + 숫돌(1) -> 일반 검(1)
			{ItemType::Equipment, static_cast<int>(EquipID::RustySword), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::Whetstone), 1}
		},
		{
			ItemType::Equipment,
			static_cast<int>(EquipID::NormalSword),
			1
		}
	},
	{
		{
			// 낡은 활(1) + 동물 힘줄(2) + 실(1) -> 일반 활(1)
			{ItemType::Equipment, static_cast<int>(EquipID::WornBow), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::AnimalTendon), 2},
			{ItemType::Ingredient, static_cast<int>(IngredID::LinenThread), 1}
		},
		{
			ItemType::Equipment,
			static_cast<int>(EquipID::NormalBow),
			1
		}
	},
	{
		{
			// 마른 나뭇가지(3) + 마법 가루(1) + 탁한 수정 조각(1) -> 일반 지팡이(1)
			{ItemType::Ingredient, static_cast<int>(IngredID::DryTwig), 3},
			{ItemType::Ingredient, static_cast<int>(IngredID::MagicDust), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::MuddyCrystal), 1}
		},
		{
			ItemType::Equipment,
			static_cast<int>(EquipID::NormalStaff),
			1
		}
	},
	{
		{
			// 녹슨 흉갑(1) + 철 주괴(2) + 질긴 가죽(2) -> 일반 흉갑(1)
			{ItemType::Equipment, static_cast<int>(EquipID::RustyArmor), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::IronBar), 2},
			{ItemType::Ingredient, static_cast<int>(IngredID::ToughLeather), 2}
		},
		{
			ItemType::Equipment,
			static_cast<int>(EquipID::NormalArmor),
			1
		}
	},
	{
		{
			// 끈적이는 액체(3) + 마른 나뭇가지(1) -> 몬스터 기름(1)
			{ItemType::Ingredient, static_cast<int>(IngredID::SlimyFluid), 3},
			{ItemType::Ingredient, static_cast<int>(IngredID::DryTwig), 1}
		},
		{
			ItemType::Ingredient,
			static_cast<int>(IngredID::MonsterOil),
			1
		}
	},
	{
		{
			// 거친 천 조각(2) + 말린 약초 줄기(1) -> 실(2)
			{ItemType::Ingredient, static_cast<int>(IngredID::RoughFabric), 2},
			{ItemType::Ingredient, static_cast<int>(IngredID::DryHerbStem), 1}
		},
		{
			ItemType::Ingredient,
			static_cast<int>(IngredID::LinenThread),
			2
		}
	},
	{
		{
			// 녹슨 단검(1) + 숫돌(1) + 부싯돌(1) -> 날카로운 단검(1)
			{ItemType::Equipment, static_cast<int>(EquipID::RustyDagger), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::Whetstone), 1},
			{ItemType::Ingredient, static_cast<int>(IngredID::Flint), 1}
		},
		{
			ItemType::Equipment,
			static_cast<int>(EquipID::SharpDagger),
			1
		}
	}
};