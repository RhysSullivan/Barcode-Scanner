#pragma once
#include "Components/ComponentManager.h"

#include <vector>
#include <string>

class ARecipe
{
public:
	ARecipe(const std::string InName, const std::vector<std::string>& Ingredients)
	{
		AComponentManager& ComponentManager = AComponentManager::GetInstance();
		IngredientsComponent = ComponentManager.AddIngredients(Ingredients);
		Name = InName;
	}
	~ARecipe()
	{
		AComponentManager& ComponentManager = AComponentManager::GetInstance();
	}
	void Serialize();
	void PrintIngredients();

private:
	std::string Name;
	int IngredientsComponent = -1;
};

