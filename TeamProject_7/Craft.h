#pragma once
#include <vector>
#include "Recipe.h"

class Inventory;

// 조합 가능 여부 확인
bool CanCraft(const Inventory& inv, const Recipe& recipe);

// 조합 실행 (재료 제거 + 결과물 추가)
bool Craft(Inventory& inv, const Recipe& recipe);

// 현재 만들 수 있는 레시피 목록 반환
std::vector<const Recipe*> GetCraftableRecipes(
    const Inventory& inv,
    const std::vector<Recipe>& recipes);