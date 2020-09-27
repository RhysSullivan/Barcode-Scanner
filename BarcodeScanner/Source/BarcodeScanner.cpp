#include <iostream>
#include <fstream>
#include <filesystem>

#include "BarcodeScanner.h"
#include "WebScrapper.h"
#include "HTMLUtils.h"
#include "Item.h"

ABarcodeScanner::ABarcodeScanner()
{
	for (const auto& entry : std::filesystem::directory_iterator("Items/"))
	{
		std::string FileName = entry.path().generic_string();
		Items.push_back(AItem(FileName));
	}
}

bool ABarcodeScanner::ScanBarcode(const std::string& ItemBarcode)
{
	bool bFoundMatchingBarcodeInItems = false;
	for (auto& a : Items)
	{
		if (a.GetBarcode() == ItemBarcode)
		{
			bFoundMatchingBarcodeInItems = true;
			a.AddOneUnit();
			a.Serialize();
			std::cout << "Duplicate Entered\n";
		}
	}
	if (!bFoundMatchingBarcodeInItems)
	{
		ConstructObjectFromScannedBarcode(ItemBarcode);
	}
	return false;
}


/*
This should only ever be called when a Barcode is scanned for the first time.
*/
void ABarcodeScanner::ConstructObjectFromScannedBarcode(const std::string& ItemBarcode)
{
	std::string UPCSiteURL = "https://www.upcdatabase.com/item/";
	std::string OutFile = "HTMLSource/UPCSource/";
	UPCSiteURL += ItemBarcode;
	OutFile += ItemBarcode;
	OutFile += ".html";


	AWebScrapper WebScrapper;
	WebScrapper.DownloadSite(OutFile, UPCSiteURL);

	std::ifstream fin(OutFile);
	std::string str((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

	if (str.find("Item Not Found") != std::string::npos)
	{
		return;
	}


	/*
	* Official Name
	*/
	std::string ItemOfficialName;
	const std::string OfficialNameStart = "tr><td>Description</td><td></td><td>";
	const std::string OfficialNameEnd = "</td></tr>";
	HTMLUtils::ExtractTextFromFormatting(str, ItemOfficialName, OfficialNameStart, OfficialNameEnd);

	/*
	* Weight
	*/
	std::string ItemWeight;
	const std::string WeightStart = "<tr><td>Size/Weight</td><td></td><td>";
	const std::string WeightEnd = "</td></tr>";
	HTMLUtils::ExtractTextFromFormatting(str, ItemWeight, WeightStart, WeightEnd);

	/*
	* Common Name
	*/
	std::string ItemCommonName;
	std::string CommonNameLine;
	std::ifstream CommonNameFile("EXAMPLE/ALLFOOD.txt");
	while (std::getline(CommonNameFile, CommonNameLine))
	{
		if (ItemOfficialName.find(CommonNameLine) != std::string::npos)
		{
			ItemCommonName = CommonNameLine;
		}
	}
	AItem NewItem = AItem(ItemBarcode, ItemCommonName, ItemOfficialName);
	NewItem.AddOneUnit();
	Items.push_back(NewItem);
	NewItem.Serialize();
}