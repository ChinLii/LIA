#include "project.h"
#include "Windows.h"
#include <fstream>
#include <qdebug.h>
#include "filemanager.h"

Project::Project(std::string name, std::string location)
{
	this->name = name;
	this->location = location;
}
Project::Project()
{
}
void Project::show()
{
	std::cout << name << " - " << location << std::endl;
}
Project::~Project()
{
}

void Project::createFolder(std::string name, int type )
{
	std::string path = location + "//" + name;

	std::string text = name + "\n" + std::to_string(type);

	if (FileManager::createDirectory(path) &&
		FileManager::createFile(path + "/folder.lia", text ) )
	{
		folderList.push_back( new Folder(*this, name, type));
		updateProjectFile();
	}


}

std::vector<Folder*> Project::getFolderListByKeyword(std::string keyword)
{
	std::vector<Folder*> displayList;
	std::string useKeyword = StringHelper::stringToLower(keyword);

	for (int i = 0; i < folderList.size(); i++)
	{
		if (StringHelper::stringToLower(folderList[i]->getName()).find(useKeyword) != std::string::npos)
		{
			displayList.push_back(folderList[i]);
		}
	}

	return displayList;
}

void Project::updateProjectFile()
{
	std::string text = name;

	for (int i = 0; i < folderList.size(); i++)
		text += "\n" + folderList[i]->getName();

	FileManager::createFile(location + "/project.lia", text);
}

void Project::deleteFolder(QModelIndexList list)
{
	std::vector<Folder*> tempList;

	for (int i = 0; i < folderList.size(); i++)
	{
		bool stay = true;
		for (int j = 0; j < list.size(); j++)
		{
			if (i == list.at(j).row())
			{
				stay = false;

				folderList[i]->destroy();

				delete folderList[i];
				break;
			}
		}

		if (stay)
			tempList.push_back(folderList[i]);
	}

	folderList = tempList;
	updateProjectFile();
}

void Project::loadFolderFromFile( std::vector<std::string> listFromFile )
{
	std::string path;
	std::string folderName;

	for (int i = 1; i < listFromFile.size(); i++)
	{
		path = location + "/" + listFromFile[i] + "/folder.lia";

		if (FileManager::canOpen(path))
		{
			std::vector<std::string> list = FileManager::getListFromFile(path);

			if (list.size() > 1)
			{
				std::string folderName = list[0];
				int folderType = std::stoi(list[1], nullptr);
				
				Folder* tempFolder = new Folder(*this, folderName, folderType);
				tempFolder->loadImageFromFile(list);
				folderList.push_back(tempFolder);
			}
		}

		else
		{
			qDebug() << "ERROR: Can not open folder.lia";
		}
	}
}