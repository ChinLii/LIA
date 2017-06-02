#include "filemanager.h"
#include <qdebug.h>
#include <fstream>

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

bool FileManager::deleteFile(std::string path)
{
	return DeleteFile( strToWstring(path).c_str() );
}

bool FileManager::copyFile(std::string baseLocation, std::string desination, std::string fileName)
{
	std::string to = desination + "//" + fileName;

	return CopyFile( strToWstring(baseLocation).c_str(), strToWstring(to).c_str(), 0);
}

bool FileManager::createFile(std::string path, std::string text)
{
	qDebug() << "FileManger - create file";
	std::ofstream outFile;
	outFile.open(path);

	if (!outFile.is_open())
		return false;

	outFile << text;
	outFile.close();

	return true;
}

bool FileManager::createDirectory(std::string path)
{
	return CreateDirectory( strToWstring(path).c_str(), NULL);
}

bool FileManager::deleteDirectory(std::string path)
{
	return RemoveDirectory( strToWstring(path).c_str() );
}

std::wstring FileManager::strToWstring(std::string s)
{
	return std::wstring(s.begin(), s.end());
}

std::vector<std::string> FileManager::getListFromFile(std::string path)
{
	std::vector<std::string> list;
	std::ifstream infile(path);
	std::string line;

	if (infile.is_open())
	{
		while (std::getline(infile, line))
			list.push_back(line);
	}

	return list;
}

bool FileManager::canOpen(std::string path)
{
	return std::ifstream(path).is_open();
}
