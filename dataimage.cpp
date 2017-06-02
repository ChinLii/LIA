#include "dataimage.h"
#include <qdebug.h>
#include "imagehelper.h"
#include "folder.h"

DataImage::DataImage(std::string n, std::string p, int t ):
	hasProcessed(false),
	name(n), path(p), type(t), currentZoom(4)
{

	if (t == Folder::FAT_TYPE || t == Folder::BOTH_TYPE )
		fatData = new FatData;

	if (t == Folder::FIBROSIS_TYPE || t == Folder::BOTH_TYPE )
		fibrosisData = new FibrosisData;

	originalImage = cv::imread(path + "/" + name, CV_LOAD_IMAGE_COLOR);

	//cv::cvtColor(originalImage, originalImage, CV_BGR2RGB);

}  
DataImage::~DataImage()
{
}

void DataImage::destroy()
{
	std::string deletePath = path + "/" + name;

	// delete the image file
	FileManager::deleteFile( deletePath );

	// delete the data file for the image
	FileManager::deleteFile( deletePath + ".data" );
}

void DataImage::init()
{
	if (!hasProcessed)
	{
		process();
		hasProcessed = true;


		if (type == Folder::FAT_TYPE || type == Folder::BOTH_TYPE)
		{

			qDebug() << "SET SLIDER";
			fatData->minCirSliderValue = 0;
			fatData->maxCirSliderValue = 100;

			fatData->minSizeSliderValue = fatData->minBlobSize;
			fatData->maxSizeSliderValue = fatData->maxBlobSize;

		}

		if (type == Folder::FIBROSIS_TYPE || type == Folder::BOTH_TYPE)
		{

		}

	}


}

void DataImage::process()
{
	if (type == Folder::FAT_TYPE || type == Folder::BOTH_TYPE)
	{
		qDebug() << "Fat Process";
		fatData->process(originalImage);
	}

	if (type == Folder::FIBROSIS_TYPE || type == Folder::BOTH_TYPE)
	{
		qDebug() << "Fibrosis Process";
		fibrosisData->process(originalImage);
	}
}

int DataImage::getFatSliderValue(int feature, int minOrMax)
{
	// return circularity value
	if (feature == 1)
	{
		if (minOrMax == 1)
			return fatData->minCirSliderValue;
		return fatData->maxCirSliderValue;
	}
	// return size value
	else
	{
		if (minOrMax == 1)
			return fatData->minSizeSliderValue;
		return fatData->maxSizeSliderValue;
	}
}

void DataImage::setFatSliderValue(int feature, int minOrMax, int value)
{
	// set circularity value
	if (feature == 1)
	{
		if (minOrMax == 1)
			fatData->minCirSliderValue = value;
		else
			fatData->maxCirSliderValue = value;
	}
	// set size value
	else
	{
		if (minOrMax == 1)
			fatData->minSizeSliderValue = value;
		else
			fatData->maxSizeSliderValue = value;
	}
}

void DataImage::save()
{
	std::string fullPath = path + "/" + name + ".data";
	std::string text;

	text += name + "\n";
	text += note;

	FileManager::createFile(fullPath, text);
}

void DataImage::setNote(std::string n)
{
	note = n;
}

int DataImage::getMinBlobSize()
{
	return fatData->minBlobSize;
}

int DataImage::getMaxBlobSize()
{
	return fatData->maxBlobSize;
}


void DataImage::processFat()
{
	qDebug() << "PROCESS IMAGE";
	fatData->process(originalImage);
}

cv::Mat DataImage::getModelImage()
{
	return fatData->modelImage;
}

void DataImage::processFat(FatOption opts)
{
	qDebug() << "PROCESS IMAGE WITH OPTIONS";
	fatData->process(originalImage, opts);

}

void DataImage::processFibrosis()
{
	qDebug() << "PROCESS FIBROSIS";
	fibrosisData->process(originalImage);
}

void DataImage::highlightFat()
{
	//pFatData->highlightFat(originalImage);

	
}

std::string DataImage::getPercentage( int type )
{
	if ( type == 1 )
		return "Processed %";

	return "Editable %";
}

double DataImage::getFatPercentage(int type) {
	return fatData->getPercentage(type);
}

void DataImage::setCircularity(double cir)
{
	circularity = cir;
}

void DataImage::zoom(int n)
{
	if (n == 1)
	{
		if ( currentZoom < 8 )
			currentZoom += 1;
	}
	else if ( n == 2 )
	{
		if (currentZoom > 1)
			currentZoom -= 1;
	}
}

std::string DataImage::getCurrentZoom()
{
	return std::to_string(currentZoom * 25) += "%";
}

QImage DataImage::getQImage(int mode)
{


	int displayHeight = ImageHelper::findZoomSize(originalImage.size().height, currentZoom * 25 );
	int displayWidth = ImageHelper::findZoomSize(originalImage.size().width, currentZoom * 25 );


	if (mode == ImageView::ORIGINAL_MODE)
	{
		qDebug() << displayHeight;
		qDebug() << displayWidth;
		return ImageHelper::mat2QImage(originalImage).scaled(displayWidth, displayHeight);
	}

	else if (mode == ImageView::PROCESSED_MODE)
	{
		cv::Mat outImage = originalImage.clone();

		if (type == Folder::FAT_TYPE || type == Folder::BOTH_TYPE)
			fatData->highlight(originalImage, fatData->modelImage, outImage);

		if (type == Folder::FIBROSIS_TYPE || type == Folder::BOTH_TYPE)
			fibrosisData->highlight(originalImage, fibrosisData->modelImage, outImage);

		return ImageHelper::mat2QImage(outImage);
	}

	else if (mode == ImageView::EDITABLE_MODE)
	{
		cv::Mat outImage = originalImage.clone();
		
		if (type == Folder::FAT_TYPE || type == Folder::BOTH_TYPE)
			fatData->highlight(originalImage, fatData->editModelImage, outImage);

		if (type == Folder::FIBROSIS_TYPE || type == Folder::BOTH_TYPE)
			fibrosisData->highlight(originalImage, fibrosisData->editModelImage, outImage);

		return ImageHelper::mat2QImage(outImage);
	}

	return ImageHelper::mat2QImage(originalImage).scaled(displayHeight, displayWidth);
}

bool DataImage::clickOnFibrosis(int x, int y)
{
	if (type == Folder::FAT_TYPE)
		return false;

	if (fibrosisData->editModelImage.at<uchar>(y, x) == FibrosisData::FIBROSIS_COLOR )
	{
		int numPixels = cv::floodFill(fibrosisData->editModelImage, cv::Point(x, y), FibrosisData::NON_FIBROSIS_COLOR);

		//fatData->eFatPixel -= numPixels;
		//fatData->eNonfatPixel += numPixels;
		//fatData->recomputePercentage();

		return true;
	}

	if (fibrosisData->editModelImage.at<uchar>(y, x) == FibrosisData::NON_FIBROSIS_COLOR )
	{
		int numPixels = cv::floodFill(fibrosisData->editModelImage, cv::Point(x, y), FibrosisData::FIBROSIS_COLOR);

		//fatData->eFatPixel += numPixels;
		//fatData->eNonfatPixel -= numPixels;
		//fatData->recomputePercentage();

		return true;
	}

	return false;
}

bool DataImage::clickOnFat(int x, int y)
{

	if (type == Folder::FIBROSIS_TYPE)
		return false;

	if (fatData->editModelImage.at<uchar>(y,x) == FatData::FAT_COLOR_CODE)
	{
		int numPixels = cv::floodFill(fatData->editModelImage, cv::Point(x, y), FatData::NONFAT_COLOR_CODE);

		fatData->eFatPixel -= numPixels;
		fatData->eNonfatPixel += numPixels;
		fatData->recomputePercentage();

		return true;
	}
	
	if (fatData->editModelImage.at<uchar>(y,x) == FatData::NONFAT_COLOR_CODE)
	{
		int numPixels = cv::floodFill(fatData->editModelImage, cv::Point(x, y), FatData::FAT_COLOR_CODE);

		fatData->eFatPixel += numPixels;
		fatData->eNonfatPixel -= numPixels;
		fatData->recomputePercentage();

		return true;
	}

	return false;
}