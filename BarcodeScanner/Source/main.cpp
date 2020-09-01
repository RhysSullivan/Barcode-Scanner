#include <iostream>
#include <fstream>

#include "WebScrapper.h"
#include "HTMLUtils.h"
#include "BarcodeScanner.h"
int main()
{
	AWebScrapper WebScrapper;
	WebScrapper.StartScrape();	

	std::cout << "==============================================\n";
	std::string Barcode = "076808516135";

	ABarcodeScanner BarcodeScanner;
	//BarcodeScanner.ScanBarcode(Barcode);
}