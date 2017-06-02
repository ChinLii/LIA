#ifndef IMPORTPROJECTDIALOG_H
#define IMPORTPROJECTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include <QLineEdit>

class MainWindow;

class ImportProjectDialog : public QDialog
{
	Q_OBJECT

public:
	ImportProjectDialog(MainWindow& m);
	~ImportProjectDialog();
	void init();

private:
	MainWindow& mainWindow;
	QPushButton cancelButton;
	QPushButton importButton;
	QPushButton browseButton;
	QLabel descriptionLabel;
	QLineEdit locationEdit;
	QGridLayout gridLayout;

private slots:
	void browseLocation();
	void importProject();

	
};

#endif // IMPORTPROJECTDIALOG_H
