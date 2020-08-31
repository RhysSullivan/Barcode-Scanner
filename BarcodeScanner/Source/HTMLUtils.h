#pragma once
#include <string>
class HTMLUtils
{
public:
	static bool ExtractTextFromFormatting(const std::string& Text, std::string& Output, const std::string& StartStr, const std::string& EndStr);
	static bool ExtractTextFromFormatting(const std::string& Text, std::string& Output, const std::string& StartStr, const std::string& EndStr, uint32_t& Offset);
	static void ExtractTextKeepFormatting(std::string& InSection, std::string& OutSection, const std::string& SectionStart, const std::string& SectionEnd);
};

