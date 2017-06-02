#include "folder.h"
#include "project.h"
#include <Windows.h>
#include <qfileinfo.h>
#include "qdebug.h"
#include <fstream>
#include "filemanager.h"

Folder::Folder( Project& p, std::string n, int t ):
thisProject(p)
{
	name = n;
	type = t;
	qDebug() << "Folder address " << this;
}

Folder::~Folder()
{

}

void Folder::destroy()
{

	for (int i = 0; i < dataImageList.size(); i++)
	{
		dataImageList[i]->destroy();
		delete dataImageList[i];
	}

	dataImageList.resize(0);

	std::string fullPath = thisProject.getLocation() + "/" + this->name;

	// delete folder.lia file
	FileManager::deleteFile(fullPath + "/folder.lia");

	// delete folder from directory
	FileManager::deleteDirectory(fullPath);
}

std::vector<DataImage*> Folder::getDataImageListByKeyword(std::string keyword)
{
	std::vector<DataImage*> displayList;
	std::string useKeyword = StringHelper::stringToLower(keyword);

	for (int i = 0; i < dataImageList.size(); i++)
	{
		if (StringHelper::stringToLower(dataImageList[i]->getName()).find(useKeyword) != std::string::npos)
		{
			displayList.push_back(dataImageList[i]);
		}
	}

	return displayList;
}

void Folder::deleteImages(QModelIndexList list)
{
	std::vector<DataImage*> tempList;

	for (int i = 0; i < dataImageList.size(); i++)
	{
		bool stay = true;
		for (int j = 0; j < list.size(); j++)
		{
			if (i == list.at(j).row())
			{
				stay = false;

				std::string deletePath = dataImageList[i]->getPath() + "/" + dataImageList[i]->getName();
				
				// delete the raw image
				FileManager::deleteFile(deletePath);
						
				// delete data file for the image
				FileManager::deleteFile(deletePath + ".data" );

				delete dataImageList[i];
				break;
			}
		}

		if (stay)
			tempList.push_back(dataImageList[i]);
	}

	dataImageList = tempList;
	updateFolderFile();
	
}

void Folder::uploadImages(QStringList list)
{
	std::string targetPath = thisProject.getLocation() + "/" + name;
	
	for (int i = 0; i < list.size(); i++)
	{
		QFileInfo fileInfo(list.at(i));
		std::string filename = fileInfo.fileName().toStdString(); 

		

		if ( isNameAvailable( filename ) &&
				FileManager::copyFile(list.at(i).toStdString(), targetPath, filename ) &&
				FileManager::createFile(targetPath + "/" + filename + ".data", filename ) )
		{
			DataImage* dImage = new DataImage(filename, targetPath, this->type );
			dImage->init();
			dataImageList.push_back( dImage );
		}
		
	}

	updateFolderFile();

}

bool Folder::isNameAvailable(std::string name)
{
	for (int i = 0; i < dataImageList.size(); i++)
	{
		if (dataImageList[i]->getName() == name)
			return false;
	}

	return true;

}

std::string Folder::getTypeString()
{
	if (type == FAT_TYPE)
		return "Fat Detection";

	if (type == FIBROSIS_TYPE)
		return "Fibrosis Detection";

	return "Both";
}



void Folder::updateFolderFile()
{
	std::string text = name + "\n";
	text += std::to_string(type);

	for (int i = 0; i < dataImageList.size(); i++)
	{
		text += "\n" + dataImageList[i]->getName();
	}

	FileManager::createFile(thisProject.getLocation() + "/" + name + "/folder.lia", text);

}



void Folder::loadImageFromFile(std::vector<std::string> listFromFile )
{

	// index 0 = folder name
	// index 1 = folder type
	// start loop from index 2
	std::string targetPath = thisProject.getLocation() + "/" + name;
	
	int type = -1;
	
	if (listFromFile.size() >= 1)
		type = std::stoi(listFromFile[1]);

	if (type == -1)
		return;
	
	for (int i = 2; i < listFromFile.size(); i++)
	{
		DataImage* dImage = new DataImage(listFromFile[i], targetPath, type );
		dImage->init();
		dataImageList.push_back( dImage );
	}

}


