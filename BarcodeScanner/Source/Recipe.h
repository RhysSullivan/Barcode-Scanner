#pragma once
#include "Components/ComponentManager.h"

#include <vector>
#include <string>
#include <iostream>

enum class EParseState
{
	E_NAME,
	E_INGREDIENTS,
	E_LINK,
	E_TIME,
	E_INVALID
};

class ARecipe
{
public:
	ARecipe(const std::string& InName, const std::vector<std::string>& Ingredients, const std::string& InLinkToRecipe)
	{
		AddIngredientsComponent(Ingredients);
		Name = InName;
		LinkToRecipe = InLinkToRecipe;
	}
	ARecipe(const std::string& FileName)
	{
		Deserialize(FileName);
	}
	~ARecipe()
	{
		AComponentManager& ComponentManager = AComponentManager::GetInstance();
	}
	void AddIngredientsComponent(const std::vector<std::string>& Ingredients)
	{
		AComponentManager& ComponentManager = AComponentManager::GetInstance();
		IngredientsComponent = ComponentManager.AddIngredients(Ingredients);
	}
	void Serialize();
	void Deserialize(const std::string& FileName);
	void PrintIngredients();
	
	friend std::ostream& operator<<(std::ostream& out, const ARecipe& Recipe);
private:
	std::string LinkToRecipe;
	std::string Name;
	int IngredientsComponent = -1;
};
