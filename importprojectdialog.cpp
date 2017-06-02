#include "importprojectdialog.h"
#include "mainwindow.h"

ImportProjectDialog::ImportProjectDialog(MainWindow& m ) : 
	mainWindow(m)
{
	
	descriptionLabel.setText("Project Location");
	locationEdit.setEnabled(false);
	browseButton.setText("Browse");
	cancelButton.setText("Cancel");
	importButton.setText("Import");


	gridLayout.addWidget(&descriptionLabel, 0, 0, 1, 1);
	gridLayout.addWidget(&locationEdit, 1, 0, 1, 3);
	gridLayout.addWidget(&browseButton, 1, 3, 1, 1);
	gridLayout.addWidget(&cancelButton, 2, 2, 1, 1);
	gridLayout.addWidget(&importButton, 2, 3, 1, 1);


	setLayout(&gridLayout);


	connect(&browseButton, SIGNAL(clicked()), this, SLOT(browseLocation()));
	connect(&cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
	connect(&importButton, SIGNAL(clicked()), this, SLOT(importProject()));
}

ImportProjectDialog::~ImportProjectDialog()
{

}

void ImportProjectDialog::init()
{
	locationEdit.clear();
}

void ImportProjectDialog::browseLocation()
{
	QString filename = QFileDialog::getExistingDirectory(this);
	locationEdit.setText(filename);
}

void ImportProjectDialog::importProject()
{
	mainWindow.importProject(locationEdit.text().toStdString());
	this->hide();
}