#ifndef DATAIMAGE_H
#define DATAIMAGE_H

#include <string>
#include <qimage.h>
#include "fatdata.h"
#include "fibrosisdata.h"
#include "fatoption.h"
#include "imageview.h"


class DataImage
{
public:
	DataImage( std::string name, std::string path, int type );
	~DataImage();
	void destroy();


	std::string getName(){ return name; }
	std::string getPath(){ return path; }
	std::string getNote(){ return note; }
	void zoom(int n);

	int getType(){ return type; }
	QImage getQImage(int mode);
	cv::Mat getOriginalImage(){ return originalImage; }
	double getFatPercentage(int type);
	void setCircularity(double cir);
	
	std::string getPercentage(int type);
	void process();
	void processFibrosis();
	void processFat();
	void processFat(FatOption opts);
	void init();
	void save();
	void setNote(std::string n);
	std::string getCurrentZoom();

	bool clickOnFat(int x, int y);
	bool clickOnFibrosis(int x, int y);

	int getMinBlobSize();
	int getMaxBlobSize();
	int getFatSliderValue(int feature, int minOrMax );
	void setFatSliderValue(int feature, int minOrMax, int value);
	cv::Mat getModelImage();
private:
	bool hasProcessed;

	FatData* fatData;
	FibrosisData* fibrosisData;
	std::string name;
	std::string path;
	std::string note;
	int type;
	int currentZoom;

	cv::Mat originalImage;
	double circularity = 0;
	void highlightFat();


	
	
};

#endif // DATAIMAGE_H
