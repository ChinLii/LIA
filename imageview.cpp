#include "imageview.h"
#include "mainwindow.h"
#include <qdebug.h>
#include "qscrollbar.h"

ImageView::ImageView( MainWindow& m ):
	AbstractView(m),
	zoomPercent(100)
{
	modeList.push_back(new OriginalMode());
	modeList.push_back(new ProcessedMode());
	modeList.push_back(new EditableMode());
	currentMode = modeList[ORIGINAL_MODE];

	init();
}

ImageView::~ImageView()
{

}

void ImageView::updateView()
{
	currentDataImage = mainWindow.getCurrentDataImage();


	zoomValueLabel->setText(currentDataImage->getCurrentZoom().c_str());

	noteEdit->setText(currentDataImage->getNote().c_str());

	if ( currentDataImage->getType() == Folder::FAT_TYPE)
	{
		setFatSlider();
	}
	else if (currentDataImage->getType() == Folder::FIBROSIS_TYPE)
	{
		setFibrosisSlider();
	}
	else
	{
		setFatSlider();
		setFibrosisSlider();
	}


	int v = imageScrollArea->verticalScrollBar()->value();
	int h = imageScrollArea->horizontalScrollBar()->value();
	
	disconnect(imagePanel, SIGNAL(leftDoubleClicked()), this, SLOT(leftClickOnPanel()));
	disconnect(imagePanel, SIGNAL(rightDoubleClicked()), this, SLOT(rightClickOnPanel()));
	delete imagePanel;
	imagePanel = new ImagePanel;

	imagePanel->setImage(QPixmap::fromImage(
		currentDataImage->getQImage(currentMode->code())
		));

	imageScrollArea->setWidget(imagePanel);
	connect(imagePanel, SIGNAL(leftDoubleClicked()), this, SLOT(leftClickOnPanel()));
	connect(imagePanel, SIGNAL(rightDoubleClicked()), this, SLOT(rightClickOnPanel()));

	imageScrollArea->verticalScrollBar()->setValue(v);
	imageScrollArea->horizontalScrollBar()->setValue(h);

	folderButton->setText(mainWindow.getCurrentFolder()->getName().c_str());




}

void ImageView::saveSliderValue()
{

	if (currentDataImage->getType() == Folder::FAT_TYPE || currentDataImage->getType() == Folder::BOTH_TYPE)
	{
		
		// Circularity
		currentDataImage->setFatSliderValue(1, 1, minCirSlider->value());
		currentDataImage->setFatSliderValue(1, 2, maxCirSlider->value());

		// Size
		currentDataImage->setFatSliderValue(2, 1, minSizeSlider->value());
		currentDataImage->setFatSliderValue(2, 2, maxSizeSlider->value());
	}
}

void ImageView::setFatSlider()
{

	minSizeSlider->setRange(currentDataImage->getMinBlobSize(),
		currentDataImage->getMaxBlobSize());
	maxSizeSlider->setRange(currentDataImage->getMinBlobSize(),
		currentDataImage->getMaxBlobSize());

	minCirSlider->setValue(currentDataImage->getFatSliderValue(1, 1));
	maxCirSlider->setValue(currentDataImage->getFatSliderValue(1, 2));

	minSizeSlider->setValue(currentDataImage->getFatSliderValue(2, 1));
	maxSizeSlider->setValue(currentDataImage->getFatSliderValue(2, 2));

	if (currentMode->code() == EDITABLE_MODE)
	{
		minCirSlider->setEnabled(true);
		maxCirSlider->setEnabled(true);
		minSizeSlider->setEnabled(true);
		maxSizeSlider->setEnabled(true);
		processButton->setEnabled(true);
	}
	else
	{
		minCirSlider->setEnabled(false);
		maxCirSlider->setEnabled(false);
		minSizeSlider->setEnabled(false);
		maxSizeSlider->setEnabled(false);
		processButton->setEnabled(false);
	}
}

void ImageView::setFibrosisSlider()
{

}

void ImageView::setSliderValueLabels()
{

	// set circularity silder value
	std::stringstream minCirSS;
	minCirSS << std::setprecision(2) << minCirSlider->value() / 100.0;

	std::stringstream maxCirSS;
	maxCirSS << std::setprecision(2) << maxCirSlider->value() / 100.0;

	minCirValueLabel->setText(minCirSS.str().c_str());
	maxCirValueLabel->setText(maxCirSS.str().c_str());

	// set size slider value
	int minSize = minSizeSlider->value();
	int maxSize = maxSizeSlider->value();

	minSizeValueLabel->setText(std::to_string(minSize).c_str());
	maxSizeValueLabel->setText(std::to_string(maxSize).c_str());
}

void ImageView::setupUi()
{
	noteEdit = new QTextEdit(this);
	noteEdit->setGeometry(960, 300, 180, 150);

	imageScrollArea = new QScrollArea(this);
	imageScrollArea->setGeometry(20, 60, 900, 600);

	imagePanel = new ImagePanel;
	imageScrollArea->setWidget(imagePanel);

	folderButton = new QPushButton(this);
	folderButton->setGeometry(20, 20, 140, 30);
 
	originalModeButton = new QPushButton(this);
	originalModeButton->setGeometry(660, 20, 60, 30);
	originalModeButton->setText("Original");

	processedModeButton = new QPushButton(this);
	processedModeButton->setGeometry(730, 20, 60, 30);
	processedModeButton->setText("Processed");

	editableModeButton = new QPushButton(this);
	editableModeButton->setGeometry(800, 20, 60, 30);
	editableModeButton->setText("Editable");

	zoomOutButton = new QPushButton(this);
	zoomOutButton->setGeometry(890, 20, 30, 30);
	zoomOutButton->setText("-");

	zoomValueLabel = new QLabel(this);
	zoomValueLabel->setGeometry(920, 20, 40, 30);

	zoomInButton = new QPushButton(this);
	zoomInButton->setGeometry(960, 20, 30, 30);
	zoomInButton->setText("+");

	saveButton = new QPushButton(this);
	saveButton->setGeometry(960, 500, 120, 30);
	saveButton->setText("Save Image");

	// Circularity setup
	cirSliderLabel = new QLabel(this);
	cirSliderLabel->setGeometry(960, 60, 160, 20);
	cirSliderLabel->setText("Circularity");
	
	minCirValueLabel = new QLabel(this);
	minCirValueLabel->setGeometry(1120, 90, 120, 20);
	minCirSlider = new QSlider(Qt::Horizontal, this);
	minCirSlider->setGeometry(960, 90, 160, 20);
	minCirSlider->setRange(0, 100);
	
	maxCirValueLabel = new QLabel(this);
	maxCirValueLabel->setGeometry(1120, 120, 120, 20);
	maxCirSlider = new QSlider(Qt::Horizontal, this);
	maxCirSlider->setGeometry(960, 120, 160, 20);
	maxCirSlider->setRange(0, 100);

	// Size setup
	sizeSliderLabel = new QLabel(this);
	sizeSliderLabel->setGeometry(960, 160, 160, 20);
	sizeSliderLabel->setText("Size");

	minSizeValueLabel = new QLabel(this);
	minSizeValueLabel->setGeometry(1120, 190, 120, 20);
	minSizeSlider = new QSlider(Qt::Horizontal, this);
	minSizeSlider->setGeometry(960, 190, 160, 20);

	maxSizeValueLabel = new QLabel(this);
	maxSizeValueLabel->setGeometry(1120, 220, 120, 20);
	maxSizeSlider = new QSlider(Qt::Horizontal, this);
	maxSizeSlider->setGeometry(960, 220, 160, 20);

	processButton = new QPushButton(this);
	processButton->setGeometry(960, 250, 60, 30);
	processButton->setText("Process");


}

void ImageView::setupSignalAndSlot()
{

	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveImage()));
	connect(folderButton, SIGNAL(clicked()), this, SLOT(backToFolder()));
	connect(originalModeButton, SIGNAL(clicked()), this, SLOT(enterOriginalMode()));
	connect(processedModeButton, SIGNAL(clicked()), this, SLOT(enterProcessedMode()));
	connect(editableModeButton, SIGNAL(clicked()), this, SLOT(enterEditableMode()));
	connect(imagePanel, SIGNAL(leftDoubleClicked()), this, SLOT(leftClickOnPanel()));
	connect(imagePanel, SIGNAL(rightDoubleClicked()), this, SLOT(rightClickOnPanel()));
	connect(processButton, SIGNAL(clicked()), this, SLOT(processImage()));

	connect(minCirSlider, SIGNAL(valueChanged(int)), this, SLOT(setSliderValueLabels()));
	connect(maxCirSlider, SIGNAL(valueChanged(int)), this, SLOT(setSliderValueLabels()));
	connect(minSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setSliderValueLabels()));
	connect(maxSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setSliderValueLabels()));
	
	connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));
	connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

	/*connect(imagePanel, SIGNAL(doubleClicked()), this, SLOT(clickOnPanel()));

	connect(&homeButton, SIGNAL(clicked()), this, SLOT(backToHome()));
	connect(&projectButton, SIGNAL(clicked()), this, SLOT(backToProject()));
	connect(&folderButton, SIGNAL(clicked()), this, SLOT(backToFolder()));

	connect(&originalModeButton, SIGNAL(clicked()), this, SLOT(enterOriginalMode()));
	connect(&processedModeButton, SIGNAL(clicked()), this, SLOT(enterProcessedMode()));
	connect(&editableModeButton, SIGNAL(clicked()), this, SLOT(enterEditableMode()));
*/
	/*connect(&processButton, SIGNAL(clicked()), this, SLOT(processImage()));
	connect(&circularitySlider, SIGNAL(valueChanged()), this, SLOT(processImage()));
	connect(&sizeSlider, SIGNAL(valueChanged()), this, SLOT(processImage()));*/
	// change value for current image
	//connect(&circularitySlider, SIGNAL(valueChanged()), this, SLOT(mainWindow.getDataImageList()));
}

void ImageView::zoomIn()
{
	qDebug() << "Zoom in ";
	currentDataImage->zoom(1);
	updateView();
}

void ImageView::zoomOut()
{
	qDebug() << "Zoom out ";
	currentDataImage->zoom(2);
	updateView();
}

void ImageView::rightClickOnPanel()
{
	currentMode->doubleRightClick(this);
}

void ImageView::leftClickOnPanel()
{
	currentMode->doubleLeftClick(this);
}

void ImageView::saveImage()
{
	mainWindow.getCurrentDataImage()->setNote( noteEdit->toPlainText().toStdString() );
	mainWindow.getCurrentDataImage()->save();
}

void ImageView::processImage()
{
	saveSliderValue();

	FatOption opts;
	opts.minCir = minCirSlider->value() / 100.0;
	opts.maxCir = maxCirSlider->value() / 100.0;
	opts.minSize = minSizeSlider->value();
	opts.maxSize = maxSizeSlider->value();

	qDebug() << "min size:" << opts.minSize;
	qDebug() << "max size:" << opts.maxSize;

	mainWindow.getCurrentDataImage()->processFat( opts );
	updateView();
}

void ImageView::clickOnImage(int i)
{
	qDebug() << "IMageview click on image";


	if (i == 1 && mainWindow.getCurrentDataImage()->clickOnFat(imagePanel->x, imagePanel->y))
		updateView();

	if (i == 2 && mainWindow.getCurrentDataImage()->clickOnFibrosis(imagePanel->x, imagePanel->y))
		updateView();
	
}


void ImageView::enterOriginalMode()
{
	currentMode->enterOriginalMode( this );
}

void ImageView::enterProcessedMode()
{
	currentMode->enterProcessedMode( this );
}

void ImageView::enterEditableMode()
{
	currentMode->enterEditableMode( this );
}


void ImageView::backToHome()
{
	saveSliderValue();
	mainWindow.changeView(MainWindow::HOME_VIEW);
}

void ImageView::backToProject()
{
	saveSliderValue();
	mainWindow.changeView(MainWindow::PROJECT_VIEW);
}

void ImageView::backToFolder()
{
	saveSliderValue();
	mainWindow.changeView(MainWindow::FOLDER_VIEW);
}

void ImageView::setMode(int mode)
{
	currentMode = modeList[mode];
	updateView();
}