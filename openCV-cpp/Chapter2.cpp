#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;


/////////////////// BASIC FUNCTIONS ////////////////////
// CONVERTIONS OF IMAGE

void main() {

	//std::string;
	//cv::imread; 

	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur1, imgBlur2, imgCanny1,imgCanny2, imgDil, imgErode;

	// CONVERT TO GRAYSCALE
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	//CONVERT TO BLURIMG
	GaussianBlur(imgGray, imgBlur1, Size
	(7, 7), 7, 0);

	GaussianBlur(imgGray, imgBlur2, Size
	(3, 3), 3, 0);

	//CONVERT TO EDGE Detector
	Canny(imgBlur2, imgCanny1, 50, 150);
	Canny(imgBlur2, imgCanny2, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//size is directly proportional to the amount of dilation
	
	dilate(imgCanny2, imgDil, kernel);
	erode(imgDil, imgErode, kernel);
	
	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur 1", imgBlur1);
	//imshow("Image Blur 2", imgBlur2);
	//imshow("Image Canny 1", imgCanny1);
	imshow("Image Canny 2", imgCanny2);
	imshow("Image Dilation", imgDil);
	imshow("Image Erode", imgErode);

	waitKey(0);
}