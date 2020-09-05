#pragma once
#include <string>
class ARecipeParser
{
public:
	void ParseRecipeListHTMLPage(const std::string& FileName);
	void ParseRecipeHTMLFile(const std::string& FileName, const std::string& LinkToRecipe);
	void ParseRecipeDirectory(const std::string& Directory);
};

