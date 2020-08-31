#include "WebScrapper.h"

#include <urlmon.h>
#include <iostream>	
#include <fstream>

#include "HTMLUtils.h"
#include "RecipeParser.h"


#define ONLINE 0

//https://www.bigoven.com/recipes/search/page/39802
void AWebScrapper::StartScrape()
{
	std::string WebAddress= "https://www.bigoven.com/recipe/pumpkin-loaf-with-cream-cheese-icing/167340";
	std::string OutFileName = "HTMLSource/test.html";
	DownloadSite(OutFileName, WebAddress);
	
	
	ARecipeParser RecipeParser;
	RecipeParser.ParseHTMLFile(OutFileName.c_str());
}

void AWebScrapper::DownloadSite(std::string& OutFileName, const std::string& URL)
{
#if ONLINE
	HRESULT hr = URLDownloadToFile(NULL, URL.c_str(), OutFileName.c_str(), 0, NULL);
	if (hr == S_OK)
	{
		std::cout << "Downloaded: " << URL << '\n';
		// Open the file and print it to the console window
		// Since the file was just written, it should still be in cache somewhere.
	}
	else
	{
		std::cout << "Operation failed with error code: " << hr << "\n";
	}
	return;
#else
	std::cout << "Downloaded: " << URL << '\n';
#endif
	return;
}