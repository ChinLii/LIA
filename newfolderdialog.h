#ifndef NEWFOLDERDIALOG_H
#define NEWFOLDERDIALOG_H

#include <QDialog>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qgridlayout.h>


class MainWindow;

class NewFolderDialog : public QDialog
{
	Q_OBJECT

public:
	void init();
	NewFolderDialog(MainWindow& m);
	~NewFolderDialog();

private:
	MainWindow& mainWindow;
	QPushButton cancelButton;
	QPushButton createButton;
	QLabel typeLabel;
	QLabel nameLabel;
	QCheckBox fatCheckbox;
	QCheckBox fibCheckbox;
	QLineEdit nameEdit;
	QGridLayout gridLayout;

private slots:
	void checkCreate();
	void createFolder();

};

#endif // NEWFOLDERDIALOG_H
