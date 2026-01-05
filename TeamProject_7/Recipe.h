#pragma once
#include<vector>
#include"ItemEnum.h"

struct RecipeInput
{
	ItemType type;
	int id;
	int count;
};

struct RecipeOutput
{
	ItemType type;
	int id;
	int count;
};

struct Recipe
{
	std::vector<RecipeInput> inputs;
	RecipeOutput output;
};