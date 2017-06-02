#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <QStringList>
#include <QTableWidget>
#include "dataimage.h"

class Project;

class Folder 
{
	friend class MainWindow;

public:

	static const int FAT_TYPE = 0;
	static const int FIBROSIS_TYPE = 1;
	static const int BOTH_TYPE = 2;

	Folder( Project& p, std::string n, int t );
	~Folder();
	std::string getName(){ return name; }
	std::string getTypeString();

	void destroy();
	void deleteImages(QModelIndexList list);
	void uploadImages(QStringList list);
	void updateFolderFile();
	void loadImageFromFile(std::vector<std::string> list); 
	std::vector<DataImage*> getDataImageListByKeyword(std::string keyword);

private:
	Project& thisProject;
	std::string name;
	int type;
	std::vector<DataImage*> dataImageList;
	bool isNameAvailable(std::string name);
	DataImage* currentImage;

};

#endif // FOLDER_H
