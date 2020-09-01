#include <iostream>
#include <fstream>

#include "WebScrapper.h"
#include "HTMLUtils.h"
#include "BarcodeScanner.h"
#include "RecipeParser.h"

int main()
{
	AWebScrapper WebScrapper;
	//WebScrapper.StartScrape();	

	std::cout << "==============================================\n";
	std::string Barcode = "076808516135";

	ABarcodeScanner BarcodeScanner;
	while (true)
	{
		std::string UserInput;
		std::getline(std::cin, UserInput);
		if (UserInput.size() > 3)
		{
			system("cls");
			BarcodeScanner.ScanBarcode(UserInput);
		}
		
	}
	ARecipeParser RecipeParser;
	RecipeParser.ParseRecipeHTMLFile("HTMLSource/Recipes/tomato-puff-pastry-bites.html");
}