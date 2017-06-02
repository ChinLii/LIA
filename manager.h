#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <QDebug>
#include "project.h"

class MainWindow;

class Manager
{
	friend class MainWindow;
public:
	Manager();
	~Manager();

	// Project
	void createProject(std::string name, std::string location);
	void importProject(std::string location);
	void setCurrentProject(int index);
	std::vector<Project*> getProjectListByKeyword(std::string keyword);
	// Folder


	
	bool isNameAvailable( std::string name );

private:
	std::vector<Project*> projectList;
	Project* currentProject;
	
};

#endif // MANAGER_H