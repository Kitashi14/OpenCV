#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;


/////////////////// Images ////////////////////

//void main() {
//
//	//std::string;
//	//cv::imread; 
//
//	string path = "Resources/test.png";
//	Mat img = imread(path);
//	imshow("Image", img);
//	waitKey(0);
//}


/////////////////// Video ////////////////////
//
//void main() {
//
//	string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//	while (true) {  //gives error when no images is left
//		cap.read(img);
//
//		imshow("Image", img);
//		waitKey(1);  //delay of 1 milli-second
//	}
//}

/////////////////// WebCam ////////////////////

void main() {

	VideoCapture cap(0);  // camera id (only one camera so '0')
	Mat img;

	while (true) {  //gives error when no images is left
		cap.read(img);

		imshow("Image", img);
		waitKey(1);  //delay of 1 milli-second
	}
}