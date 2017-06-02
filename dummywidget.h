#ifndef DUMMYWIDGET_H
#define DUMMYWIDGET_H

#include <QWidget>
#include <qpushbutton.h>

class DummyWidget : public QWidget
{
	Q_OBJECT

public:
	DummyWidget();
	~DummyWidget();

private:
	QPushButton* newButton;
	QPushButton* openButton;
	
};

#endif // DUMMYWIDGET_H
