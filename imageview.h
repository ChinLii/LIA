#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H


#include "abstractview.h"
#include <qpushbutton.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <qslider.h>
#include <qtextedit.h>
#include <qscrollarea.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "imagepanel.h"
#include "imagemode.h"
#include "originalmode.h"
#include "processedmode.h"
#include "editablemode.h"
#include "dataimage.h"

class ImageView : public AbstractView
{
	Q_OBJECT

public:
	static const int ORIGINAL_MODE = 0;
	static const int PROCESSED_MODE = 1;
	static const int EDITABLE_MODE = 2;

	
	ImageView( MainWindow& m );
	~ImageView();

	void clickOnImage(int i);
	void updateView();
	void setMode(int mode);

private:

	DataImage* currentDataImage;
	std::vector<ImageMode*> modeList;

	int zoomPercent;
	ImageMode* currentMode;
	ImagePanel* imagePanel;

	void setupUi();
	void setupSignalAndSlot();

	void setFibrosisSlider();
	void setFatSlider();
	void saveSliderValue();

	QGridLayout gridLayout;



	QLabel fatSliderHeadLabel;
	QLabel fibSliderHeadLabel;
	QLabel imageNameLabel;

	QPushButton homeButton;
	QPushButton projectButton;

	QPushButton* saveButton;
	QTextEdit* noteEdit;
	QPushButton* folderButton;
	QPushButton* processButton;

	QPushButton* originalModeButton;
	QPushButton* processedModeButton;
	QPushButton* editableModeButton;

	QLabel* zoomValueLabel;
	QPushButton* zoomInButton;
	QPushButton* zoomOutButton;

	QSlider* minSizeSlider;
	QSlider* maxSizeSlider;
	QLabel* minSizeValueLabel;
	QLabel* maxSizeValueLabel;
	
	QSlider* minCirSlider;
	QSlider* maxCirSlider;
	QLabel* minCirValueLabel;
	QLabel* maxCirValueLabel;

	QSlider* minSatSlider;
	QSlider* maxSatSlider;

	QLabel* sizeSliderLabel;
	QLabel* cirSliderLabel;

	QScrollArea* imageScrollArea;
	

private slots:
	void zoomIn();
	void zoomOut();
	void saveImage();
	void leftClickOnPanel();
	void rightClickOnPanel();
	void backToHome();
	void backToProject();
	void backToFolder();
	void enterOriginalMode();
	void enterProcessedMode();
	void enterEditableMode();
	void processImage();
	void setSliderValueLabels();
	
};

#endif // IMAGEVIEW_H
