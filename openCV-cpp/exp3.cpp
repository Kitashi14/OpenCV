#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////////// Doc viewer webCam ////////////////////

Mat imgOriginal, imgThre, imgGray, imgBlur, imgCanny, imgDil;

vector<Point> getContour(Mat img)
{

	vector<Point> biggestContour = {{0, 0}};

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> polyConerPoints(contours.size());
	vector<Rect> boundRect(contours.size());
	string shapeName;

	int maxarea = 0;

	for (int i = 0; i < contours.size(); i++)
	{

		int area = contourArea(contours[i]);
		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], polyConerPoints[i], 0.02 * peri, true);
			int objCorner = (int)polyConerPoints[i].size();

			if (objCorner == 4 and maxarea < max(area, maxarea))
			{
				maxarea = area;
				biggestContour = {polyConerPoints[i][0], polyConerPoints[i][1], polyConerPoints[i][2], polyConerPoints[i][3]};
				drawContours(imgOriginal, polyConerPoints, i, Scalar(255, 0, 255), 2);
			}
		}
	}
	return biggestContour;
}

Mat preProcessing(Mat img)
{

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	// size is directly proportional to the amount of dilation

	dilate(imgCanny, imgDil, kernel);

	return imgDil;
}

void draw(vector<Point> points)
{

	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i], 10, Scalar(65, 42, 244), FILLED);
		// (image, center point, radius, color, thickness/FILLED)

		// putText(imgOriginal,to_string( i + 1), points[i], FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0), 2);
		//(image, text, left_lower_point, font_family, scale, color, width);
	}
}

vector<Point> order(vector<Point> points)
{

	vector<int> sumPoints, diffPoints;
	vector<Point> finalPoints;

	for (int i = 0; i < points.size(); i++)
	{
		sumPoints.push_back((points[i].x + points[i].y));
		diffPoints.push_back((points[i].x - points[i].y));
	}

	finalPoints.push_back(points[(min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin())]);	 // 1st point
	finalPoints.push_back(points[(max_element(diffPoints.begin(), diffPoints.end()) - diffPoints.begin())]); // 2nd point
	finalPoints.push_back(points[(min_element(diffPoints.begin(), diffPoints.end()) - diffPoints.begin())]); // 3rd point
	finalPoints.push_back(points[(max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin())]);	 // 4th point

	for (auto e : finalPoints)
	{
		cout << "(" << e.x << "," << e.y << ")"
			 << ",  ";
	}
	cout << "\n";

	return finalPoints;
}

Mat wrapping(vector<Point> points)
{

	float w = 350, h = 475;
	Mat matrix, imgWarp;

	Point2f src[4] = {points[0], points[1], points[2], points[3]};
	Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(imgOriginal, imgWarp, matrix, Point(w, h));

	int cropValue = 10;

	Rect roi(cropValue, cropValue, w - (2 * cropValue), h - (2 * cropValue));

	imgWarp = imgWarp(roi);

	return imgWarp;
}

void main()
{

	VideoCapture cap(0);

	while (true)
	{ // gives error when no images is left

		cap.read(imgOriginal);
		// preprocessing
		imgThre = preProcessing(imgOriginal);

		// getContour for biggest contour
		vector<Point> initialPoint = getContour(imgThre);

		if (initialPoint.size() != 4)
		{
			cout << "NO doc present in frame" << endl;
		}

		else
		{
			// ordering
			vector<Point> finalPoint = order(initialPoint);

			// draw points
			// draw(finalPoint);

			// wrapping
			Mat finalImg = wrapping(finalPoint);

			// imshow("Image Dilation", imgThre);
			imshow("Doc", finalImg);
		}
		imshow("Image", imgOriginal);
		waitKey(1); // delay of 1 milli-second
	}
}