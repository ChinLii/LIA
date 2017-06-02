#include <qdebug.h>
#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <Windows.h>
#include <string>
#include <iostream>
#include "fatdata.h"
#include "fatprocessor.h"
#include "imagehelper.h"
#include "fibrosisprocessor.h"
#include "imageview.h"
#include "dummywidget.h"

float findAccuracyOfFatDetection(float tp, float fn, float fp, float tn){
	float acc;
	acc = ((tp + tn) / (tp + tn + fp + fn)) * 100;
	return acc;
}


float findTPR( float tp, float fn )
{
	return (tp / (tp + fn)) * 100;
}

float findFPR(float fp, float fn)
{
	return (fp / (fp + fn)) * 100;
}



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	/*FatProcessor::train("C:/Users/X220/Documents/Visual Studio 2013/Projects/LIA/LIA/trainImages");
	FibrosisProcessor::loadTest("C:/Users/X220/Desktop/trainSvmFib.xml");

	MainWindow window;
	window.show();*/


	QScrollArea d;


	QLabel* label = new QLabel();

	label->setPixmap(QPixmap::fromImage(QImage("C:/Users/X220/Desktop/testImage.tif")).scaled(100,100));
	label->setGeometry(100, 100, 100, 100);

	label->setParent(&d);
	
	d.show();

	//std::string path = "C:/Users/X220/Desktop/cat";
	//float sum = 0;

	//for (int x = 0; x < 16; x++){
	//	
	//	float tp = 0, fn = 0; // for find true positive rate
	//	float fp = 0, tn = 0; // for find false positive rate
	//	
	//	
	//	std::string name = "lia" + std::to_string(x+1);
	//	DataImage dumma(name + ".tif" , path, 0);

	//	dumma.processFat();

	//	cv::Mat input = dumma.getModelImage();
	//	cv::Mat test = cv::imread(path + "/" +  name + "_test.tif");
	//	
	//	

	//	cv::imwrite(path + "/dog_ " + name + ".tif", input);

	//	for (int i = 0; i < input.rows; i++){
	//		for (int j = 0; j < input.cols; j++){
	//			if (input.at<uchar>(i, j) == 255 && test.at<cv::Vec3b>(i, j)[1] == 255){
	//				// Fat correct
	//				tp++;
	//			}
	//			else if (input.at<uchar>(i, j) != 255 && test.at<cv::Vec3b>(i, j)[1] != 255){
	//				//non fat correct
	//				tn++;
	//			}
	//			else if (input.at<uchar>(i, j) != 255 && test.at<cv::Vec3b>(i, j)[1] == 255){
	//				//non fat incorrect as fat
	//				fp++;
	//			}
	//			else if (input.at<uchar>(i, j) == 255 && test.at<cv::Vec3b>(i, j)[1] != 255){
	//				//fat incorrect as non fat
	//				fn++;
	//			}
	//		}
	//	}

	//	float dd = findAccuracyOfFatDetection(tp, fn, fp, tn);
	//	float dTPR = findTPR(tp, fn);
	//	float dFPR = findFPR(fp, fn);
	//	sum += dd;

	//	qDebug() << "Image" << std::to_string(x + 1).c_str();
	//	qDebug() << "Acc: " << dd;
	//	qDebug() << "TPR: " << dTPR;
	//	qDebug() << "FPR: " << dFPR;
	//}


	//qDebug() << "Average accuracy: " << (sum / 16);


	//FibrosisProcessor::loadTest("C:/Users/X220/Desktop/train_SVM_fib");

	//DataImage image("name", "location", Folder::FIBROSIS_TYPE );
	//image.process();

	//FatProcessor::loadTest("ddd");
	/*MainWindow mainWindow;
	mainWindow.show();*/

	//FibrosisProcessor::train("C:/Users/X220/Desktop/fibs");


	//FibrosisProcessor::test_enhance("C:/Users/kanan_000/Downloads/03215159.TIF");
	//FibrosisProcessor::train("C:/Users/kanan_000/Documents/Visual Studio 2013/Projects/LIA/LIA/fib_train_images");
	//DataImage image( "03221548.TIF",
	//"C:/Users/kanan_000/Documents/Visual Studio 2013/Projects/20150209 FibrsosiDetection by Pond/20150209 FibrsosiDetection by Pond/mainwindow/dataset/new");
	
	//image.processFibrosis();

	//FileManager::createDirectory("C://Users//ChinLi-PC//Desktop//IBB");

	//QScrollArea area;
	///*ImagePanel* panel = new ImagePanel;
	//area.setWidget(panel);*/
	//
	//QVBoxLayout layout;
	//layout.addWidget(&area);

	//QWidget w;
	//w.setLayout(&layout);
	//w.show();

	//DummyWidget w;
	//w.show();

	
	return a.exec();
}
