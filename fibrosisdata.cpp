#include "fibrosisdata.h"

FibrosisData::FibrosisData()
{

}

FibrosisData::~FibrosisData()
{

}

void FibrosisData::highlight(const cv::Mat& originalImage, const cv::Mat& modelImage, cv::Mat& outputImage)
{
	for (int i = 0; i < modelImage.rows; i++)
	{
		for (int j = 0; j < modelImage.cols; j++)

			if (modelImage.at<uchar>(i, j) == FIBROSIS_COLOR) {	//highlight fibrosis
			outputImage.at<cv::Vec3b>(i, j)[0] = originalImage.at<cv::Vec3b>(i, j)[0] / 2;			//R  *because orgImg and displayImg is RGB, not BGR
			outputImage.at<cv::Vec3b>(i, j)[1] = (originalImage.at<cv::Vec3b>(i, j)[1] + 255) / 2;	//G
			outputImage.at<cv::Vec3b>(i, j)[2] = originalImage.at<cv::Vec3b>(i, j)[2] / 2;			//B

			}
			else if (modelImage.at<uchar>(i, j) == BG_COLOR) { //set background color
				outputImage.at<cv::Vec3b>(i, j)[0] = 128;	//R *because displayImg is RGB, not BGR
				outputImage.at<cv::Vec3b>(i, j)[1] = 128;	//G
				outputImage.at<cv::Vec3b>(i, j)[2] = 128;	//B
			}
			else { //non-fat or tissue
				outputImage.at<cv::Vec3b>(i, j)[0] = originalImage.at<cv::Vec3b>(i, j)[0];	//R *because orgImg and displayImg is RGB, not BGR
				outputImage.at<cv::Vec3b>(i, j)[1] = originalImage.at<cv::Vec3b>(i, j)[1];	//G
				outputImage.at<cv::Vec3b>(i, j)[2] = originalImage.at<cv::Vec3b>(i, j)[2];	//B
			}
	}

}




void FibrosisData::process(const cv::Mat& originalImage)
{
	modelImage = cv::Mat(originalImage.rows, originalImage.cols, CV_8UC1);


	cv::Mat enhancedImage;
	FibrosisProcessor::enhance(originalImage, enhancedImage );

	cv::Mat lowPassedImage;
	ImageHelper::fibLowPassFilter(enhancedImage, lowPassedImage);

	FibrosisProcessor::produceModelImage(lowPassedImage, modelImage);

	cv::Mat grayInput;
	cv::cvtColor(originalImage, grayInput, CV_RGB2GRAY);

	cv::Mat binaryImg;
	cv::Mat blurredImg;
	cv::GaussianBlur(grayInput, blurredImg, cv::Size(11, 11), 2.5);
	cv::threshold(blurredImg, binaryImg, 180, 255, cv::THRESH_BINARY);

	SetOfContours contours;
	cv::Mat tempBinaryImg = binaryImg.clone();
	cv::findContours(tempBinaryImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	std::vector<BlobFeatures> blobFeatures;
	FatProcessor::findAreaAndCircularity(contours, blobFeatures);
	FatProcessor::findAverageGreyLevel(grayInput, binaryImg, contours, blobFeatures);
	FatProcessor::detectBackground(contours, blobFeatures, binaryImg);


	for (int i = 0; i < binaryImg.rows; i++)
	{
		for (int j = 0; j < binaryImg.cols; j++)
		{
			if (binaryImg.at<uchar>(i, j) == 128) 
				modelImage.at<uchar>(i, j) = BG_COLOR;
		}
	}

	editModelImage = modelImage.clone();

}
