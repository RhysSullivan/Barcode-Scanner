#pragma once
#include "Item.h"
#include <string>
#include <vector>
class ABarcodeScanner
{
public:
	ABarcodeScanner();
	bool ScanBarcode(const std::string& ItemBarcode);
	void ConstructObjectFromScannedBarcode(const std::string& ItemBarcode);

private:
	std::vector<AItem> Items;
};

