#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

///////////////// COLOR DETECTION /////////////////////////

void main() {

	string path = "Resources/shapes.png";
	Mat mask, imgHSV, img = imread(path);

	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	int hmin = 0, smin = 110, vmin = 153;
	int hmax = 19, smax = 240, vmax = 255;

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);


	while (true) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		inRange(imgHSV, lower, upper, mask);
		
		//(inputImage, lower_limit, upper_limit, outputImage);

		imshow("Car Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image Mast", mask);
		waitKey(1);
	}

}