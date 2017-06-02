#include "mainWindow.h"
#include "newprojectdialog.h"

NewProjectDialog::NewProjectDialog(MainWindow& m) :
mainWindow(m)
{
	setWindowTitle("New LIA Project");
	headLabel.setText("Name and Location");
	nameLabel.setText("Project Name: ");
	locationLabel.setText("Project Location: ");
	browseButton.setText("Browse");
	createButton.setText("Create");
	cancelButton.setText("Cancel");
	locationEdit.setEnabled(false);
	createButton.setEnabled(false);
	gridLayout.addWidget(&headLabel, 0, 0, 1, 2);
	gridLayout.addWidget(&nameLabel, 1, 0, 1, 1);
	gridLayout.addWidget(&nameEdit, 1, 1, 1, 3);
	gridLayout.addWidget(&locationLabel, 2, 0, 1, 1);
	gridLayout.addWidget(&locationEdit, 2, 1, 1, 2);
	gridLayout.addWidget(&browseButton, 2, 3, 1, 1);
	gridLayout.addWidget(&createButton, 3, 3, 1, 1);
	gridLayout.addWidget(&cancelButton, 3, 2, 1, 1);
	setLayout(&gridLayout);
	connect(&nameEdit, SIGNAL(textChanged(QString)), this, SLOT(checkCanCreate()));
	connect(&locationEdit, SIGNAL(textChanged(QString)), this, SLOT(checkCanCreate()));
	connect(&browseButton, SIGNAL(clicked()), this, SLOT(browseLocation()));
	connect(&createButton, SIGNAL(clicked()), this, SLOT(createProject()));
	connect(&cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
}
NewProjectDialog::~NewProjectDialog()
{
}
void NewProjectDialog::init()
{
	nameEdit.clear();
	locationEdit.clear();
}
void NewProjectDialog::browseLocation()
{
	QString filename = QFileDialog::getExistingDirectory(this);
	locationEdit.setText(filename);
	checkCanCreate();
}
void NewProjectDialog::createProject()
{
	std::string projectName = nameEdit.text().toStdString();
	std::string projectPath = locationEdit.text().toStdString();
	
	qDebug() << nameEdit.text() << " " << locationEdit.text();
	
	mainWindow.createProject(projectName, projectPath);
	this->hide();
}
void NewProjectDialog::checkCanCreate()
{
	createButton.setEnabled(nameEdit.text().size() > 0 && locationEdit.text().size() > 0);
}