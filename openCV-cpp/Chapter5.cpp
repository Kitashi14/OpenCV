#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////////	WRAP IMAGES ////////////////////

float w = 250, h = 350;
Mat matrix, imgWarp;

void main()
{

    String path = "Resources/cards.jpg";
    Mat cardImg, img = imread(path);

    resize(img, cardImg, Size(), 0.5, 0.5);

    Point2f src[4] = { {264.5, 71}, {384, 96.5}, {202.5, 197.5}, {337, 228.5} };
    Point2f dst[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(cardImg, imgWarp, matrix, Point(w, h));

    for (int i = 0; i < 4; i++) {
        circle(cardImg, src[i], 6, Scalar(0, 0, 255), FILLED);
    }

    imshow("Image", cardImg);
    imshow("Image Warp", imgWarp);

    waitKey(0);
}