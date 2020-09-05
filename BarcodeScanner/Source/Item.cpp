#include "Item.h"


#include <fstream>

AItem::AItem(const std::string InBarcode, const std::string InItemCommonName, const std::string InItemOfficialName)
	: Barcode(InBarcode), ItemCommonName(InItemCommonName), ItemOfficialName(InItemOfficialName)
{
}

AItem::AItem(const std::string FileToReadFrom)
{
	Deserialize(FileToReadFrom);
}

void AItem::Serialize()
{
	std::string OutFileName = "Items/" + Barcode + ".txt";
	std::ofstream SerializedValues(OutFileName);
	if (SerializedValues.is_open())
	{
		SerializedValues << "#BARCODE\n" << Barcode << '\n';
		SerializedValues << "#ITEM_OFFICIAL_NAME\n" << ItemOfficialName << '\n';
		SerializedValues << "#ITEM_COMMON_NAME\n" << ItemCommonName << '\n';
	}
}

void AItem::Deserialize(const std::string& InSerializedFile)
{
	std::ifstream SerializedFileToRead(InSerializedFile);
}