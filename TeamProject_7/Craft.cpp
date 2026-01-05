#include"Inventory.h"
#include"Recipe.h"

// 조합 가능 여부
bool CanCraft(const Inventory& inv, const Recipe& recipe)
{
    for (const auto& input : recipe.inputs)
    {
        if (inv.GetItemCount(input.type, input.id) < input.count) // 수정해야 됨
            return false;
    }
    return true;
}

// 조합하기
bool Craft(Inventory& inv, const Recipe& recipe)
{
    if (!CanCraft(inv, recipe))
        return false;

    // 1. 재료 제거
    for (const auto& input : recipe.inputs)
    {
        inv.RemoveItem(input.type, input.id, input.count);
    }

    // 2. 결과 추가
    inv.AddItem(recipe.output.type, recipe.output.id, recipe.output.count);

    return true;
}

// 지금 만들 수 있는 레시피만 찾기
std::vector<const Recipe*> GetCraftableRecipes(
    const Inventory& inv,
    const std::vector<Recipe>& recipes)
{
    std::vector<const Recipe*> result;

    for (const auto& recipe : recipes)
    {
        if (CanCraft(inv, recipe))
            result.push_back(&recipe);
    }
    return result;
}