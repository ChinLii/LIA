#include "manager.h"
#include <algorithm>
#include "Windows.h"
#include <fstream>
#include "filemanager.h"
#include <cctype>


Manager::Manager()
{
	
}

Manager::~Manager()
{
	for (int i = 0; i < projectList.size(); i++)
		delete projectList[i];
	
	projectList.resize(0);
}


std::vector<Project*> Manager::getProjectListByKeyword(std::string keyword)
{
	std::vector<Project*> displayList;
	std::string useKeyword = StringHelper::stringToLower(keyword);

	for (int i = 0; i < projectList.size(); i++)
	{
		if (StringHelper::stringToLower(projectList[i]->getName()).find(useKeyword) != std::string::npos)
		{
			displayList.push_back(projectList[i]);
		}
	}

	return displayList;
}


void Manager::createProject(std::string name, std::string location)
{

	if (!isNameAvailable(name))
	{
		qDebug() << "This name is not available.";
		return;
	}

	std::string projectPath = location + "/" + name;
	if (FileManager::createDirectory(projectPath) &&
		FileManager::createFile(projectPath + "/project.lia", name) )
	{
		qDebug() << "YEAH";
		projectList.push_back( new Project(name, projectPath));
	}

}

void Manager::importProject(std::string location)
{
	std::string path = location + "/project.lia";

	if (FileManager::canOpen(path))
	{
		std::vector<std::string> list = FileManager::getListFromFile(path);
		std::string name;

		if (list.size() > 0)
		{
			name = list[0];
		}

		if (isNameAvailable(name))
		{
			projectList.push_back( new Project(name, location));
			projectList[ projectList.size() - 1 ]->loadFolderFromFile(list);
		}

	}

}

void Manager::setCurrentProject(int index)
{
	currentProject = projectList[index];
}

bool Manager::isNameAvailable(std::string name)
{
	for (int i = 0; i < projectList.size(); i++)
	{
		if (projectList[i]->getName() == name)
			return false;
	}
	return true;
}

