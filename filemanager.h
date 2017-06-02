#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Windows.h"

class FileManager
{
public:
	FileManager();
	~FileManager();

	static bool copyFile(std::string baseLocation, std::string desination, std::string fileName);
	static std::wstring strToWstring(std::string str);

	static bool createDirectory(std::string path);
	static bool deleteDirectory(std::string path);

	static bool createFile(std::string path, std::string text);
	static bool deleteFile(std::string path);

	static std::vector<std::string> FileManager::getListFromFile(std::string path);
	static bool canOpen(std::string path);

private:
	
};

#endif // FILEMANAGER_H
