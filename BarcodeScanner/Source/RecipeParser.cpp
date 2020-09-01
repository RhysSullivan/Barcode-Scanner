#include "RecipeParser.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <iomanip>

#include "HTMLUtils.h"
#include "WebScrapper.h"

void ARecipeParser::ParseRecipeListHTMLPage(const std::string& FileName)
{
	std::string DownloadedFileStr;
	HTMLUtils::ReadDownloadedFileIntoString(DownloadedFileStr, FileName);
	

	const std::string RecipeURLStart = "data-url=\"";
	const std::string RecipeURLEnd = "\">";

	uint32_t Offset = 0;
	uint32_t NumRecipesFound = 0;
	while (DownloadedFileStr.find(RecipeURLStart, Offset) != std::string::npos)
	{
		std::string OutRecipeURL;
		HTMLUtils::ExtractTextKeepFormatting(DownloadedFileStr, OutRecipeURL, RecipeURLStart, RecipeURLEnd, Offset);
		const std::string RecipeNameStart = "https://www.bigoven.com/recipe/";
		if (OutRecipeURL.find(RecipeNameStart) != std::string::npos)
		{
			uint32_t StartLoc = OutRecipeURL.find(RecipeNameStart) + RecipeNameStart.size();
			uint32_t EndLoc = OutRecipeURL.find('/', StartLoc);
			std::string RecipeName = OutRecipeURL.substr(StartLoc, EndLoc - StartLoc);

			std::string OutRecipeFileName = "HTMLSource/Recipes/";
			OutRecipeFileName += RecipeName + ".html";
			AWebScrapper WebScrapper;
			WebScrapper.DownloadSite(OutRecipeFileName, OutRecipeURL);

			ParseRecipeHTMLFile(OutRecipeFileName);
		}
	}
}

void ARecipeParser::ParseRecipeHTMLFile(const std::string& FileName)
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
	HTMLUtils::ExtractTextFromFormatting(str, NameSection, NameSectionStart, NameSectionEnd, NameOffset);
	std::cout << NameSection << '\n';
	
	/*
	* Servings
	*/
	std::string ServingsSection;
	const std::string ServingsSectionStart = "<div class=\"yield\">";
	const std::string ServingsSectionEnd = "</div>";
	uint32_t ServingsOffset = 0;
	HTMLUtils::ExtractTextFromFormatting(str, ServingsSection, ServingsSectionStart, ServingsSectionEnd, ServingsOffset);
	std::cout << ServingsSection << '\n';

	/*
	* Time
	*/
	std::string TimeSection;
	const std::string TimeSectionStart = "<div class=\"ready-in rc-opt\">";
	const std::string TimeSectionEnd = "</div>";
	uint32_t TimeOffset = 0;
	HTMLUtils::ExtractTextFromFormatting(str, TimeSection, TimeSectionStart, TimeSectionEnd, TimeOffset);
	std::cout << TimeSection << '\n';

	/*
	* Type & Amount
	*/
	std::string IngredientsSection;
	const std::string IngredientsSectionStart = "<ul class=\"ingredients-list\">";
	const std::string IngredientsSectionEnd = "</ul>";
	HTMLUtils::ExtractTextKeepFormatting(str, IngredientsSection, IngredientsSectionStart, IngredientsSectionEnd);



	const std::string IngAmountStartStr = "<span class=\"amount\">";
	const std::string IngAmountEndStr = "</span>";
	const std::string IngNameStartStr = "<span class=\"name\">";
	const std::string IngNameEndStr = "</span>";

	uint32_t Offset = 0;
	while (IngredientsSection.find(IngAmountStartStr, Offset) != std::string::npos)
	{
		std::string IngAmount;
		HTMLUtils::ExtractTextFromFormatting(IngredientsSection, IngAmount, IngAmountStartStr, IngAmountEndStr, Offset);

		std::string IngName;
		HTMLUtils::ExtractTextFromFormatting(IngredientsSection, IngName, IngNameStartStr, IngNameEndStr, Offset);

		if (!IngAmount.empty() && !IngName.empty())
		{
			std::cout << std::left << IngAmount  << std::setw(40) << std::right << IngName  << '\n';
		}
	}
	std::cout << "\n\n\n";
}
