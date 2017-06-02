#ifndef FATDATA_H
#define FATDATA_H

#include <string>
#include <vector>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "fatprocessor.h"
#include "imagehelper.h"
#include "fatoption.h"

class DataImage;
typedef std::vector<std::vector<cv::Point>> SetOfContours;

class FatData
{

	friend class DataImage;

public:
	static const uchar TISSUE_COLOR_CODE = 0;
	static const uchar BG_COLOR_CODE = 128;
	static const uchar NONFAT_COLOR_CODE = 200;
	static const uchar FAT_COLOR_CODE = 255;
	FatData();
	~FatData();

	void reProcess(const cv::Mat& originalImage, FatOption opt);

	void findMinMaxArea(std::vector<BlobFeatures> blobFeatures);
	void process( const cv::Mat& img );
	void process(const cv::Mat& img, FatOption opts);
	void computePercentage(int type);
	void recomputePercentage();
	double getPercentage(int type);

	//void highlightFat(cv::Mat& originalImage);
	//void highlightFat(cv::Mat& modelImage, cv::Mat& outputImage);
	//void highlightFat(const cv::Mat& originalImage, const cv::Mat& modelImage, cv::Mat& outputImage);
	void highlight(const cv::Mat& originalImage, const cv::Mat& modelImage, cv::Mat& outputImage);
	
	
private:
	// pixel counts for processed image
	double pTissuePixel, pFatPixel, pNonfatPixel, pBgPixel;

	// pixel counts for editable image
	double eTissuePixel, eFatPixel, eNonfatPixel, eBgPixel;

	double processedPercentage;
	double editablePercentage;
	cv::Mat* originalImage;
	cv::Mat modelImage;
	cv::Mat editModelImage;

	SetOfContours contourList;
	int minBlobSize;
	int maxBlobSize;

	int minCirSliderValue;
	int maxCirSliderValue;
	int minSizeSliderValue;
	int maxSizeSliderValue;

};

#endif // FATDATA_H
