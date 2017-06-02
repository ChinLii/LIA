#include "folderview.h"
#include "mainwindow.h"
#include <sstream>
#include <qheaderview.h>

FolderView::FolderView(MainWindow& m) :
AbstractView(m),
uploadImageDialog(m)
{
	init();
}

FolderView::~FolderView()
{

}

void FolderView::setupUi()
{
	QStringList headList;
	headList << "Image" << "Name" << "Processed Percentage" << "Editable Percentage" << "Size";
	imageTable.setColumnCount(5);
	imageTable.setHorizontalHeaderLabels(headList);
	imageTable.setSelectionBehavior(QAbstractItemView::SelectRows);
	imageTable.setEditTriggers(QAbstractItemView::NoEditTriggers);

	homeButton.setText("LIVER IMAGE ANALYSIS");
	uploadImageButton.setText("Upload Image");
	deleteButton.setText("Delete Image");
	searchBar = new QLineEdit(this);

	gridLayout.addWidget(&homeButton, 0, 0, 1, 1);
	gridLayout.addWidget(&projectNameButton, 0, 1, 1, 1);
	gridLayout.addWidget(&folderNameLabel, 0, 2, 1, 1);
	gridLayout.addWidget(&imageTable, 1, 1, 10, 1);
	gridLayout.addWidget(&optionLabel, 1, 0, 1, 1);
	gridLayout.addWidget(&uploadImageButton, 2, 0, 1, 1);
	gridLayout.addWidget(&deleteButton, 3, 0, 1, 1);
	

	setLayout(&gridLayout);
}

void FolderView::setupSignalAndSlot()
{
	connect(&uploadImageButton, SIGNAL(clicked()), this, SLOT(uploadImage()));
	connect(&homeButton, SIGNAL(clicked()), this, SLOT(backToHome()));
	connect(&projectNameButton, SIGNAL(clicked()), this, SLOT(backToProject()));
	connect(&imageTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(enterImage(int, int)));
	connect(&deleteButton, SIGNAL(clicked()), this, SLOT(deleteImage()));
}

void FolderView::updateView()
{



	projectNameButton.setText(mainWindow.getCurrentProject()->getName().c_str());
	folderNameLabel.setText(mainWindow.getCurrentFolder()->getName().c_str());
	
	imageTable.setRowCount(0);

	//std::vector<DataImage*> list = mainWindow.getDataImageList();
	std::vector<DataImage*> list = mainWindow.getDataImageListByKeyword(searchBar->text().toStdString());
	
	for (int i = 0; i < list.size(); i++)
	{
	
		imageTable.insertRow(i);
		// set table
		QPixmap pixmap;
		
		QString pathName = list[i]->getPath().c_str();
		QString imageName = list[i]->getName().c_str();
		
		if (pixmap.load(pathName+"/"+imageName)){
			QTableWidgetItem* image = new QTableWidgetItem;
			image->setData(Qt::DecorationRole, pixmap.scaled(50, 50));
			imageTable.setItem(i, 0, image);
		}
		imageTable.setItem(i, 1,
			new QTableWidgetItem(
			QString(list[i]->getName().c_str()))
			);
		//set percentage in table
		std::stringstream proPercent;
		std::stringstream editPercent;
		proPercent << list[i]->getPercentage(1);
		editPercent << list[i]->getPercentage(2);
		
		imageTable.setItem(i, 2,
			new QTableWidgetItem(
			QString(proPercent.str().c_str()))
			);

		imageTable.setItem(i, 3,
			new QTableWidgetItem(
			QString(editPercent.str().c_str()))
			);

		int row = list[i]->getOriginalImage().rows;
		int column = list[i]->getOriginalImage().cols;
		std::string size = std::to_string(column) + " x " + std::to_string(row);
		QString qsize = size.c_str();
		imageTable.setItem(i, 4,
			new QTableWidgetItem(
			QString(qsize))
			);
	}
	qDebug() << "**************************";
}

void FolderView::deleteImage()
{
	mainWindow.getCurrentFolder()->deleteImages(
		imageTable.selectionModel()->selectedRows()
		);

	updateView();
}

void FolderView::uploadImage()
{
	uploadImageDialog.init();
	uploadImageDialog.setModal(true);
	uploadImageDialog.show();
}

void FolderView::backToHome()
{
	mainWindow.changeView(MainWindow::HOME_VIEW);
}

void FolderView::backToProject(){
	mainWindow.changeView(MainWindow::PROJECT_VIEW);
}

void FolderView::enterImage(int row, int col)
{
	mainWindow.setCurrentImage(row);
	mainWindow.changeView(MainWindow::IMAGE_VIEW);
}