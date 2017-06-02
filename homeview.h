#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include "abstractview.h"
#include <QPushButton>
#include <QDialog>
#include <QGridLayout>
#include <QTableWidget>
#include <QLabel>
#include <string>
#include "newprojectdialog.h"
#include "importprojectdialog.h"

class HomeView : public AbstractView
{
	Q_OBJECT

public:
	HomeView(MainWindow& m);
	~HomeView();
	void updateProjectList();
	void updateView();

private:
	void setupUi();
	void setupSignalAndSlot();


	// ui
	QLabel* headLabel;
	QTableWidget* projectTable;
	QPushButton* newProjectButton;
	QPushButton* openProjectButton;
	QLineEdit* searchBar;
	NewProjectDialog newProjectDialog;
	ImportProjectDialog impProjectDialog;
	

private slots:
	void updateSearchBar();
	void newProject();
	void importProject();
	void test(int row, int column);
};

#endif // HOMEVIEW_H