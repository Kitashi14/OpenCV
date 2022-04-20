#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;


///////////////////  RESIZE AND CROP  ////////////////////

void main() {

	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgResize1, imgResize2, imgCrop;
	
	cout << img.size() << endl;
	resize(img, imgResize1, Size(640, 480));
	resize(img, imgResize2, Size(), 0.5,0.5);
	
	cout << imgResize1.size() << endl;
	cout << imgResize2.size() << endl;

	Rect roi(200, 100, 300, 300);
	// (coordinate x, coordinate y, width, height)

	imgCrop = img(roi);

	imshow("Image", img);
	imshow("Image Resize with dimensions", imgResize1);
	//imshow("Image Resize with relative scaling", imgResize2);
	imshow("Image Resize with relative scaling", imgCrop);
	
	waitKey(0);
}