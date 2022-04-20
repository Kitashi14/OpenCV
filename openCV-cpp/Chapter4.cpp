#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;


///////////////////  DRAW SHAPES AND TEXT ////////////////////

void main() {

	//Blank Image	
	Mat img(512, 512, CV_8UC3, Scalar(78, 106, 0));
	//(height, width, type of pixel, color)	
	circle(img, Point(256, 256), 155, Scalar(65, 42, 244), FILLED);
	// (image, center point, radius, color, thickness/FILLED)

	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), 4);
	line(img, Point(145, 276), Point(367, 276), Scalar(255, 255, 255),4);

	putText(img, "BanglaDesh", Point(195, 266), FONT_HERSHEY_DUPLEX, 0.65, Scalar(255, 255, 255), 2);
	//(image, text, left_lower_point, font_family, scale, color, width);

	imshow("Bangldesh Flag", img);
	

	waitKey(0);
}