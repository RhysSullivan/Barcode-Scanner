#include "RecipeParser.h"
#include <fstream>
#include <iostream>
#include <string>
void ARecipeParser::ParseHTMLFile(char* FileName)
{
	std::ifstream fin(FileName);
	
	std::string FileLine;
	std::string IngredientsSectionStart = "<ul class=\"ingredients - list\">";
	
	while (fin.getline(FileLine, 2048))
	{
		auto IngredientsStringLocation = FileLine.find(IngredientsSectionStart);
	}
}
