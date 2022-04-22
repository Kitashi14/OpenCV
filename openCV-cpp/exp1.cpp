#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/// <summary>
/// COLOR DETECTION USING WEBCAM
/// </summary>

void main() {

	VideoCapture cap(0);  // camera id (only one camera so '0')
	Mat mask, imgHSV, img;

	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);


	while (true) {  //gives error when no images is left
		cap.read(img);
		flip(img, img, +1);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		cout << hmin<< "," << hmax << "," << smin << "," << smax << "," << vmin << "," << vmax << endl;

		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image Mask", mask);
		waitKey(1);  //delay of 1 milli-secondv
	}
}