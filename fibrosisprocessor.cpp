#include "fibrosisprocessor.h"
#include <qdebug.h>

CvSVM FibrosisProcessor::trainedSvm;

FibrosisProcessor::FibrosisProcessor()
{

}

FibrosisProcessor::~FibrosisProcessor()
{

}

void FibrosisProcessor::loadTest(std::string path)
{
	trainedSvm.load(path.c_str());
	qDebug() << "var count: " << trainedSvm.get_var_count();
}

void FibrosisProcessor::enhance(const cv::Mat& inputImage, cv::Mat& outputImage ) {
	
	const int rows = inputImage.rows;
	const int cols = inputImage.cols;

	outputImage = inputImage.clone();

	double mT = 126, mF = 109;

	//for each pixel
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//find the distance
			double disT = abs(mT - inputImage.at<cv::Vec3b>(i, j)[2]);
			double disF = abs(mF - inputImage.at<cv::Vec3b>(i, j)[2]);

			if ((disT > disF) && (inputImage.at<cv::Vec3b>(i, j)[1] > inputImage.at<cv::Vec3b>(i, j)[2])) 
			{
				//fibrosis
				double c = 6 * disF;
				double newVal = inputImage.at<cv::Vec3b>(i, j)[2] - c - 50;
				if (newVal < 0)
					newVal = 0;
				outputImage.at<cv::Vec3b>(i, j)[2] = (uchar)newVal;
			}
			else if ((disT < disF) && (inputImage.at<cv::Vec3b>(i, j)[1] < inputImage.at<cv::Vec3b>(i, j)[2]))
			{
				//tissue
				double c = 6 * disT;
				double newVal = inputImage.at<cv::Vec3b>(i, j)[2] + c + 25;
				if (newVal > 255)
					newVal = 255;
				outputImage.at<cv::Vec3b>(i, j)[2] = (uchar)newVal;
			}
		}
	}

}

void FibrosisProcessor::train(const std::string& path)
{
	std::string trainImageName;
	std::string gtImageName;
	cv::Mat trainGt;
	cv::Mat fibVector, labelVector;
	SetOfContours contours;
	std::vector<int> labels;
	std::vector<FibrosisFeatures> fibFts;
	cv::Mat gtImage;
	cv::Mat originalImage;

	std::vector<std::string> listImageName = FileManager::getListFromFile(path + "/train_image_list.txt");

	std::vector<cv::Mat> enhanceImageList(listImageName.size());

	for (int i = 0; i < listImageName.size(); i++)
	{
		trainImageName = listImageName[i] + ".tif";
		gtImageName = "hi_" + trainImageName;

		originalImage = cv::imread(path + "/" + trainImageName );
		gtImage = cv::imread(path + "/" + gtImageName);

		if (originalImage.data)
			qDebug() << "OK ";

		if (gtImage.data)
			qDebug() << "GT OK";
		
		enhance(originalImage, enhanceImageList[i]);
		cv::namedWindow("xx");
		cv::imshow("xx", enhanceImageList[i]);

		//stub_train(enhanceImageList[i], gtImage, fibFts, labels);
	}

	//convertSample2FtVector(fibFts, labels, fibVector, labelVector);

	//trainSVM(fibVector,labelVector );
	
}

void FibrosisProcessor::detectBackground( const cv::Mat& inputImage, cv::Mat& outputImage )
{

}


void FibrosisProcessor::stub_predict(cv::Mat& inputImg, cv::Mat& outputImg)
{
	cv::Mat tempImg(inputImg.rows, inputImg.cols, CV_8UC1);
	outputImg = inputImg.clone();
	cv::Mat a_ftVector(1, 3, CV_32FC1);

	for (int i = 0; i < inputImg.rows; i++) 
	{
		for (int j = 0; j < inputImg.cols; j++) 
		{
			//read color value of each pixel
			a_ftVector.at<float>(0, 0) = inputImg.at<cv::Vec3b>(i, j)[0];
			a_ftVector.at<float>(0, 1) = inputImg.at<cv::Vec3b>(i, j)[1];
			a_ftVector.at<float>(0, 2) = inputImg.at<cv::Vec3b>(i, j)[2];

			float respones = trainedSvm.predict(a_ftVector, 3);

			if (respones > 0)  
			{
				tempImg.at<uchar>(i, j) = 0;
			}
			else
			{
				tempImg.at<uchar>(i, j) = 255;
			}
		}
	}


	for (int i = 0; i < inputImg.rows; i++)
	{
		for (int j = 0; j < inputImg.cols; j++)
		{
			outputImg.at<cv::Vec3b>(i, j)[0] = tempImg.at<uchar>(i, j);
			outputImg.at<cv::Vec3b>(i, j)[1] = tempImg.at<uchar>(i, j);
			outputImg.at<cv::Vec3b>(i, j)[2] = tempImg.at<uchar>(i, j);
		}
	}
}

void FibrosisProcessor::trainSVM(const cv::Mat& ftVector, const cv::Mat& labelsVector )
{
	qDebug() << "TRAIN SVM";
	cv::SVMParams params;
	params.svm_type = CvSVM::C_SVC;
	params.kernel_type = CvSVM::RBF;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 10, FLT_EPSILON);

	//CvSVM svm;
	// train
	trainedSvm.train_auto(ftVector, labelsVector, cv::Mat(), cv::Mat(), params);
	//trainedSvm.save("train_SVM");
	qDebug() << "TRAIN SVM FINISH";

}

void FibrosisProcessor::stub_train(cv::Mat inputImg, cv::Mat gtImg, std::vector<FibrosisFeatures>& FibFts, std::vector<int>& labels)
{
	const int rows = inputImg.rows;
	const int cols = inputImg.cols;

	//for each pixel
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) 
		{
			FibrosisFeatures ff;
			//compute the bin index
			
			ff.blue = inputImg.at<cv::Vec3b>(i, j)[0];
			ff.green = inputImg.at<cv::Vec3b>(i, j)[1];
			ff.red = inputImg.at<cv::Vec3b>(i, j)[2];

			FibFts.push_back(ff);
			if (gtImg.at<cv::Vec3b>(i, j)[0] == 0 && gtImg.at<cv::Vec3b>(i, j)[1] == 255 && gtImg.at<cv::Vec3b>(i, j)[2] == 0) 
			{
				//fibrosis
				labels.push_back(1);
			}
			else {
				//tissue + bg = non fibrosis
				labels.push_back(0);
				//numTissue++;
				//t[idx1][idx2][idx3] += 1;
			}
		}
	}

}


void FibrosisProcessor::test_enhance(std::string path)
{
	cv::Mat inputImage = cv::imread(path, CV_LOAD_IMAGE_COLOR);
	cv::Mat resultImage;
	enhance(inputImage, resultImage);

	cv::namedWindow("ENHANCE");
	cv::imshow("ENHANCE", resultImage);
}

void FibrosisProcessor::convertSample2FtVector(const std::vector<FibrosisFeatures>& fibFts, const std::vector<int>& labels, cv::Mat& fibVector, cv::Mat& labelVector)
{
	fibVector = cv::Mat(fibFts.size(), 3, CV_32FC1); // 3 feature
	labelVector = cv::Mat(labels.size(), 1, CV_32FC1);

	qDebug() << "FIB SIZE " << fibFts.size();
	qDebug() << "LABEL " << labels.size();



	for (int i = 0; i < fibFts.size(); i++){
		fibVector.at<float>(i, 0) = fibFts[i].blue;
		fibVector.at<float>(i, 1) = fibFts[i].green;
		fibVector.at<float>(i, 2) = fibFts[i].red;
		labelVector.at<float>(i, 0) = labels[i];

	}

}

void FibrosisProcessor::produceModelImage(cv::Mat& inputImg, cv::Mat& outputImg)
{

	cv::Mat a_ftVector(1, 6, CV_32FC1);

	//fibrosis

	for (int i = 0; i < inputImg.rows; i++)
	{
		for (int j = 0; j < inputImg.cols; j++)
		{

			float blue = inputImg.at<cv::Vec3b>(i, j)[0];
			float green = inputImg.at<cv::Vec3b>(i, j)[1];
			float red = inputImg.at<cv::Vec3b>(i, j)[2];
			
			if (blue <= 0)	blue = 1;
			if (green <= 0) green = 1;
			if (red <= 0)	red = 1;

			//read color value of each pixel
			a_ftVector.at<float>(0, 0) = blue;
			a_ftVector.at<float>(0, 1) = green;
			a_ftVector.at<float>(0, 2) = red;
			
			// three extra features
			a_ftVector.at<float>(0, 3) = red / blue;
			a_ftVector.at<float>(0, 4) = green / blue;
			a_ftVector.at<float>(0, 5) = green / red;

			float respones = trainedSvm.predict(a_ftVector, 6);
			//std::cout << respones << endl;
			if (respones < 0)
			{
				outputImg.at<uchar>(i, j) = FibrosisData::FIBROSIS_COLOR;
			}
			else
			{
				outputImg.at<uchar>(i, j) = FibrosisData::TISSUE_COLOR;
			}
		}
	}

}
