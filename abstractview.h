#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>
#include "stringhelper.h"


class MainWindow;

class AbstractView : public QWidget
{
	Q_OBJECT
public:
	AbstractView(MainWindow& m);
	~AbstractView();

	virtual void updateView(){}

protected:
	void init()
	{
		setupUi();
		setupSignalAndSlot();
	}
	virtual void setupUi() = 0;
	virtual void setupSignalAndSlot() = 0;
	MainWindow& mainWindow;


};

#endif // ABSTRACTVIEW_H
