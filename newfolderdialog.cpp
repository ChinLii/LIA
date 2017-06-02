#include "newfolderdialog.h"
#include "mainwindow.h"

NewFolderDialog::NewFolderDialog(MainWindow& m) :
mainWindow(m)
{
	nameLabel.setText("Folder Name:");
	typeLabel.setText("Folder Type");
	fatCheckbox.setText("Fat Detection");
	fibCheckbox.setText("Fibrosis Detection");
	cancelButton.setText("Cancel");
	createButton.setText("Create");

	gridLayout.addWidget(&nameLabel, 0, 0, 1, 1);
	gridLayout.addWidget(&nameEdit, 0, 1, 1, 2);
	gridLayout.addWidget(&typeLabel, 1, 0, 1, 1);
	gridLayout.addWidget(&fatCheckbox, 2, 1, 1, 2);
	gridLayout.addWidget(&fibCheckbox, 3, 1, 1, 2);
	gridLayout.addWidget(&cancelButton, 4, 2, 1, 1);
	gridLayout.addWidget(&createButton, 4, 3, 1, 1);
	
	setLayout(&gridLayout);

	connect(&nameEdit, SIGNAL(textChanged(QString)), this, SLOT(checkCreate()));
	connect(&fatCheckbox, SIGNAL(stateChanged(int)), this, SLOT(checkCreate()));
	connect(&fibCheckbox, SIGNAL(stateChanged(int)), this, SLOT(checkCreate()));
	connect(&cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
	connect(&createButton, SIGNAL(clicked()), this, SLOT(createFolder()));

	createButton.setEnabled(false);

}

NewFolderDialog::~NewFolderDialog()
{

}

void NewFolderDialog::init()
{
	nameEdit.clear();
	fatCheckbox.setChecked(false);
	fibCheckbox.setChecked(false);
}

void NewFolderDialog::checkCreate()
{
	createButton.setEnabled(
			nameEdit.text().size() > 0 &&
			(fatCheckbox.isChecked() || fibCheckbox.isChecked())
		);
	
}

void NewFolderDialog::createFolder()
{
	int folderType = 1;

	if (fatCheckbox.isChecked())
	{
		if (fibCheckbox.isChecked())
			folderType = 2;
		else
			folderType = 0;
	}
	

	mainWindow.createFolder(nameEdit.text().toStdString(), folderType );
	this->hide();
}