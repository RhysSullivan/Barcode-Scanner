#include "HTMLUtils.h"
#include <fstream>
// these two are so similar, consider collapsing contents into private method
bool HTMLUtils::ExtractTextFromFormatting(const std::string& Text, std::string& Output, const std::string& StartStr, const std::string& EndStr)
{
	if (Text.empty())
	{
		return false;
	}
	uint32_t SectionStart = static_cast<uint32_t>(Text.find(StartStr) + StartStr.size());
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
	return true;
}

bool HTMLUtils::ExtractTextFromFormatting(const std::string& Text, std::string& Output, const std::string& StartStr, const std::string& EndStr, uint32_t& Offset)
{
	if (Text.empty())
	{
		return false; // TODO: Throw error
	}
	uint32_t SectionStart = static_cast<uint32_t>(Text.find(StartStr, Offset));
	uint32_t SectionEnd = static_cast<uint32_t>(Text.find(EndStr, SectionStart));

	if ((SectionStart == std::string::npos || SectionEnd == std::string::npos))
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

void HTMLUtils::ExtractTextKeepFormatting(std::string& InSection, std::string& OutSection, const std::string& SectionStart, const std::string& SectionEnd)
{
	uint32_t SectionStartIndex = static_cast<uint32_t>(InSection.find(SectionStart));
	uint32_t SectionEndIndex = static_cast<uint32_t>(InSection.find(SectionEnd, SectionStartIndex));
	OutSection = InSection.substr(SectionStartIndex, SectionEndIndex - SectionStartIndex + SectionEnd.size());
}

void HTMLUtils::ExtractTextKeepFormatting(std::string& InSection, std::string& OutSection, const std::string& SectionStart, const std::string& SectionEnd, uint32_t& Offset)
{
	uint32_t SectionStartIndex = static_cast<uint32_t>(InSection.find(SectionStart, Offset)+SectionStart.size());
	uint32_t SectionEndIndex = static_cast<uint32_t>(InSection.find(SectionEnd, SectionStartIndex));
	OutSection = InSection.substr(SectionStartIndex, SectionEndIndex - SectionStartIndex);
	Offset = SectionEndIndex;
}

void HTMLUtils::ReadDownloadedFileIntoString(std::string& OutString, const std::string& FileName)
{
	std::ifstream fin(FileName);
	OutString = std::string((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
}