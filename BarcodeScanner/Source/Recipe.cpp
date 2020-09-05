#include "Recipe.h"
#include "Components/ComponentManager.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
void ARecipe::Serialize()
{
	std::ofstream OutFile;
	
	std::string OutFileName = "Recipes/";
	OutFileName += Name + ".txt";
	OutFile.open(OutFileName);

	if (!OutFile.is_open())
	{
		std::cout << "Error: Couldn't open file: " << OutFileName << '\n';
	}

	OutFile << *this;
}

void ARecipe::Deserialize(const std::string& FileName)
{
	std::ifstream RecipeFile(FileName);

	if (RecipeFile.is_open())
	{
		EParseState ParseState = EParseState::E_INVALID;
		std::string Line;
		std::vector<std::string> TEMP_Ingredients;
		while (std::getline(RecipeFile, Line))
		{
			if (Line.empty())
			{
				continue;
			}
			else if (Line == "#NAME#")
			{
				ParseState = EParseState::E_NAME;
			}
			else if (Line == "#INGREDIENTS#")
			{
				ParseState = EParseState::E_INGREDIENTS;
			}
			else if (Line == "#LINK#")
			{
				ParseState = EParseState::E_LINK;
			}
			else
			{
				switch (ParseState)
				{
				case EParseState::E_NAME:
					Name = Line;
					break;
				case EParseState::E_INGREDIENTS:
					TEMP_Ingredients.push_back(Line);
					break;
				case EParseState::E_LINK:
					LinkToRecipe = Line;
					break;
				case EParseState::E_TIME:
					break;
				case EParseState::E_INVALID:
					break;
				default:
					break;
				}
			}
		}
		AddIngredientsComponent(TEMP_Ingredients);
	}
}


std::ostream& operator<<(std::ostream& out, const ARecipe& Recipe)
{
	out << "#NAME#\n" << Recipe.Name << '\n';
	out << "#INGREDIENTS#\n";
	AComponentManager& ComponentManager = AComponentManager::GetInstance();
	RecipeIngredients* OutIng;

	if (ComponentManager.GetIngredients(Recipe.IngredientsComponent, OutIng))
	{
		for (const auto& Ingredient : *OutIng)
		{
			for (const auto& IngredientLetter : Ingredient)
			{
				out << IngredientLetter;
			}
			out << '\n';
		}
	}

	out << "#LINK#" << '\n';
	out << Recipe.LinkToRecipe;
	return out;
}

void ARecipe::PrintIngredients()
{
	AComponentManager& a = AComponentManager::GetInstance();


}