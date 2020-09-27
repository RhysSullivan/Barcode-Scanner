#pragma once
#include <string>

enum class EItemParseState
{
	E_BARCODE,
	E_ITEM_OFFICIAL_NAME,
	E_ITEM_COMMON_NAME,
	E_AMOUNT,
	E_INVALID
};

class AItem
{
public:	
	AItem(const std::string& InBarcode, const std::string& InItemCommonName, const std::string& InItemOfficialName);
	AItem(const std::string& FileToReadFrom);
	void Serialize();
	void Deserialize(const std::string& InSerializedFile);
	std::string& GetBarcode() { return Barcode; }
	void RemoveOneUnit() { --Amount; }
	void AddOneUnit() { ++Amount; }
private:
	std::string Barcode;
	std::string ItemCommonName;
	std::string ItemOfficialName;
	int Amount = 0;
};

