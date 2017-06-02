#ifndef  PROJECTVIEW_H
#define  PROJECTVIEW_H

#include "abstractview.h"
#include "newfolderdialog.h"
#include <QPushbutton>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QTableWidget>

class ProjectView : public AbstractView
{
	Q_OBJECT
public:
	ProjectView(MainWindow& m);
	~ProjectView();
	void updateView();
	

private:
	void setupUi();
	void setupSignalAndSlot();

	QPushButton* deleteFolderButton;
	QLineEdit* searchBar;
	NewFolderDialog newFolderDialog;
	QPushButton homeButton;
	QLabel folderNameLabel;
	QPushButton newFolderButton;
	QLabel optionsLabel;
	QLabel groupLabel;
	QCheckBox bothCheckBox;
	QCheckBox fatCheckBox;
	QCheckBox fibCheckBox;
	QTableWidget folderTable;
	QGridLayout mainLayout;


private slots:
	void updateSearchBar();
	void deleteFolder();
	void backToHome();
	void newFolder();
	void enterFolder(int row, int col);


};
#endif // PROJECTVIEW_H