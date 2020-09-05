#include "Recipe.h"
#include "Components/ComponentManager.h"

#include <vector>
#include <string>
#include <fstream>

void ARecipe::Serialize()
{
	std::ofstream OutFile;
	
	std::string OutFileName = "Recipes/";
	OutFileName += Name + ".txt";
	OutFile.open(OutFileName);


	AComponentManager& ComponentManager = AComponentManager::GetInstance();
	RecipeIngredients* OutIng;
	
	if (ComponentManager.GetIngredients(IngredientsComponent, OutIng))
	{
		for (const auto& Ingredient : *OutIng)
		{
			for (const auto& IngredientLetter : Ingredient)
			{
				OutFile << IngredientLetter;
			}
			OutFile << '\n';
		}
	}
}


void ARecipe::PrintIngredients()
{
	AComponentManager& a = AComponentManager::GetInstance();


}