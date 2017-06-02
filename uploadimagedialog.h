#ifndef UPLOADIMAGEDIALOG_H
#define UPLOADIMAGEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTableWidget>
#include <qgridlayout.h>

class MainWindow;

class UploadImageDialog : public QDialog
{
	Q_OBJECT

public:
	UploadImageDialog(MainWindow& m);
	~UploadImageDialog();
	void init();

private:
	MainWindow& mainWindow;
	QPushButton browseButton;
	QPushButton deleteButton;
	QPushButton cancelButton;
	QPushButton uploadButton;
	QTableWidget imageTable;
	QGridLayout gridLayout;
	QStringList imagePathList;
	void updateDialog();

	private slots:
	void browseImage();
	void deleteImage();
	void uploadImages();
	
};

#endif // UPLOADIMAGEDIALOG_H
