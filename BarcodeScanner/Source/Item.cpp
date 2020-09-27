#include "Item.h"


#include <fstream>
#include <string>
AItem::AItem(const std::string& InBarcode, const std::string& InItemCommonName, const std::string& InItemOfficialName)
	: Barcode(InBarcode), ItemCommonName(InItemCommonName), ItemOfficialName(InItemOfficialName)
{
}

AItem::AItem(const std::string& FileToReadFrom)
{
	Deserialize(FileToReadFrom);
}

void AItem::Serialize()
{
	std::string OutFileName = "Items/" + Barcode + ".txt";
	std::ofstream SerializedValues(OutFileName);
	if (SerializedValues.is_open())
	{
		SerializedValues << "#BARCODE#\n" << Barcode << '\n';
		SerializedValues << "#ITEM_OFFICIAL_NAME#\n" << ItemOfficialName << '\n';
		SerializedValues << "#ITEM_COMMON_NAME#\n" << ItemCommonName << '\n';
		SerializedValues << "#AMOUNT#\n" << Amount << '\n';
	}
}

void AItem::Deserialize(const std::string& InSerializedFile)
{
	std::ifstream SerializedFileToRead(InSerializedFile);

	if (SerializedFileToRead.is_open())
	{
		EItemParseState ParseState = EItemParseState::E_INVALID;
		std::string Line;
		while (std::getline(SerializedFileToRead, Line))
		{
			if (Line.empty())
			{
				continue;
			}
			else if (Line == "#BARCODE#")
			{
				ParseState = EItemParseState::E_BARCODE;
			}
			else if (Line == "#ITEM_OFFICIAL_NAME#")
			{
				ParseState = EItemParseState::E_ITEM_OFFICIAL_NAME;
			}
			else if (Line == "#ITEM_COMMON_NAME#")
			{
				ParseState = EItemParseState::E_ITEM_COMMON_NAME;
			}
			else if (Line == "#AMOUNT#")
			{
				ParseState = EItemParseState::E_AMOUNT;
			}
			else
			{
				switch (ParseState)
				{
				case EItemParseState::E_BARCODE:
					Barcode = Line;
					break;
				case EItemParseState::E_ITEM_OFFICIAL_NAME:
					ItemOfficialName = Line;
					break;
				case EItemParseState::E_ITEM_COMMON_NAME:
					ItemCommonName = Line;
					break;
				case EItemParseState::E_AMOUNT:
					Amount = std::stoi(Line);
					break;
				case EItemParseState::E_INVALID:
					break;
				default:
					break;
				}
			}
		}
	}
}