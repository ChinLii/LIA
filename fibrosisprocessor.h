#ifndef FIBROSISPROCESSOR_H
#define FIBROSISPROCESSOR_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include "filemanager.h"
#include "fibrosisfeatures.h"
#include "fibrosisdata.h"

typedef std::vector<std::vector<cv::Point>> SetOfContours;

class FibrosisProcessor
{
public:
	static CvSVM trainedSvm;

	FibrosisProcessor();
	~FibrosisProcessor();
	//static int binSize;

	static void detectBackground(const cv::Mat& inputImage, cv::Mat& outputImage);
	static void produceModelImage(cv::Mat& input, cv::Mat& output);
	static void loadTest(std::string path);
	static void enhance(const cv::Mat& inputImage, cv::Mat& outputImage );
	static void train(const std::string& path);
	static void stub_train(cv::Mat in, cv::Mat i, std::vector<FibrosisFeatures>& blobFts, std::vector<int>& labels);
	static int translate(uchar intensity) { return  intensity / 8; }
	static void trainSVM(const cv::Mat& ftVector, const cv::Mat& labelsVector );
	static void test_enhance(std::string path);
	static void convertSample2FtVector(const std::vector<FibrosisFeatures>& fibFts, const std::vector<int>& labels, cv::Mat& fibVector, cv::Mat& labelVector);
	static void stub_predict(cv::Mat& input, cv::Mat& output);


private:
	
};

#endif // FIBROSISPROCESSOR_H
