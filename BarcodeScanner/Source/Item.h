#pragma once
#include <string>
class AItem
{
public:
	AItem(const std::string InBarcode, const std::string InItemCommonName, const std::string InItemOfficialName);
	AItem(const std::string FileToReadFrom);
	void Serialize();
	void Deserialize(const std::string& InSerializedFile);
private:
	std::string Barcode;
	std::string ItemCommonName;
	std::string ItemOfficialName;
};

