#include "dummywidget.h"

DummyWidget::DummyWidget()
{
	newButton = new QPushButton(this);
	newButton->setText("New Project");
	newButton->setGeometry(20, 50, 110, 30);

	openButton = new QPushButton(this);
	openButton->setText("Open Project");
	openButton->setGeometry(20, 90, 110, 30);
}

DummyWidget::~DummyWidget()
{

}
