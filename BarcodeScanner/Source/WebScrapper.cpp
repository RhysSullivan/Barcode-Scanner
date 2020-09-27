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
	std::string BigOvenSearchPage = "https://www.bigoven.com/recipes/search/page/";
	std::string PageOutput = "HTMLSource/RecipePages/";
	uint32_t EndPage = 30;//39842

	for (uint32_t PageIndex = 1; PageIndex < EndPage; PageIndex++)
	{
		std::string PageAddress = BigOvenSearchPage + std::to_string(PageIndex);
		std::string OutPageFileName = PageOutput + std::to_string(PageIndex) + ".html";
		DownloadSite(OutPageFileName, PageAddress);		

		ARecipeParser RecipeParser;
		RecipeParser.ParseRecipeListHTMLPage(OutPageFileName);
	}
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
	//std::cout << "Downloaded: " << URL << '\n';
#endif
	return;
}