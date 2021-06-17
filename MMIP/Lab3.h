#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;


void GaussianBlur(const Mat& in_image, Mat& out_image, int ksize, double sigma);
void convolution(const Mat& in_image, const double* Mask, int ksize, double koef, Mat& out_image);
void test_Lab3();