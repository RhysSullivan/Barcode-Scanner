#pragma once
#include <vector>
#include <array>
#include <string>

#define MAX_CHARS_PER_INGREDIENT 30
#define MAX_INGREDIENTS_PER_RECIPE 20
typedef std::array<std::array<char, MAX_CHARS_PER_INGREDIENT>, MAX_INGREDIENTS_PER_RECIPE> RecipeIngredients;

class AComponentManager
{
private:
	static AComponentManager* instanceRef;
	AComponentManager()
	{
		instanceRef = nullptr;
	}
public:
	static AComponentManager& GetInstance()
	{
		if (!instanceRef)
		{
			instanceRef = new AComponentManager;
		}
		return *instanceRef;
	}
	int AddIngredients(const std::vector<std::string>& InIngredients)
	{
		if (IngredientOffset >= Ingredients.size())
		{
			Ingredients.push_back(RecipeIngredients());
		}
		for (int IngredientAddIndex = 0; IngredientAddIndex < InIngredients.size(); IngredientAddIndex++)
		{
			for (int CharIndex = 0; CharIndex < InIngredients[IngredientAddIndex].size(); CharIndex++)
			{
				if (CharIndex < MAX_CHARS_PER_INGREDIENT && IngredientAddIndex < MAX_INGREDIENTS_PER_RECIPE)
				{
					Ingredients[IngredientOffset][IngredientAddIndex][CharIndex] = InIngredients[IngredientAddIndex][CharIndex];
				}
			}
		}
		return IngredientOffset++;
	}
	bool GetIngredients(int Offset, RecipeIngredients*& OutIngredients)
	{
		if (Offset >= Ingredients.size())
			return false;
		OutIngredients = &Ingredients[Offset];
		return true;
	}
private:
	int IngredientOffset = 0;
	/*
	This lays out the memory sequentially for a faster read speed. (Maybe later try hashing?)
	
	The layout should be like:
		[RecipeIngredientsList]
			[Ingredient]
				[LettersInIngredient]
		[RecipeIngredientsList]
					[Ingredient]
						[LettersInIngredient]
	
	*/
	std::vector<RecipeIngredients> Ingredients;
};
