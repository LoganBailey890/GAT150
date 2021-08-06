#include "FileSystem.h"
#include<filesystem>

namespace nc
{
	void setFilePath(const std::string& pathway)
	{
		std::filesystem::current_path(pathway);

	}
	std::string GetFilePath()
	{
		return std::filesystem::current_path().string();
	}
}