#include "fatdata.h"
#include "dataimage.h"
#include <qdebug.h>

FatData::FatData()
{

}

FatData::~FatData()
{

}

double FatData::getPercentage(int type)
{
	if (type == 1)
		return processedPercentage;
	
	if (type == 2)
		return editablePercentage;

	return -1;
}

void FatData::recomputePercentage()
{
	editablePercentage = 100.0 * eFatPixel / (eTissuePixel + eNonfatPixel);
}

void FatData::computePercentage(int type){
		
	if (type == 1)
	{
		pBgPixel = pTissuePixel = pFatPixel = pNonfatPixel = 0;

		for (int i = 0; i < modelImage.rows; i++){
			for (int j = 0; j < modelImage.cols; j++){
				if (modelImage.at<uchar>(i, j) == BG_COLOR_CODE) {
					pBgPixel++;
				}
				else if (modelImage.at<uchar>(i, j) == TISSUE_COLOR_CODE) {
					pTissuePixel++;
				}
				else if (modelImage.at<uchar>(i, j) == FAT_COLOR_CODE) {
					pFatPixel++;
				}
				else { //if ( imgData->modelImg.at<uchar>(i, j) == NONFAT_COLOR_CODE ) {
					pNonfatPixel++;
				}
			}
		}
		processedPercentage = 100.0 * pFatPixel / (pTissuePixel + pNonfatPixel);
	}
	else if (type == 2)
	{

		eBgPixel = eTissuePixel = eFatPixel = eNonfatPixel = 0;

		for (int i = 0; i < editModelImage.rows; i++){
			for (int j = 0; j < editModelImage.cols; j++){
				if (editModelImage.at<uchar>(i, j) == BG_COLOR_CODE) {
					eBgPixel++;
				}
				else if (editModelImage.at<uchar>(i, j) == TISSUE_COLOR_CODE) {
					eTissuePixel++;
				}
				else if (editModelImage.at<uchar>(i, j) == FAT_COLOR_CODE) {
					eFatPixel++;
				}
				else { //if ( imgData->modelImg.at<uchar>(i, j) == NONFAT_COLOR_CODE ) {
					eNonfatPixel++;
				}
			}
		}
		editablePercentage = 100.0 * eFatPixel / (eTissuePixel + eNonfatPixel);
	}
	
}

void FatData::process( const cv::Mat& originalImage )
{

	modelImage = cv::Mat(originalImage.rows, originalImage.cols, CV_8UC1);

	cv::Mat greyImage;
	ImageHelper::convertToGreyScale( originalImage, greyImage);

	cv::Mat blobImage(greyImage.rows, greyImage.cols, CV_8UC1);

	// part 1 : low pass, binarize, morph openning
	FatProcessor::convertedImage(greyImage, blobImage);

	cv::Mat cloneBlob = blobImage.clone();

	FatProcessor::fatFindContours(cloneBlob, contourList);


	cv::Mat contourImage(blobImage.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(contourImage, contourList, -1, cv::Scalar(0), 1);

	std::vector<BlobFeatures> blobFeatures;
	FatProcessor::findAreaAndCircularity(contourList, blobFeatures);
	FatProcessor::findAverageGreyLevel(greyImage, blobImage, contourList, blobFeatures);

	FatProcessor::removeNonFatBlob(blobImage, blobFeatures, contourList, modelImage );
	FatProcessor::detectBackground(contourList, blobFeatures, modelImage);

	findMinMaxArea(blobFeatures);

	computePercentage(1);
}

void FatData::findMinMaxArea( std::vector<BlobFeatures> blobFeatures )
{
	if (blobFeatures.size() > 0)
	{
		minBlobSize = blobFeatures[0].getArea();
		maxBlobSize = blobFeatures[0].getArea();
	}

	for (int i = 0; i < blobFeatures.size(); i++)
	{
		if ( blobFeatures[i].getType() == 1 )
			continue;

		if (minBlobSize > blobFeatures[i].getArea())
			minBlobSize = blobFeatures[i].getArea();

		if (maxBlobSize < blobFeatures[i].getArea())
			maxBlobSize = blobFeatures[i].getArea();
	}
}

void FatData::reProcess(const cv::Mat& originalImage, FatOption opt)
{
		//FatProcessor::removeNonFatBlob(blobImage, blobFeatures, contourList, editModelImage, opts);
}

void FatData::process(const cv::Mat& originalImage, FatOption opts)
{
	editModelImage = cv::Mat(originalImage.rows, originalImage.cols, CV_8UC1);

	cv::Mat greyImage;
	ImageHelper::convertToGreyScale(originalImage, greyImage);

	cv::Mat blobImage(greyImage.rows, greyImage.cols, CV_8UC1);

	// part 1 : low pass, binarize, morph openning
	FatProcessor::convertedImage(greyImage, blobImage);

	
	cv::Mat cloneBlob = blobImage.clone();

	FatProcessor::fatFindContours(cloneBlob, contourList);

	cv::Mat contourImage(blobImage.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(contourImage, contourList, -1, cv::Scalar(0), 1);

	std::vector<BlobFeatures> blobFeatures;
	FatProcessor::findAreaAndCircularity(contourList, blobFeatures);
	FatProcessor::findAverageGreyLevel(greyImage, blobImage, contourList, blobFeatures);
	
	FatProcessor::removeNonFatBlob(blobImage, blobFeatures, contourList, editModelImage, opts);
	FatProcessor::detectBackground(contourList, blobFeatures, editModelImage);

	computePercentage(2);

}

void FatData::highlight(const cv::Mat& originalImage, const cv::Mat& modelImage, cv::Mat& outputImage)
{
	for (int i = 0; i < modelImage.rows; i++)
	{
		for (int j = 0; j < modelImage.cols; j++)

			if (modelImage.at<uchar>(i, j) == FAT_COLOR_CODE) {	//highlight fat
			outputImage.at<cv::Vec3b>(i, j)[0] = originalImage.at<cv::Vec3b>(i, j)[0] / 2;			//R  *because orgImg and displayImg is RGB, not BGR
			outputImage.at<cv::Vec3b>(i, j)[1] = (originalImage.at<cv::Vec3b>(i, j)[1] + 255) / 2;	//G
			outputImage.at<cv::Vec3b>(i, j)[2] = originalImage.at<cv::Vec3b>(i, j)[2] / 2;			//B


			}
			else if (modelImage.at<uchar>(i, j) == BG_COLOR_CODE) { //set background color
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

//void FatData::highlightFat(cv::Mat& originalImage)
//{
//
//	for (int i = 0; i < modelImage.rows; i++)
//	{
//		for (int j = 0; j < modelImage.cols; j++)
//
//			if (modelImage.at<uchar>(i, j) == FAT_COLOR_CODE) {	//highlight fat
//			displayImage.at<cv::Vec3b>(i, j)[0] = originalImage.at<cv::Vec3b>(i, j)[0] / 2;			//R  *because orgImg and displayImg is RGB, not BGR
//			displayImage.at<cv::Vec3b>(i, j)[1] = (originalImage.at<cv::Vec3b>(i, j)[1] + 255) / 2;	//G
//			displayImage.at<cv::Vec3b>(i, j)[2] = originalImage.at<cv::Vec3b>(i, j)[2] / 2;			//B
//
//
//			}
//			else if (modelImage.at<uchar>(i, j) == BG_COLOR_CODE) { //set background color
//				displayImage.at<cv::Vec3b>(i, j)[0] = 128;	//R *because displayImg is RGB, not BGR
//				displayImage.at<cv::Vec3b>(i, j)[1] = 128;	//G
//				displayImage.at<cv::Vec3b>(i, j)[2] = 128;	//B
//			}
//			else { //non-fat or tissue
//				displayImage.at<cv::Vec3b>(i, j)[0] = originalImage.at<cv::Vec3b>(i, j)[0];	//R *because orgImg and displayImg is RGB, not BGR
//				displayImage.at<cv::Vec3b>(i, j)[1] = originalImage.at<cv::Vec3b>(i, j)[1];	//G
//				displayImage.at<cv::Vec3b>(i, j)[2] = originalImage.at<cv::Vec3b>(i, j)[2];	//B
//			}
//	}
//
//}