#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QStackedLayout>
#include <QWidget>
#include "manager.h"
#include "abstractview.h"
#include <vector>
#include <qimage.h>

class MainWindow : public QWidget
{
		Q_OBJECT
	public:
		enum View{ HOME_VIEW, PROJECT_VIEW, FOLDER_VIEW, IMAGE_VIEW };

		MainWindow();
		~MainWindow();
		

		// Home View
		std::vector<Project*> getProjectList();
		std::vector<Project*> getProjectListByKeyword(std::string keyword);
		void createProject(std::string name, std::string location);
		void importProject(std::string location);
		void setCurrentProject(int index);
		Project* getCurrentProject();

		// Project View
		std::vector<Folder*> getFolderListByKeyword(std::string keyword);
		std::vector<Folder*> getFolderList();
		void createFolder(std::string name, int type );
		void setCurrentFolder(int index);
		Folder* getCurrentFolder();

		// Folder View
		std::vector<DataImage*> getDataImageList();
		std::vector<DataImage*> getDataImageListByKeyword(std::string keyword);
		void uploadImages(QStringList imagePathList);
		void setCurrentImage(int index);

		// Image View
		DataImage* getCurrentDataImage();

		
	public slots:
		void changeView(int view);


	private:
		void notifyUpdate();
		Manager manager;
		QStackedLayout stackedLayout;
		
		std::vector<AbstractView*> views;

	};

#endif // MAINWINDOW_H