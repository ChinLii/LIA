#ifndef FIBROSISDATA_H
#define FIBROSISDATA_H

#include <string>
#include <vector>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "fatprocessor.h"
#include "imagehelper.h"
#include "fibrosisprocessor.h"

class DataImage;

class FibrosisData
{
	friend class DataImage;

public:
	static const uchar TISSUE_COLOR= 0;
	static const uchar BG_COLOR = 128;
	static const uchar NON_FIBROSIS_COLOR = 200;
	static const uchar FIBROSIS_COLOR = 255;

	FibrosisData();
	~FibrosisData();

	void process(const cv::Mat& img);
	void highlight(const cv::Mat& originalImage, const cv::Mat& modelImage, cv::Mat& outputImage);

private:
	cv::Mat* originalImage;
	cv::Mat modelImage;
	cv::Mat editModelImage;
	
};

#endif // FIBROSISDATA_H
