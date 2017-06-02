#include "mainwindow.h"
#include "homeview.h"
#include "projectview.h"
#include "folderview.h"
#include "imageview.h"

MainWindow::MainWindow()
{
	views.push_back( new HomeView(*this));
	views.push_back( new ProjectView(*this));
	views.push_back( new FolderView(*this));
	views.push_back( new ImageView(*this));

	for (int i = 0; i < views.size(); i++)
		stackedLayout.addWidget( views[i] );

	setLayout(&stackedLayout);
	resize(1200, 700);
} 
MainWindow::~MainWindow()
{

}

std::vector<Project*> MainWindow::getProjectList()
{
	return manager.projectList;
}

std::vector<Project*> MainWindow::getProjectListByKeyword(std::string keyword)
{
	return manager.getProjectListByKeyword(keyword);
}

std::vector<Folder*> MainWindow::getFolderListByKeyword(std::string keyword)
{
	return manager.currentProject->getFolderListByKeyword(keyword);
}

std::vector<DataImage*> MainWindow::getDataImageListByKeyword(std::string keyword)
{
	return manager.currentProject->currentFolder->getDataImageListByKeyword(keyword);
}

std::vector<Folder*> MainWindow::getFolderList()
{
	return manager.currentProject->folderList;
}

std::vector<DataImage*> MainWindow::getDataImageList()
{
	return manager.currentProject->currentFolder->dataImageList;
}

void MainWindow::createProject(std::string name, std::string location)
{
	manager.createProject(name, location);
	notifyUpdate();
}

void MainWindow::importProject(std::string location)
{
	manager.importProject(location);
	notifyUpdate();
}

void MainWindow::notifyUpdate()
{
	views[ stackedLayout.currentIndex() ]->updateView();
}

void MainWindow::changeView(int view)
{
	stackedLayout.setCurrentIndex(view);
	notifyUpdate();
}

void MainWindow::setCurrentProject(int index)
{
	manager.setCurrentProject(index);
}

void MainWindow::setCurrentFolder(int index)
{
	Project* projectDummy = manager.currentProject;

	if ( projectDummy != NULL )
		projectDummy->currentFolder = projectDummy->folderList[index];
}

void MainWindow::setCurrentImage(int index)
{
	Folder* folderDummy = manager.currentProject->currentFolder;

	if (folderDummy != NULL)
	{
		folderDummy->currentImage = folderDummy->dataImageList[index];
		folderDummy->currentImage->init();
	}
}


Project* MainWindow::getCurrentProject()
{
	return manager.currentProject;
}

Folder* MainWindow::getCurrentFolder()
{
	return manager.currentProject->currentFolder;
}

void MainWindow::createFolder(std::string name, int type)
{
	manager.currentProject->createFolder(name,type);
	notifyUpdate();
}

void MainWindow::uploadImages(QStringList imagePathList)
{
	manager.currentProject->currentFolder->uploadImages(imagePathList);
	notifyUpdate();
}

DataImage* MainWindow::getCurrentDataImage()
{
	return manager.currentProject->currentFolder->currentImage;
}