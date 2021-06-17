#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat ApplyGrowingRegions(const Mat& Image, const Point point, const uchar threshold);
void test_Lab7();