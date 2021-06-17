#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


void filter(Mat imageIn, Mat imageOut, double* matrix, int sizeX, int sizeY, double sum);

uchar* hist(Mat imageIn);
uchar avarage(Mat imageIn);
void threshold(Mat imageIn, Mat imageOut);
void test_Lab8();