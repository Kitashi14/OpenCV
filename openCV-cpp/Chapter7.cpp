#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;


///////////////// SHAPE DETECTION ////////////////////

void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> polyConerPoints(contours.size());
	vector<Rect> boundRect(contours.size());
	string shapeName;

	for (int i = 0; i < contours.size(); i++) {
		
		int area = contourArea(contours[i]);
		cout << area << endl;
		if (area > 1000) {
			float peri = arcLength(contours[i], true);
			cout << peri << endl;
			approxPolyDP(contours[i], polyConerPoints[i], 0.02 * peri, true);
			

			boundRect[i] =  boundingRect(polyConerPoints[i]);
			
			
			int objCorner = (int)polyConerPoints[i].size();

			if (objCorner == 3) { shapeName = "Tri"; }
			else if (objCorner == 4) {
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout <<"AspRatio : "<< aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { shapeName = "Square"; }
				else {
					shapeName = "Rec";
				}
			}
			else if (objCorner >= 4) { shapeName = "Circle"; }

			drawContours(img, polyConerPoints, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 0, 255), 4);
			putText(img, shapeName, { boundRect[i].x , boundRect[i].y-5}, FONT_HERSHEY_DUPLEX, 0.45, Scalar(0, 0, 0), 1);

		}
	}
}

void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);

	Mat imgGray, imgBlur,imgCanny, imgDil;

	// Preprocessing  of the Image
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size
	(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	imshow("Image", img);
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Diluted", imgDil);*/
	waitKey(0);
}