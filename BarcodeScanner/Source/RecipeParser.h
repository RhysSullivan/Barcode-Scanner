#pragma once
#include <string>
class ARecipeParser
{
public:
	void ExtractTextKeepFormatting(std::string& InSection, std::string& OutSection, const std::string& SectionStart, const std::string& SectionEnd);
	void ParseHTMLFile(char* FileName);
};

