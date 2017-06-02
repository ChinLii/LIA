#ifndef IMAGEHELPER_H
#define IMAGEHELPER_H

#include <qimage.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

class ImageHelper
{
public:
	static const int THRESHOLD = 220;

	ImageHelper();
	~ImageHelper();

	static double findZoomSize(int originalSize, int zoomValue);
	static QImage mat2QImage(const cv::Mat& mat);
	static void convertToGreyScale( const cv::Mat& input, cv::Mat& result );
	static void lowPassFilter(cv::Mat& input, cv::Mat& result);
	static void fibLowPassFilter(cv::Mat& input, cv::Mat& result);
	static void binarize(cv::Mat& input, cv::Mat& result);
	static void morphOpening(cv::Mat& input, cv::Mat& blobImg);

private:
	
};

#endif // IMAGEHELPER_H
