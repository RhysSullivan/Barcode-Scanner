#include "RecipeParser.h"
#include <fstream>
#include <iostream>
#include <string>

bool ExtractTextFromFormatting(const std::string& Text, std::string& Output, const std::string& StartStr, const std::string& EndStr, int& Offset)
{
	int SectionStart = Text.find(StartStr, Offset);
	int SectionEnd = Text.find(EndStr, SectionStart);

	if (SectionStart == std::string::npos || SectionEnd == std::string::npos)
	{
		return false;
	}
	if (Text[SectionStart + StartStr.size()] != '>' || Text[SectionEnd + EndStr.size()-1] != '>')
	{
		std::cout << Text[SectionStart + StartStr.size()-1];
		Offset = SectionEnd;
		return false;
	}
	std::string TextSection = Text.substr(SectionStart, SectionEnd - SectionStart);

	int OpenBrackets = 0;
	for (int i = 0; i < TextSection.size(); i++)
	{
		char CurrentChar = TextSection[i];
		if (CurrentChar == '<')
		{
			OpenBrackets++;
		}
		else if (CurrentChar == '>')
		{
			OpenBrackets--;
		}
		else if (OpenBrackets == 0)
		{
			Output += CurrentChar;
		}
	}
	Offset = SectionEnd;
	return true;
}

void ARecipeParser::ParseHTMLFile(char* FileName)
{
	std::ifstream fin(FileName);
	std::string IngredientsSectionStart = "<ul class=\"ingredients-list\">";
	std::string IngredientsSectionEnd = "</ul>";
	std::string str((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	

	std::string IngredientsSection;
	int IngOff = 0;


	ExtractTextFromFormatting(str, IngredientsSection, IngredientsSectionStart, IngredientsSectionEnd, IngOff)

	if ()
	{
		std::cout << IngredientsSection;
		std::string IngAmountStartStr = "<span class=\"amount\">";
		std::string IngAmountEndStr = "</span>";
		std::string IngNameStartStr = "<span class=\"name\">";
		std::string IngNameEndStr = "</span>";

		int Offset = 0;
		while (IngredientsSection.find(IngAmountStartStr, Offset) != std::string::npos)
		{
			std::string Amount;
			ExtractTextFromFormatting(IngredientsSection, Amount, IngAmountStartStr, IngAmountEndStr, Offset);

			std::string Name;
			ExtractTextFromFormatting(IngredientsSection, Name, IngNameStartStr, IngNameEndStr, Offset);
		
			std::cout << Amount << "    " << Name << "\n";
		}
	}
}
