#include "homeview.h"
#include <QDebug>
#include "mainwindow.h"
#include <vector>


HomeView::HomeView(MainWindow& m) :
	AbstractView(m),
	newProjectDialog(m),
	impProjectDialog(m)
{
	init();
}

HomeView::~HomeView()
{

}

void HomeView::setupUi()
{
	this->resize(920, 640);


	QStringList headList;
	headList << "Name" << "Created Date" << "Date Modified";
	projectTable = new QTableWidget(this);
	projectTable->setColumnCount(3);
	projectTable->setHorizontalHeaderLabels(headList);
	projectTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	projectTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	projectTable->setGeometry(150, 50, 630, 530);

	newProjectButton = new QPushButton(this);
	newProjectButton->setText("New Project");
	newProjectButton->setGeometry(20, 50, 110, 30);
	
	openProjectButton = new QPushButton(this);
	openProjectButton->setText("Open Project");
	openProjectButton->setGeometry(20, 90, 110, 30);

	headLabel = new QLabel(this);
	headLabel->setText("LIVER IMAGE ANALYSIS");
	headLabel->setGeometry(30, 10, 120, 30);

	searchBar = new QLineEdit(this);
	searchBar->setGeometry(600, 10, 180, 25);

}

void HomeView::setupSignalAndSlot()
{
	connect(projectTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(test(int, int)));
	connect(newProjectButton, SIGNAL(clicked()), this, SLOT(newProject()));
	connect(openProjectButton, SIGNAL(clicked()), this, SLOT(importProject()));
	connect(searchBar, SIGNAL(textChanged(QString)), this, SLOT(updateSearchBar()));
}

void HomeView::updateSearchBar()
{
	qDebug() << "UPDATE SEARCH BAR";
	updateView();
}

void HomeView::newProject()
{
	newProjectDialog.init();
	newProjectDialog.setModal(true);
	newProjectDialog.show();
}

void HomeView::importProject()
{
	impProjectDialog.init();
	impProjectDialog.setModal(true);
	impProjectDialog.show();
}

void HomeView::test(int row, int column)
{
	mainWindow.setCurrentProject(row);
	mainWindow.changeView(MainWindow::PROJECT_VIEW);


}



void HomeView::updateView()
{
	projectTable->setRowCount(0);

	//std::vector<Project*> list = mainWindow.getProjectList();

	std::vector<Project*> list = mainWindow.getProjectListByKeyword(searchBar->text().toStdString());
	for (int i = 0; i < list.size(); i++)
	{

		projectTable->insertRow(i);

		projectTable->setItem(i, 0,
			new QTableWidgetItem(
			QString(list[i]->getName().c_str()))
			);

		// manager.getProjectList().at(i);
	}
}