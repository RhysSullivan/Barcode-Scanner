#include <iostream>
#include <fstream>

#include "BarcodeScanner.h"
#include "WebScrapper.h"
#include "HTMLUtils.h"
bool ABarcodeScanner::ScanBarcode(const std::string& Barcode)
{
	std::string UPCSiteURL = "https://www.upcdatabase.com/item/";
	std::string OutFile = "HTMLSource/UPCSource/";
	UPCSiteURL += Barcode;
	OutFile += Barcode;
	OutFile += ".html";


	AWebScrapper WebScrapper;
	WebScrapper.DownloadSite(OutFile, UPCSiteURL);

	std::ifstream fin(OutFile);
	std::string str((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

	std::string OutName;
	const std::string NameStart = "tr><td>Description</td><td></td><td>";
	const std::string NameEnd = "</td></tr>";
	HTMLUtils::ExtractTextFromFormatting(str, OutName, NameStart, NameEnd);


	std::string OutWeight;
	const std::string WeightStart = "<tr><td>Size/Weight</td><td></td><td>";
	const std::string WeightEnd = "</td></tr>";
	HTMLUtils::ExtractTextFromFormatting(str, OutWeight, WeightStart, WeightEnd);

	std::cout << OutName << "\t\t\t\t\t" << OutWeight;
    return false;
}
