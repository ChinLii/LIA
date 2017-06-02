#include "uploadimagedialog.h"
#include <QFileDialog>
#include <QDebug>
#include "mainwindow.h"

UploadImageDialog::UploadImageDialog(MainWindow& m)
	: mainWindow(m)
{

	QStringList headList;
	headList << "Image" << "Filename";
	imageTable.setColumnCount(2);
	imageTable.setHorizontalHeaderLabels(headList);
	imageTable.setSelectionBehavior(QAbstractItemView::SelectRows);
	imageTable.setEditTriggers(QAbstractItemView::NoEditTriggers);


	
	browseButton.setText("Browse");
	deleteButton.setText("Delete");
	cancelButton.setText("Cancel");
	uploadButton.setText("Upload");


	gridLayout.addWidget(&imageTable, 0, 1, 4, 3);
	gridLayout.addWidget(&browseButton, 0, 0, 1, 1);
	gridLayout.addWidget(&deleteButton, 1, 0, 1, 1);
	gridLayout.addWidget(&cancelButton, 5, 3, 1, 1);
	gridLayout.addWidget(&uploadButton, 5, 4, 1, 1);
	setLayout(&gridLayout);


	connect(&browseButton, SIGNAL(clicked()), this, SLOT(browseImage()));
	connect(&deleteButton, SIGNAL(clicked()), this, SLOT(deleteImage()));
	connect(&cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
	connect(&uploadButton, SIGNAL(clicked()), this, SLOT(uploadImages()));
}

UploadImageDialog::~UploadImageDialog()
{

}

void UploadImageDialog::init()
{
	imageTable.setRowCount(0);
	imagePathList.clear();
}

void UploadImageDialog::updateDialog()
{
	imageTable.setRowCount(0);
	for (int i = 0; i < imagePathList.size(); i++)
	{
		QFileInfo fileInfo(imagePathList.at(i));
		QPixmap pixmap;
		if (pixmap.load(imagePathList.at(i)))
		{

			QTableWidgetItem* image = new QTableWidgetItem;
			image->setData(Qt::DecorationRole, pixmap.scaled(50, 50));
			imageTable.insertRow(i);
			imageTable.setItem(i, 1, new QTableWidgetItem(fileInfo.fileName()));
			imageTable.setItem(i, 0, image);
		}
	}
}

void UploadImageDialog::browseImage()
{ 
	QStringList list = QFileDialog::getOpenFileNames();
	for (int i = 0; i < list.size(); i++)
	{
		QPixmap pixmap;
		if (pixmap.load(list.at(i)))
			imagePathList.push_back(list.at(i));
	}

	updateDialog();
}

void UploadImageDialog::deleteImage()
{
	//remove from list 
	QItemSelectionModel *select = imageTable.selectionModel();
	QModelIndexList list = select->selectedRows();
	
	QStringList dummyImagePathList;

	for (int i = 0; i < imagePathList.size(); i++)
	{
		bool stay = true;
		for (int j = 0; j < list.size(); j++)
		{
			if (i == list.at(j).row())
			{
				stay = false;
				break;
			}
		}

		if ( stay )
			dummyImagePathList.push_back(imagePathList.at(i));
	}

	imagePathList = dummyImagePathList;
	
	updateDialog();
}

void UploadImageDialog::uploadImages()
{
	for (int i = 0; i < imagePathList.size(); i++)
	{
		qDebug() << imagePathList.at(i);
	}
	mainWindow.uploadImages(imagePathList);
	this->hide();
}