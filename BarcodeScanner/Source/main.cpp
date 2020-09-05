#include <iostream>
#include <fstream>
#include <vector>


#include "WebScrapper.h"
#include "HTMLUtils.h"
#include "BarcodeScanner.h"
#include "RecipeParser.h"
#include "Components/ComponentManager.h"

AComponentManager* AComponentManager::instanceRef = 0;

int main()
{
	AWebScrapper WebScrapper;
	WebScrapper.StartScrape();	

	ARecipeParser RecipeParser;
	//RecipeParser.ParseRecipeDirectory("Recipes/");


	AComponentManager& ComponentManager = AComponentManager::GetInstance();

	return 0;

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
}