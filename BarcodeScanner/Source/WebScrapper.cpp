#include "WebScrapper.h"

#include <urlmon.h>
#include <iostream>	
#include <fstream>

#include "RecipeParser.h"
void AWebScrapper::StartScrape()
{

	char webAddress[256] = "https://www.bigoven.com/recipe/pumpkin-loaf-with-cream-cheese-icing/167340";
	char szFileName[80] = "HTMLSource/test.html";

	HRESULT hr = URLDownloadToFile(NULL, webAddress, szFileName, 0, NULL);
	if (hr == S_OK)
	{
		std::cout << "Downloaded: " << webAddress << '\n';
		// Open the file and print it to the console window
		// Since the file was just written, it should still be in cache somewhere.
		ARecipeParser RecipeParser;
		RecipeParser.ParseHTMLFile(szFileName);
	}
	else 
	{
		std::cout << "Operation failed with error code: " << hr << "\n";
	}
}
