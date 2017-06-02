#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include "abstractview.h"
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QGridLayout>
#include "uploadimagedialog.h"
#include <qpixmap.h>
#include <qlineedit.h>

class FolderView : public AbstractView
{
	Q_OBJECT

public:
	FolderView(MainWindow& m);
	~FolderView();
	void updateView();

private:

	
	QGridLayout gridLayout;
	QPushButton uploadImageButton;
	QLabel optionLabel;
	QPushButton homeButton;
	QPushButton projectNameButton;
	QPushButton deleteButton;
	QLabel folderNameLabel;
	QTableWidget imageTable;
	UploadImageDialog uploadImageDialog;
	
	QLineEdit* searchBar;

	void setupUi();
	void setupSignalAndSlot();
	

private slots:
	void uploadImage();
	void backToHome();
	void backToProject();
	void enterImage(int r, int c);
	void deleteImage();
	
};

#endif // FOLDERVIEW_H
