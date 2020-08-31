#include "RecipeParser.h"
#include <fstream>
#include <iostream>
#include <cassert>

#include <iomanip>
bool ExtractTextFromFormatting(const std::string& Text, std::string& Output, const std::string& StartStr, const std::string& EndStr, uint32_t& Offset)
{
	uint32_t SectionStart = static_cast<uint32_t>(Text.find(StartStr, Offset));
	uint32_t SectionEnd = static_cast<uint32_t>(Text.find(EndStr, SectionStart));

	if (SectionStart == std::string::npos || SectionEnd == std::string::npos)
	{
		return false;
	}

	std::string TextSection = Text.substr(SectionStart, SectionEnd - SectionStart);

	uint32_t OpenBrackets = 0;
	uint32_t NumberOfContinuousSpaces = 0;
	bool bStartWritingCharacters = false;
	uint32_t SequentialSpaces = 0;
	for (uint32_t i = 0; i < static_cast<uint32_t>(TextSection.size()); i++)
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
			if ((CurrentChar > 31 && CurrentChar < 125))
			{
				if (CurrentChar == ' ')
				{
					++SequentialSpaces;
				}
				else
				{
					SequentialSpaces = 0;
					bStartWritingCharacters = true;
				}

				if (SequentialSpaces < 2 && bStartWritingCharacters)
				{
					Output += CurrentChar;
				}
			}
		}
	}
	Offset = SectionEnd;

	return true;
}

void ARecipeParser::ExtractTextKeepFormatting(std::string& InSection, std::string& OutSection, const std::string& SectionStart, const std::string& SectionEnd)
{
	uint32_t SectionStartIndex = static_cast<uint32_t>(InSection.find(SectionStart));
	uint32_t SectionEndIndex = static_cast<uint32_t>(InSection.find(SectionEnd, SectionStartIndex));
	OutSection = InSection.substr(SectionStartIndex, SectionEndIndex- SectionStartIndex + SectionEnd.size());
}

void ARecipeParser::ParseHTMLFile(char* FileName)
{
	std::ifstream fin(FileName);
	
	std::string str((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	/*
	* Name
	*/
	std::string NameSection;
	const std::string NameSectionStart = "<h1>";
	const std::string NameSectionEnd = "</h1>";
	uint32_t NameOffset = 0;
	ExtractTextFromFormatting(str, NameSection, NameSectionStart, NameSectionEnd, NameOffset);
	std::cout << NameSection << '\n';
	
	/*
	* Servings
	*/
	std::string ServingsSection;
	const std::string ServingsSectionStart = "<div class=\"yield\">";
	const std::string ServingsSectionEnd = "</div>";
	uint32_t ServingsOffset = 0;
	ExtractTextFromFormatting(str, ServingsSection, ServingsSectionStart, ServingsSectionEnd, ServingsOffset);
	std::cout << ServingsSection << '\n';

	/*
	* Time
	*/
	std::string TimeSection;
	const std::string TimeSectionStart = "<div class=\"ready-in rc-opt\">";
	const std::string TimeSectionEnd = "</div>";
	uint32_t TimeOffset = 0;
	ExtractTextFromFormatting(str, TimeSection, TimeSectionStart, TimeSectionEnd, TimeOffset);
	std::cout << TimeSection << '\n';

	/*
	* Type & Amount
	*/
	std::string IngredientsSection;
	const std::string IngredientsSectionStart = "<ul class=\"ingredients-list\">";
	const std::string IngredientsSectionEnd = "</ul>";
	ExtractTextKeepFormatting(str, IngredientsSection, IngredientsSectionStart, IngredientsSectionEnd);



	const std::string IngAmountStartStr = "<span class=\"amount\">";
	const std::string IngAmountEndStr = "</span>";
	const std::string IngNameStartStr = "<span class=\"name\">";
	const std::string IngNameEndStr = "</span>";

	uint32_t Offset = 0;
	while (IngredientsSection.find(IngAmountStartStr, Offset) != std::string::npos)
	{
		std::string IngAmount;
		ExtractTextFromFormatting(IngredientsSection, IngAmount, IngAmountStartStr, IngAmountEndStr, Offset);

		std::string IngName;
		ExtractTextFromFormatting(IngredientsSection, IngName, IngNameStartStr, IngNameEndStr, Offset);

		if (!IngAmount.empty() && !IngName.empty())
		{
			std::cout << std::left << IngAmount  << std::setw(40) << std::right << IngName  << '\n';
		}
	}
}
