#ifndef PROJECT_H
#define ‪PROJECT_H

#include <string>
#include <iostream>
#include <vector>
#include "folder.h"
#include <qstringlist.h>

	class Project
	{
		friend class MainWindow;
	public:
		Project(std::string name, std::string location);
		Project();
		~Project();
		void show();
		std::string getName(){ return name; }
		std::string getLocation(){ return location; }
		void createFolder(std::string name, int type );
		std::vector<Folder*> getFolderList(){ return folderList; }
		std::vector<Folder*> getFolderListByKeyword(std::string keyword);

		void loadFolderFromFile( std::vector<std::string> list);
		void deleteFolder(QModelIndexList list);
		

	private:
		std::string name;
		std::string location;
		std::vector<Folder*> folderList;
		Folder* currentFolder;
		void updateProjectFile();

	};

#endif // PROJECT_H