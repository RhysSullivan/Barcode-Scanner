#include "WebScrapper.h"
#include "HTMLUtils.h"
#include "BarcodeScanner.h"
#include "RecipeParser.h"
#include "Components/ComponentManager.h"
AComponentManager* AComponentManager::instanceRef = 0;
#include <iostream>
#include <fstream>
#include <vector>

#include "Networking/Server/Server.h"
#include "Networking/Client/Client.h"

#define SERVER

int main() 
{
#ifdef SERVER
	Server();
#else
	Client();
#endif
}

/*


AComponentManager* AComponentManager::instanceRef = 0;

int main()
{
	AWebScrapper WebScrapper;
	//WebScrapper.StartScrape();	

	ARecipeParser RecipeParser;
	RecipeParser.ParseRecipeDirectory("Recipes/");
	

	AComponentManager& a = AComponentManager::GetInstance();
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
}*/