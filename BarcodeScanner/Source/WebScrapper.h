#pragma once
#include <string>
class AWebScrapper
{
public:
	void StartScrape();
	void DownloadSite(std::string& OutFileName, const std::string& URL);
};

