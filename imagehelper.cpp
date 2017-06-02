#include "imagehelper.h"
#include <qdebug.h>

ImageHelper::ImageHelper()
{

}

ImageHelper::~ImageHelper()
{


}

double ImageHelper::findZoomSize(int originalSize, int zoomValue)
{
	return (zoomValue / 100.0) * originalSize;
}

QImage ImageHelper::mat2QImage(const cv::Mat& mat)
{
	switch (mat.type())
	{
		// 8-bit, 4 channel
	case CV_8UC4:
	{
		QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);

		return image;
	}

		// 8-bit, 3 channel
	case CV_8UC3:
	{
		QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

		return image.rgbSwapped();
	}

		// 8-bit, 1 channel
	case CV_8UC1:
	{
		static QVector<QRgb>  sColorTable;

		// only create our color table once
		if (sColorTable.isEmpty())
		{
			for (int i = 0; i < 256; ++i)
				sColorTable.push_back(qRgb(i, i, i));
		}

		QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);

		image.setColorTable(sColorTable);

		return image;
	}

	default:
		qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << mat.type();
		break;
	}

	return QImage();
}

void ImageHelper::convertToGreyScale( const cv::Mat& input, cv::Mat& result)
{
	cv::cvtColor(input, result, CV_BGR2GRAY);
}

void ImageHelper::lowPassFilter(cv::Mat& input, cv::Mat& result)
{
	cv::GaussianBlur(input, result, cv::Size(7, 7), 1.5);
}

void ImageHelper::fibLowPassFilter( cv::Mat& input, cv::Mat& result ) 
{
	cv::boxFilter(input, result, -1, cv::Size(7, 7));
	cv::GaussianBlur(input, result, cv::Size(3, 3), 0);
	cv::addWeighted(input, 2.5, result, -0.5, 0, result );
}

void ImageHelper::binarize( cv::Mat& input, cv::Mat& result)
{
	cv::threshold(input, result, THRESHOLD, 255, cv::THRESH_BINARY);
}
void ImageHelper::morphOpening(cv::Mat& input, cv::Mat& blobImg)
{
	cv::Mat element = cv::getStructuringElement( cv::MORPH_OPEN, cv::Size(9, 9));
	cv::morphologyEx(input, blobImg, cv::MORPH_OPEN, element);
}