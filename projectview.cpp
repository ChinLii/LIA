#include "projectview.h"
#include "mainwindow.h"

ProjectView::ProjectView(MainWindow &m) :
	AbstractView(m),
	newFolderDialog(m)
{
	init();
}
ProjectView::~ProjectView()
{
}
void ProjectView::setupUi()
{
	QStringList headList;
	headList << "Type" << "Name" << "Created Date" << "Date Modified";
	folderTable.setColumnCount(4);
	folderTable.setHorizontalHeaderLabels(headList);
	folderTable.setSelectionBehavior(QAbstractItemView::SelectRows);
	folderTable.setEditTriggers(QAbstractItemView::NoEditTriggers);

	deleteFolderButton = new QPushButton();
	deleteFolderButton->setText("Delete Folder");

	homeButton.setText("LIVER IMAGE ANALYSIS");

	optionsLabel.setText("Project Options");
	newFolderButton.setText("New Folder");
	
	searchBar = new QLineEdit(this);
	searchBar->setGeometry(600, 10, 160, 30);

	groupLabel.setText("Group by Type");
	bothCheckBox.setText("Both");
	fatCheckBox.setText("Fat Detection");
	fibCheckBox.setText("Fibrosis Detection");

	mainLayout.addWidget(&folderTable, 1, 1, 10, 1);
	mainLayout.addWidget(&homeButton, 0, 0, 1, 1);
	mainLayout.addWidget(&folderNameLabel, 0, 1, 1, 1);
	
	mainLayout.addWidget(&optionsLabel, 1, 0, 1, 1);
	mainLayout.addWidget(&newFolderButton, 2, 0, 1, 1);
	mainLayout.addWidget(deleteFolderButton, 3, 0, 1, 1);
	
	mainLayout.addWidget(&groupLabel, 4, 0, 1, 1);
	mainLayout.addWidget(&bothCheckBox,5, 0, 1, 1);
	mainLayout.addWidget(&fatCheckBox, 6, 0, 1, 1);
	mainLayout.addWidget(&fibCheckBox, 7, 0, 1, 1);

	setLayout(&mainLayout);
}

void ProjectView::setupSignalAndSlot(){

	connect(&homeButton, SIGNAL(clicked()), this, SLOT(backToHome()));
	connect(&newFolderButton, SIGNAL(clicked()), this, SLOT(newFolder()));
	connect(&folderTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(enterFolder(int, int)));
	connect(deleteFolderButton, SIGNAL(clicked()), this, SLOT(deleteFolder()));
	connect(searchBar, SIGNAL(textChanged(QString)), this, SLOT(updateSearchBar()));

}

void ProjectView::updateSearchBar()
{
	updateView();
}

void ProjectView::backToHome(){

	mainWindow.changeView(0);
}

void ProjectView::newFolder()
{
	newFolderDialog.init();
	newFolderDialog.setModal(true);
	newFolderDialog.show();
}

void ProjectView::enterFolder(int row, int col)
{
	mainWindow.setCurrentFolder(row);
	mainWindow.changeView(MainWindow::FOLDER_VIEW);
	
}

void ProjectView::deleteFolder()
{
	mainWindow.getCurrentProject()->deleteFolder(
		folderTable.selectionModel()->selectedRows()
		);

	updateView();
}



void ProjectView::updateView()
{
	folderNameLabel.setText(mainWindow.getCurrentProject()->getName().c_str());

	folderTable.setRowCount(0);

	/*std::vector<Folder*> list = mainWindow.getFolderList();*/
	std::vector<Folder*> list = mainWindow.getFolderListByKeyword(searchBar->text().toStdString());

	for (int i = 0; i < list.size(); i++)
	{

		folderTable.insertRow(i);

	
		// set folder type
		folderTable.setItem(i, 0,
			new QTableWidgetItem(
			QString(list[i]->getTypeString().c_str()))
			);

		// set folder name
		folderTable.setItem(i, 1,
			new QTableWidgetItem(
			QString(list[i]->getName().c_str()))
			);

		// manager.getProjectList().at(i);
	}
}