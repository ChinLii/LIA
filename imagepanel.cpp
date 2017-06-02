#include "imagepanel.h"
#include <qdebug.h>

ImagePanel::ImagePanel()
{
	QVBoxLayout layout;
	layout.addWidget(&pixLabel);
	this->setLayout(&layout);
}

ImagePanel::~ImagePanel()
{

}

void ImagePanel::setImage(QPixmap pix)
{
	pixLabel.setGeometry(0, 0, pix.width(), pix.height());
	this->setGeometry(0, 0, pix.width(), pix.height());
	pixLabel.setPixmap(pix);
}

void ImagePanel::mouseDoubleClickEvent(QMouseEvent* event)
{
	qDebug() << "X:" << event->x();
	qDebug() << "Y:" << event->y();

	x = event->x();
	y = event->y();

	qDebug() << "CLICK:" << event->button();

	if (event->button() == 1 )
		emit(leftDoubleClicked());

	if (event->button() == 2 )
		emit(rightDoubleClicked());

	//update();
}
