#pragma once
#include<vector>
#include"Recipe.h"

class RecipeDatabase
{
public:
	static const std::vector<Recipe>& GetAllRecipes();
};