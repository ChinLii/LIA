#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <QWidget>
#include <qevent.h>
#include <qpixmap.h>
#include <qlabel.h>
#include <qlayout.h>

class ImagePanel : public QWidget
{
	Q_OBJECT

public:
	ImagePanel();
	~ImagePanel();

	int x;
	int y;

	void setImage(QPixmap pix);

signals:
	void leftDoubleClicked();
	void rightDoubleClicked();

private:
	QLabel pixLabel;

	void mouseDoubleClickEvent(QMouseEvent* Event);

};
	
#endif // IMAGEPANEL_H
