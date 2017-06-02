#include "fatprocessor.h"
#include "qdebug.h"
#include "imagehelper.h"

double FatProcessor::minArea = 0;
double FatProcessor::maxArea = 0;
double FatProcessor::minCircularity = 0;
double FatProcessor::maxCircularity = 0;
double FatProcessor::minGrayLevel = 0;
double FatProcessor::maxGrayLevel = 0;
CvSVM FatProcessor::trainedSvm;


FatProcessor::FatProcessor()
{

}

FatProcessor::~FatProcessor()
{

}

void FatProcessor::loadTest(std::string path)
{
	//trainedSvm.load(path.c_str());

	qDebug() << "SVM address" << &trainedSvm;

}

void FatProcessor::convertedImage( cv::Mat& input, cv::Mat& blobImage)
{
	cv::Mat tempImage1, tempImage2;

	//lowpass filter
	ImageHelper::lowPassFilter(input, tempImage1);

	//binarization process threshold 220
	ImageHelper::binarize(tempImage1, tempImage2);

	//Morphological openning
	ImageHelper::morphOpening(tempImage2, blobImage);

}

void FatProcessor::train(const std::string& path)
{
	std::string trainImageName;
	std::string gtImageName;
	cv::Mat trainGt;
	cv::Mat ftVector, labelVector;
	SetOfContours contours;
	std::vector<int> labels;
	std::vector<BlobFeatures> blobFts;

	cv::Mat gtImage;
	cv::Mat originalImage;

	std::vector<std::string> listImageName = FileManager::getListFromFile(path + "/train_image_list.txt" );

	for (int i = 0; i < listImageName.size(); i++)
	{
		trainImageName = listImageName[i] + ".tif";
		gtImageName = "(BG)" + trainImageName;

		//load ground truth and training image
		gtImage = cv::imread(path + "/" + gtImageName, CV_LOAD_IMAGE_GRAYSCALE);
		originalImage = cv::imread(path + "/" + trainImageName, CV_LOAD_IMAGE_COLOR);

		////find contours from ground truth image
		findContoursFromGroundImage(gtImage, contours, labels);
		trainGt = gtImage.clone();

		// calculate features
		calculateTrainingFeatures(trainGt, originalImage, blobFts, labels);
	}
	//convert all sample into feature vector for SVM and train it
	convertSample2FtVector(blobFts, labels, ftVector, labelVector);
	//train not done yet!!!!!
	trainSVM(ftVector, labelVector );
}



void FatProcessor::trainSVM(const cv::Mat ftVector, const cv::Mat& labelsVector )
{
	cv::SVMParams params;
	params.svm_type = CvSVM::C_SVC;
	params.kernel_type = CvSVM::RBF;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 1000, FLT_EPSILON);

	//CvSVM svm;
	// train
	//trainedSvm.train_auto(ftVector, labelsVector, cv::Mat(), cv::Mat(), params);
	trainedSvm.train(ftVector, labelsVector, cv::Mat(), cv::Mat(), params);
	trainedSvm.save("trainAlready");


	qDebug() << "trainedSvm in TrainSVM" << &trainedSvm;
	//KNN 
	//knn.train(ftVector, labelsVector);
}

void FatProcessor::convertSample2FtVector(const std::vector<BlobFeatures>& blobFts, const std::vector<int>& labels, cv::Mat& ftVector, cv::Mat& labelVector)
{
	ftVector = cv::Mat(blobFts.size(), 3, CV_32FC1); // 3 feature
	labelVector = cv::Mat(labels.size(), 1, CV_32FC1);
	
	qDebug() << "BLOB " << blobFts.size();
	qDebug() << "LABEL " << labels.size();

	//find the largest area
	/*double maxTrainedArea = 0.0;
	for (int i = 0; i < blobFts.size(); i++)
	if (blobFts[i].getArea() > maxTrainedArea)
	maxTrainedArea = blobFts[i].getArea();
	cout << "Largest area = " << maxTrainedArea << endl;*/
	//find in normal data
	/*for (int i = 0; i < blobFts.size(); i++){

	ftVector.at<float>(i, 0) = blobFts[i].getArea();
	ftVector.at<float>(i, 1) = blobFts[i].getCircularity();
	ftVector.at<float>(i, 2) = blobFts[i].getAvgGrayLevel();
	labelVector.at<float>(i, 0) = labels[i];

	}*/

	//Normalization DATA with min max 
	float currentArea, currentCir, currentGray;
	float currentlength;
	maxArea = blobFts[0].getArea();
	minArea = blobFts[0].getArea();
	maxCircularity = blobFts[0].getCircularity();
	minCircularity = blobFts[0].getCircularity();
	maxGrayLevel = blobFts[0].getAvgGrayLevel();
	minGrayLevel = blobFts[0].getAvgGrayLevel();
	for (int i = 0; i < blobFts.size(); i++)
	{
		currentArea = blobFts[i].getArea();
		currentCir = blobFts[i].getCircularity();
		currentGray = blobFts[i].getAvgGrayLevel();

		if (maxArea <= currentArea)
			maxArea = currentArea;
		if (minArea > currentArea)
			minArea = currentArea;

		if (maxCircularity <= currentCir)
			maxCircularity = currentCir;
		if (minCircularity > currentCir)
			minCircularity = currentCir;

		if (maxGrayLevel <= currentGray)
			maxGrayLevel = currentGray;
		if (minGrayLevel > currentGray)
			minGrayLevel = currentGray;
	}


	for (int i = 0; i < blobFts.size(); i++){
		ftVector.at<float>(i, 0) = normalizeData(blobFts[i].getArea(), minArea, maxArea);
		ftVector.at<float>(i, 1) = normalizeData(blobFts[i].getCircularity(), minCircularity, maxCircularity);
		ftVector.at<float>(i, 2) = normalizeData(blobFts[i].getAvgGrayLevel(), minGrayLevel, maxGrayLevel);
		labelVector.at<float>(i, 0) = labels[i];

	}

	//Normalization data without min max
	/*float currentArea, currentCir, currentGray;
	float currentlength;
	for (int i = 0; i < blobFts.size(); i++) {
	currentArea = blobFts[i].getArea();
	currentCir = blobFts[i].getCircularity();
	currentGray = blobFts[i].getAvgGrayLevel();
	currentlength = findLenght(currentCir, currentArea, currentGray);

	ftVector.at<float>(i, 0) = currentArea/currentlength;
	ftVector.at<float>(i, 1) = currentCir/currentlength;
	ftVector.at<float>(i, 2) = currentGray/currentlength;
	labelVector.at<float>(i, 0) = labels[i];

	cout << " === " << i << " === " << endl;

	cout << "Area: " << ftVector.at<float>(i, 0) << endl;
	cout << "Cir: " << ftVector.at<float>(i, 1) << endl;
	cout << "Gray: " << ftVector.at<float>(i, 2) << endl;
	cout << "GET CIR :" << blobFts[i].getCircularity() << endl;
	cout << "CURRENT LENGHT :" << currentlength << endl;

	}*/


}

float FatProcessor::normalizeData(float x, float min, float max)
{
	return (x - min) / (max - min);
}

void FatProcessor::findContoursFromGroundImage(const cv::Mat& blobImg, SetOfContours& contours, std::vector<int>& labels)
{
	SetOfContours tempContours;
	std::vector<BlobFeatures> blobFts;
	std::vector<int> tempLabels;
	cv::Mat targetArea(blobImg.rows, blobImg.cols, blobImg.type());

	//clear tempContours and tempLabels
	tempContours.clear();
	tempLabels.clear();

	////find contours of the non-fatblob areas "0"
	detectColor(blobImg, NON_FAT_COLOR, targetArea);
	cv::findContours(targetArea, tempContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	contours.insert(contours.end(), tempContours.begin(), tempContours.end());
	tempLabels = std::vector<int>(tempContours.size(), NON_FAT_LABEL);
	labels.insert(labels.end(), tempLabels.begin(), tempLabels.end());

	//find coutours of the fat area "1"
	detectColor(blobImg, FAT_COLOR, targetArea);
	cv::findContours(targetArea, tempContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cv::Mat contoursImg(targetArea.size(), CV_8U, cv::Scalar(255));
	contours.insert(contours.end(), tempContours.begin(), tempContours.end());
	tempLabels = std::vector<int>(tempContours.size(), FAT_LABEL);
	labels.insert(labels.end(), tempLabels.begin(), tempLabels.end());
}

void FatProcessor::detectColor(const cv::Mat& img, const int color, cv::Mat& out){
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++) {
			int val = (int)img.at<uchar>(i, j);
			if (val == color)
				out.at<uchar>(i, j) = 255;	//white
			else
				out.at<uchar>(i, j) = 0;	//black
			}
}

void FatProcessor::calculateTrainingFeatures(const cv::Mat& trainGT, const cv::Mat& input, std::vector<BlobFeatures>& blobFts, std::vector<int>& labels) {
	std::vector<int> tempLabels;
	cv::Mat fatImg, nonfatImg;

	nonfatImg = trainGT.clone();
	fatImg = trainGT.clone();

	for (int i = 0; i < nonfatImg.rows; ++i)
		for (int j = 0; j < nonfatImg.cols; ++j)
			if (nonfatImg.at<uchar>(i, j) == 128)
				nonfatImg.at<uchar>(i, j) = 255;
			else
				nonfatImg.at<uchar>(i, j) = 0;

	for (int i = 0; i < fatImg.rows; ++i)
		for (int j = 0; j < fatImg.cols; ++j)
			if (fatImg.at<uchar>(i, j) == 0)
				fatImg.at<uchar>(i, j) = 255;
			else
				fatImg.at<uchar>(i, j) = 0;

	cv::waitKey(0);
	//------------------------------------ Non-fat ------------------------------------------------//
	cv::Mat blobImg1 = nonfatImg.clone();
	SetOfContours nonFatContours;
	fatFindContours(blobImg1, nonFatContours);
	std::vector<BlobFeatures> blobFts1;
	findAreaAndCircularity(nonFatContours, blobFts1);
	findAverageGreyLevel(input, nonfatImg, nonFatContours, blobFts1);
	std::vector<int> tempLabels1 = std::vector<int>(blobFts1.size(), NON_FAT_LABEL);

	//----------------------------------- Fat --------------------------------------------------//
	cv::Mat blobImg2 = fatImg.clone();
	SetOfContours fatContours;
	fatFindContours(blobImg2, fatContours);
	std::vector<BlobFeatures> blobFts2;
	findAreaAndCircularity(fatContours, blobFts2);
	findAverageGreyLevel(input, fatImg, fatContours, blobFts2);
	std::vector<int> tempLabels2 = std::vector<int>(blobFts2.size(), FAT_LABEL);

	//---------------------------------------------------------
	blobFts.insert(blobFts.end(), blobFts1.begin(), blobFts1.end());
	blobFts.insert(blobFts.end(), blobFts2.begin(), blobFts2.end());
	//---------------------------------------------------------
}

void FatProcessor::fatFindContours(const cv::Mat& blobImg, SetOfContours& contours)
{
	//find contour
	cv::findContours(blobImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//draw contour image
	cv::Mat contourImg(blobImg.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(contourImg, contours, -1, cv::Scalar(0), 1);
}

void FatProcessor::findAreaAndCircularity(const SetOfContours& contours, std::vector<BlobFeatures>& blobFeat)
{
	qDebug() << "FIND AREA AND CIR" << contours.size();
	double area, perimeter, circularity;
	BlobFeatures ft; // in each of contour will keep in blobFeature vector.
	double max = 0.0, min = 1.0;

	for (int i = 0; i < contours.size(); i++)
	{
		area = cv::contourArea(contours[i], 0);
		perimeter = cv::arcLength(contours[i], 1);
		circularity = (4 * 3.14*area) / (perimeter*perimeter); // calcuale the curcularity. Per each blob
		ft.setArea(area);
		ft.setcircularity(circularity);
		blobFeat.push_back(ft); // keep blob into the list of blobFeat
		/*cout << "area = " << area << endl;
		cout << "circularity = " << circularity << endl;*/
		if (max <= circularity)
			max = circularity;
		else if (min >= circularity)
			min = circularity;

	}

}

void FatProcessor::findAverageGreyLevel(const cv::Mat& input, const  cv::Mat& blobImg, const SetOfContours& contours, std::vector<BlobFeatures>& blobFts)
{

	int fill, count;
	double sum;
	cv::Mat temp;
	temp = blobImg.clone();
	//loop in colums
	for (int n = 0; n < contours.size(); ++n) {
		//cMax is cols maximum
		//cMin is cols minimum
		int cMax = contours[n][0].x;
		int cMin = contours[n][0].x;
		//rMax is rows maximum
		//rMin is rows minimum
		int rMax = contours[n][0].y;
		int rMin = contours[n][0].y;

		for (int i = 1; i < contours[n].size(); ++i) {
			if (cMax <  contours[n][i].x)
				cMax = contours[n][i].x;
			if (cMin > contours[n][i].x)
				cMin = contours[n][i].x;
			if (rMax < contours[n][i].y)
				rMax = contours[n][i].y;
			if (rMin > contours[n][i].y)
				rMin = contours[n][i].y;
		}
		////////////input image//output image//
		fill = floodFill(temp, contours[n][0], 128);

		sum = 0;
		count = 0;
		for (int i = rMin; i < rMax; ++i) {
			for (int j = cMin; j < cMax; ++j)
				if (temp.at<uchar>(i, j) == 128) {
				sum += input.at<uchar>(i, j);
				count++;
				}
		}
		sum = sum / count;
		blobFts[n].setAvgGrayLevel(sum);  // set all element in blobfeture.
		fill = floodFill(temp, contours[n][0], 255);

	}
}

void FatProcessor::removeNonFatBlob(const cv::Mat& blobImg, const cv::vector<BlobFeatures>& blobFts, const SetOfContours& contours, cv::Mat& output)
{
	output = blobImg.clone();
	//create a vector to store features
	cv::Mat a_ftVector(1, 3, CV_32FC1);

	
	//Normalization data with max min

	for (int i = 0; i < blobFts.size(); i++)
	{
		a_ftVector.at<float>(0, 0) = normalizeData(blobFts[i].getArea(), minArea, maxArea);
		a_ftVector.at<float>(0, 1) = normalizeData(blobFts[i].getCircularity(), minCircularity, maxCircularity);
		a_ftVector.at<float>(0, 2) = normalizeData(blobFts[i].getAvgGrayLevel(), minGrayLevel, maxGrayLevel);

		float response = trainedSvm.predict(a_ftVector, 3);

		//qDebug() << "res: " << response;
	/*	cout <<"++++++ RES +++++++ : "<< respones << endl;*/
		if ( response > 0.04 )  
		{
			cv::floodFill(output, contours[i][1], 200);
		}
	}

}

// Remove non fat with options from slider bar
void FatProcessor::removeNonFatBlob(const cv::Mat& blobImg, const cv::vector<BlobFeatures>& blobFts, const SetOfContours& contours, cv::Mat& output, FatOption opts )
{
	output = blobImg.clone();
	//create a vector to store features
	cv::Mat a_ftVector(1, 3, CV_32FC1);

	//Normalization data with max min

	for (int i = 0; i < blobFts.size(); i++)
	{

		//a_ftVector.at<float>(0, 0) = normalizeData(blobFts[i].getArea(), minArea, maxArea);
		//a_ftVector.at<float>(0, 1) = normalizeData(blobFts[i].getCircularity(), minCircularity, maxCircularity);
		//a_ftVector.at<float>(0, 2) = normalizeData(blobFts[i].getAvgGrayLevel(), minGrayLevel, maxGrayLevel);

		//float respones = trainedSvm.predict(a_ftVector, 3);

		if ( !opts.check(blobFts[i].getArea(), blobFts[i].getCircularity()) )
		{
			cv::floodFill(output, contours[i][1], 200  );
		}
	}

}



void FatProcessor::detectBackground(SetOfContours& contours, std::vector<BlobFeatures>& blobFts, cv::Mat& blobImg) {
	//set threshold values
	const int bgAreaTH = 3000;
	const int contourLenTH = 500;
	const int edgePixelTh = 100;
	//set constants for row/column before the last
	const int maxX = blobImg.cols - 2;
	const int maxY = blobImg.rows - 2;



	//looping: check all blobs
	for (int i = 0; i < contours.size(); i++) {

		//get the area and length of each contour
		int area = blobFts[i].getArea();
		int len = contours[i].size();

		//check conditions: large area and long contour
		if ((area > bgAreaTH) || (len > contourLenTH)) {
			int countEdgePixel = 0;
			for (int n = 0; n < contours[i].size(); ++n) {
				int x = contours[i][n].x;
				int y = contours[i][n].y;
				if ((x == 1) || (x == maxX) || (y == 1) || (y == maxY))
					countEdgePixel++;
			}

			//check condition: many contour points located of the boundary of image
			if (countEdgePixel > edgePixelTh) {
				blobFts[i].setType(BlobFeatures::BACKGROUND);
				cv::floodFill(blobImg, contours[i][len / 2], 128);

			}
		}
	}
}




//void FatProcessor::convertedImage(Mat& input, Mat& blobImg){
//	Mat tempimage1, tempimage2;
//	//lowpass filter
//	low_pass_filtering(input, tempimage1);
//	//binarization process threshold 220
//	binarization(tempimage1, tempimage2);
//	//Morphological openning
//	morphological_opening(tempimage2, blobImg);
//}
//void FatProcessor::convert_grey_scale(Mat& input, Mat& result){
//	cvtColor(input, result, CV_BGR2GRAY);
//}
//void FatProcessor::low_pass_filtering(Mat& input, Mat& result){
//	GaussianBlur(input, result, Size(7, 7), 1.5);
//}
//void FatProcessor::binarization(Mat& input, Mat& result){
//	threshold(input, result, THRESHOLD, 255, THRESH_BINARY);
//}
//void FatProcessor::morphological_opening(Mat& input, Mat& blobImg){
//	Mat element = getStructuringElement(MORPH_OPEN, Size(9, 9));
//	morphologyEx(input, blobImg, MORPH_OPEN, element);
//}
//
//void FatProcessor::findContour(const Mat& blobImg, SetOfContours& contours){
//	//find contour
//	cv::findContours(blobImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//	//draw contour image
//	cv::Mat contourImg(blobImg.size(), CV_8U, cv::Scalar(255));
//	cv::drawContours(contourImg, contours, -1, cv::Scalar(0), 1);
//	/*namedWindow("CONTOURS");
//	imshow("CONTOURS", contourImg);*/
//}
//
//void FatProcessor::find_areacircularity(const SetOfContours& contours, vector<BlobFeatures>& blobFeat)
//{
//	double area, perimeter, circularity;
//	BlobFeatures ft; // in each of contour will keep in blobFeature vector.
//	double max = 0.0, min = 1.0;
//
//	for (int i = 0; i < contours.size(); i++)
//	{
//		area = cv::contourArea(contours[i], 0);
//		perimeter = cv::arcLength(contours[i], 1);
//		circularity = (4 * 3.14*area) / (perimeter*perimeter); // calcuale the curcularity. Per each blob
//		ft.setArea(area);
//		ft.setcircularity(circularity);
//		blobFeat.push_back(ft); // keep blob into the list of blobFeat
//		/*cout << "area = " << area << endl;
//		cout << "circularity = " << circularity << endl;*/
//		if (max <= circularity)
//			max = circularity;
//		else if (min >= circularity)
//			min = circularity;
//
//
//	}
//
//
//
//}
//
//void FatProcessor::find_avg_greylevel(const Mat& input, const Mat& blobImg, const SetOfContours& contours, vector<BlobFeatures>& blobFts){
//
//	int fill, count;
//	double sum;
//	Mat temp;
//	temp = blobImg.clone();
//	//loop in colums
//	for (int n = 0; n < contours.size(); ++n) {
//		//cMax is cols maximum
//		//cMin is cols minimum
//		int cMax = contours[n][0].x;
//		int cMin = contours[n][0].x;
//		//rMax is rows maximum
//		//rMin is rows minimum
//		int rMax = contours[n][0].y;
//		int rMin = contours[n][0].y;
//
//		for (int i = 1; i < contours[n].size(); ++i) {
//			if (cMax <  contours[n][i].x)
//				cMax = contours[n][i].x;
//			if (cMin > contours[n][i].x)
//				cMin = contours[n][i].x;
//			if (rMax < contours[n][i].y)
//				rMax = contours[n][i].y;
//			if (rMin > contours[n][i].y)
//				rMin = contours[n][i].y;
//		}
//		////////////input image//output image//
//		fill = floodFill(temp, contours[n][0], 128);
//
//		sum = 0;
//		count = 0;
//		for (int i = rMin; i < rMax; ++i) {
//			for (int j = cMin; j < cMax; ++j)
//				if (temp.at<uchar>(i, j) == 128) {
//				sum += input.at<uchar>(i, j);
//				count++;
//				}
//		}
//		sum = sum / count;
//		blobFts[n].setAvgGrayLevel(sum);  // set all element in blobfeture.
//		fill = floodFill(temp, contours[n][0], 255);
//
//	}
//}
//
//void FatProcessor::detectBG(SetOfContours& contours, vector<BlobFeatures>& blobFts, cv::Mat& blobImg) {
//	//set threshold values
//	const int bgAreaTH = 3000;
//	const int contourLenTH = 500;
//	const int edgePixelTh = 100;
//	//set constants for row/column before the last
//	const int maxX = blobImg.cols - 2;
//	const int maxY = blobImg.rows - 2;
//
//	//looping: check all blobs
//	for (int i = 0; i < contours.size(); i++) {
//
//		//get the area and length of each contour
//		int area = blobFts[i].getArea();
//		int len = contours[i].size();
//
//		//check conditions: large area and long contour
//		if ((area > bgAreaTH) || (len > contourLenTH)) {
//			int countEdgePixel = 0;
//			for (int n = 0; n < contours[i].size(); ++n) {
//				int x = contours[i][n].x;
//				int y = contours[i][n].y;
//				if ((x == 1) || (x == maxX) || (y == 1) || (y == maxY))
//					countEdgePixel++;
//			}
//
//			//check condition: many contour points located of the boundary of image
//			if (countEdgePixel > edgePixelTh) {
//				cv::floodFill(blobImg, contours[i][len / 2], 128);
//				//remove contour and blobft?
//				//???
//
//
//			}
//		}
//	}
//}
//
//void FatProcessor::hough_transform_circle(Mat input, Mat result){
//	GaussianBlur(input, result, Size(5, 5), 1.3);
//	vector<Vec3f> circles;
//	HoughCircles(result, circles, CV_HOUGH_GRADIENT,
//		2,   // accumulator resolution 
//		30,  // minimum distance between two circles
//		100, // Canny high threshold 
//		30, // minimum number of votes 
//		0, 40); // min and max radius
//	vector<cv::Vec3f>::const_iterator itc = circles.begin();
//
//	while (itc != circles.end()) {
//
//		circle(result,
//			cv::Point((*itc)[0], (*itc)[1]), // circle centre
//
//			(*itc)[2], // circle radius
//			cv::Scalar(0, 255, 0), // color 
//			2); // thickness
//
//		++itc;
//	}
//
//}
//
//void FatProcessor::remove_non_fatblob(const Mat& blobImg, const vector<BlobFeatures>& blobFts, const SetOfContours& contours, CvSVM& trainedSVM, Mat& output)
//{
//	output = blobImg.clone();
//	//create a vector to store features
//	Mat a_ftVector(1, 3, CV_32FC1);
//
//	//looping: for all blobs
//	// non normalization data image 
//
//	//for (int i = 0; i < blobFts.size(); i++){
//	//	//set values to feature vector
//	//	a_ftVector.at<float>(0, 0) = blobFts[i].getArea();
//	//	a_ftVector.at<float>(0, 1) = blobFts[i].getCircularity();
//	//	a_ftVector.at<float>(0, 2) = blobFts[i].getAvgGrayLevel();
//	//	//predict by SVM
//	//	float respones = trainedSVM.predict(a_ftVector, 3);
//	//	
//	//	//float respones = knn.find_nearest(a_ftVector, 3);
//	//	//remove noise blobs
//	//	
//	//	
//	//	if (respones >= 0)  //1 == fat but 0 == non fat
//	//		floodFill(output, contours[i][1], 200);
//	//	else{
//	//		/*cout << " === " << i << " ===" << endl;
//	//		cout << "BlobArea#" << ":   " << blobFts[i].getArea() << endl;
//	//		cout << "BlobCircularity#" << ":   " << blobFts[i].getCircularity() << endl;
//	//		cout << "BlobAvgGrayLevel#"  << ":    " << blobFts[i].getAvgGrayLevel() << endl;
//	//		cout << "==============================" << endl<<endl;*/
//	//		/*if (blobFts[i].getCircularity() <= mid){
//	//			floodFill(output, contours[i][1], 200);
//	//		}*/
//	//	}
//	//}
//
//	// Normalization DATA 
//
//	//float currentArea, currentCir, currentGray;
//	//float currentlength;
//	//for (int i = 0; i < blobFts.size(); i++) {
//	//	currentArea = blobFts[i].getArea();
//	//	currentCir = blobFts[i].getCircularity();
//	//	currentGray = blobFts[i].getAvgGrayLevel();
//	//	currentlength = findLenght(currentCir, currentArea, currentGray);
//	//	a_ftVector.at<float>(0, 0) = currentArea / currentlength;
//	//	a_ftVector.at<float>(0, 1) = currentCir / currentlength;
//	//	a_ftVector.at<float>(0, 2) = currentGray / currentlength;
//	//	
//	//	float respones = trainedSVM.predict(a_ftVector, 3);
//	//	//cout <<"++++++ RES +++++++ : "<< respones << endl;
//	//	if (respones > 0 )  //1 == fat but 0 == non fat
//	//		floodFill(output, contours[i][1], 200);
//	//}
//	//
//
//	//Normalization data with max min
//
//	for (int i = 0; i < blobFts.size(); i++)
//	{
//
//		a_ftVector.at<float>(0, 0) = normalizeData(blobFts[i].getArea(), minArea, maxArea);
//		a_ftVector.at<float>(0, 1) = normalizeData(blobFts[i].getCircularity(), minCir, maxCir);
//		a_ftVector.at<float>(0, 2) = normalizeData(blobFts[i].getAvgGrayLevel(), minGray, maxGray);
//
//		float respones = trainedSVM.predict(a_ftVector, 3);
//		//cout <<"++++++ RES +++++++ : "<< respones << endl;
//		if (respones > 0)  //1 == fat but 0 == non fat
//		{
//			floodFill(output, contours[i][1], 200);
//		}
//
//
//		/*if (blobFts[i].getArea() < 2000){
//		cout << "AREA :" << blobFts[i].getArea() << endl;
//		cout << "CIR :" << blobFts[i].getCircularity() << endl;
//		cout << "GRAY :" << blobFts[i].getAvgGrayLevel() << endl;
//		}*/
//	}
//
//
//
//}
//
//void FatProcessor::highlightFat(ImageData* imgData) {
//	for (int i = 0; i < imgData->modelImg.rows; i++)
//		for (int j = 0; j < imgData->modelImg.cols; j++)
//			if (imgData->modelImg.at<uchar>(i, j) == FAT_COLOR_CODE) {	//highlight fat
//		imgData->displayImg.at<cv::Vec3b>(i, j)[0] = imgData->orgImg.at<cv::Vec3b>(i, j)[0] / 2;			//R  *because orgImg and displayImg is RGB, not BGR
//		imgData->displayImg.at<cv::Vec3b>(i, j)[1] = (imgData->orgImg.at<cv::Vec3b>(i, j)[1] + 255) / 2;	//G
//		imgData->displayImg.at<cv::Vec3b>(i, j)[2] = imgData->orgImg.at<cv::Vec3b>(i, j)[2] / 2;			//B
//
//
//			}
//			else if (imgData->modelImg.at<uchar>(i, j) == BG_COLOR_CODE) { //set background color
//				imgData->displayImg.at<cv::Vec3b>(i, j)[0] = 128;	//R *because displayImg is RGB, not BGR
//				imgData->displayImg.at<cv::Vec3b>(i, j)[1] = 128;	//G
//				imgData->displayImg.at<cv::Vec3b>(i, j)[2] = 128;	//B
//			}
//			else { //non-fat or tissue
//				imgData->displayImg.at<cv::Vec3b>(i, j)[0] = imgData->orgImg.at<cv::Vec3b>(i, j)[0];	//R *because orgImg and displayImg is RGB, not BGR
//				imgData->displayImg.at<cv::Vec3b>(i, j)[1] = imgData->orgImg.at<cv::Vec3b>(i, j)[1];	//G
//				imgData->displayImg.at<cv::Vec3b>(i, j)[2] = imgData->orgImg.at<cv::Vec3b>(i, j)[2];	//B
//			}
//}
//
//double FatProcessor::computeFatPercentage(ImageData* imgData){
//	imgData->tissue_pixel = 0;
//	imgData->fat_pixel = 0;
//	imgData->nonfat_pixel = 0;
//	imgData->bg_pixel = 0;
//
//	for (int i = 0; i < imgData->modelImg.rows; i++)
//		for (int j = 0; j < imgData->modelImg.cols; j++)
//			if (imgData->modelImg.at<uchar>(i, j) == BG_COLOR_CODE) {
//		imgData->bg_pixel++;
//			}
//			else if (imgData->modelImg.at<uchar>(i, j) == TISSUE_COLOR_CODE) {
//				imgData->tissue_pixel++;
//			}
//			else if (imgData->modelImg.at<uchar>(i, j) == FAT_COLOR_CODE) {
//				imgData->fat_pixel++;
//			}
//			else { //if ( imgData->modelImg.at<uchar>(i, j) == NONFAT_COLOR_CODE ) {
//				imgData->nonfat_pixel++;
//			}
//			return imgData->getFatPercentage();
//}
//float FatProcessor::normalizeData(float x, float min, float max){
//	return (x - min) / (max - min);
//}
//
