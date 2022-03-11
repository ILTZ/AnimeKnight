#include "Paths.h"
#include <filesystem>


std::string getCurrentAssetsDirectory()
{
	//K:\PixelSheat\Test

	std::filesystem::path p = std::filesystem::current_path().make_preferred();
	p += "\\Resources\\";
	std::string path = p.string();

	return path;
}

