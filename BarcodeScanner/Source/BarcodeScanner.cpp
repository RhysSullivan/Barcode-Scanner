#include <iostream>
#include <fstream>

#include "BarcodeScanner.h"
#include "WebScrapper.h"
#include "HTMLUtils.h"
#include "Item.h"
bool ABarcodeScanner::ScanBarcode(const std::string& ItemBarcode)
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
	/*
		#Barcode#
		01235137
		#Item Official Name#
		Barilla Protein Plus Angel Hair Pasta 14.5 Ounce - 2 Pack
		#Item Common Name#
		Pasta
		#Average Expiration date#
		5 days
		#Quantity#
		2
	*/
	AItem ScannedBarcode(ItemBarcode, ItemCommonName, ItemOfficialName);
	ScannedBarcode.Serialize();
	return false;
}
