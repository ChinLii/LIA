#ifndef FATPROCESSOR_H
#define FATPROCESSOR_H
#include <iostream>
#include <vector>
#include <fstream>
#include "blobfeatures.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <string>
#include "filemanager.h"
#include "fatoption.h"


const int THRESHOLD = 220;
const int NON_FAT_LABEL = 0;
const int FAT_LABEL = 1;

//area color
const uchar FAT_COLOR = 0;
const uchar NON_FAT_COLOR = 128;

typedef std::vector<std::vector<cv::Point>> SetOfContours;

class FatProcessor
{
public:
	
	static void train( const std::string& path);
	static double minArea;
	static double maxArea;
	static double minCircularity;
	static double maxCircularity;
	static double minGrayLevel;
	static double maxGrayLevel;
	static CvSVM trainedSvm;

	//float maxArea, minArea, maxCir, minCir, maxGray, minGray;
	FatProcessor();
	~FatProcessor();

	static void loadTest(std::string path);
	static void convertedImage( cv::Mat& input, cv::Mat& blobImg );

	static void detectBackground(SetOfContours& contours, std::vector<BlobFeatures>& blobFts, cv::Mat& blobImg);
	static void findContoursFromGroundImage(const cv::Mat& blobImg, SetOfContours& contours, std::vector<int>& labels);
	static void detectColor(const cv::Mat& img, const int color, cv::Mat& out);
	static void calculateTrainingFeatures(const cv::Mat& trainGT, const cv::Mat& input, std::vector<BlobFeatures>& blobFts, std::vector<int>& labels);
	static void fatFindContours(const cv::Mat& blobImg, SetOfContours& contours);
	static void findAreaAndCircularity(const SetOfContours& contours, std::vector<BlobFeatures>& blobFeat);
	static void findAverageGreyLevel(const cv::Mat& input, const cv::Mat& blobImg, const SetOfContours& contours, std::vector<BlobFeatures>& blobFts);
	static void convertSample2FtVector(const std::vector<BlobFeatures>& blobFts, const std::vector<int>& labels, cv::Mat& ftVector, cv::Mat& labelVector);
	static float normalizeData(float x, float min, float max);
	static void trainSVM(const cv::Mat ftVector, const cv::Mat& labelsVector );
	static void removeNonFatBlob(const cv::Mat& blobImg, const cv::vector<BlobFeatures>& blobFts, const SetOfContours& contours, cv::Mat& output);
	static void removeNonFatBlob(const cv::Mat& blobImg, const cv::vector<BlobFeatures>& blobFts, const SetOfContours& contours, cv::Mat& output, FatOption opts);


private:

	
};

#endif // FATPROCESSOR_H
