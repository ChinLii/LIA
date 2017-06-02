#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <fstream>
#include <QDebug>

class MainWindow;

class NewProjectDialog : public QDialog
	{
		Q_OBJECT
	public:
		void init();
		NewProjectDialog(MainWindow& m);
		~NewProjectDialog();
	private:
		MainWindow& mainWindow;
		QLabel headLabel;
		QLabel nameLabel;
		QLabel locationLabel;
		QPushButton createButton;
		QPushButton cancelButton;
		QPushButton browseButton;
		QLineEdit nameEdit;
		QLineEdit locationEdit;
		QGridLayout gridLayout;

private slots:
		void createProject();
		void browseLocation();
		void checkCanCreate();
};

#endif // NEWPROJECTDIALOG_H