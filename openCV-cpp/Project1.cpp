#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/////////////////// Project 1 ////////////////////

Mat img;
VideoCapture cap(0);

Point getContours(Mat imgDil);

// { hmin, hmax, smin, smax, vmin, vmax };
vector<pair<string, vector<int>>> colorDetected = { {"BluePen", {79,117,66,165,78,255}} };

vector<Scalar> colorToShow = { {0,0,255} };

vector<pair<Scalar, Point>> colorPoints;

vector<pair<Scalar, Point>> findColor(Mat img) {
	Mat imgHSV, mask;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	Point corner;

	for (int i = 0; i < colorDetected.size(); i++) {
		Scalar lower(colorDetected[i].second[0], colorDetected[i].second[2], colorDetected[i].second[4]);
		Scalar upper(colorDetected[i].second[1], colorDetected[i].second[3], colorDetected[i].second[5]);

		inRange(imgHSV, lower, upper, mask);
		//imshow(colorDetected[i].first, mask);

		Mat imgBlur, imgCanny, imgDil;

		/*GaussianBlur(mask, imgBlur, Size
		(3, 3), 3, 0);
		Canny(imgBlur, imgCanny, 25, 75);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgCanny, imgDil, kernel);
		imshow(colorDetected[i].first, imgDil);*/

		corner = getContours(mask);
		if(corner.x != 0 && corner.y!=0)
			colorPoints.push_back({ colorToShow[i], corner});
	}

	return colorPoints;
}

Point getContours(Mat imgDil) {

	Point corner(0, 0);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> polyConerPoints(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++) {

		int area = contourArea(contours[i]);
		//cout << area << endl;
		if (area > 200) {
			float peri = arcLength(contours[i], true);
			//cout << peri << endl;
			approxPolyDP(contours[i], polyConerPoints[i], 0.02 * peri, true);

			boundRect[i] = boundingRect(polyConerPoints[i]);

			//drawContours(img, polyConerPoints, i, Scalar(255, 0, 255), 2);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 0, 255), 4);
			corner.x = boundRect[i].x + boundRect[0].width / 2;
			corner.y = boundRect[i].y;
			cout << corner.x << "," << corner.y << endl;

		}
	}
	

	return corner;

	
}

void draw(vector<pair<Scalar, Point>> colorPoints) {

	for (int i = 0; i < colorPoints.size(); i++) {
		circle(img, colorPoints[i].second, 5, colorPoints[i].first, FILLED);
		// (image, center point, radius, color, thickness/FILLED)
	}

}

void main() {

	/*VideoCapture cap(0);*/

	vector<pair<Scalar, Point>> PointsAndColor;

	while (true) {

		cap.read(img);
		flip(img, img, +1);
		PointsAndColor = findColor(img);

		draw(PointsAndColor);

		imshow("Camera", img);
		waitKey(2);
		
	}
}